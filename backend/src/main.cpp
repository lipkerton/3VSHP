#if defined(_WIN32)
    #include <winsock2.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <cerrno>
#endif
#include <string_view>
#include <iostream>
#include <array>

#if defined(_WIN32)
    using sock_type = SOCKET;
    sock_type const invalid_socket = INVALID_SOCKET;
    int const socket_error = SOCKET_ERROR;
#elif defined(__linux__) || defined(__APPLE__)
    using sock_type = int;
    sock_type const invalid_socket = -1;
    int const socket_error = -1;
#endif

int close_socket(sock_type socket_handle) {
    #if defined(_WIN32)
        return closesocket(socket_handle);
    #elif defined(__linux__) || defined(__APPLE__)
        return close(socket_handle);
    #endif
}

int cleanup_networking() {
    #if defined(_WIN32)
        return WSACleanup();
    #elif defined(__linux__) || defined(__APPLE__)
        return 0;
    #endif
}

int get_last_socket_error() {
    #if defined(_WIN32)
        return WSAGetLastError();
    #elif defined(__linux__) || defined(__APPLE__)
        return errno;
    #endif
}

int main() {
    #if defined(_WIN32)
        WSADATA wsa_data {};
        int const startup_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
        if (startup_result != 0) {
            std::cerr << "Error while initializing Winsock! Error code: " << startup_result << "\n";
            return startup_result;
        }
    #endif

    sock_type const listening_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listening_socket == invalid_socket) {
        int const error_code = get_last_socket_error();
        std::cerr << "Error while initializing socket! Error code: " << error_code << "\n";
        cleanup_networking();
        return error_code;
    }
    sockaddr_in server_address {};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    int const bind_result = bind(
        listening_socket,
        reinterpret_cast<sockaddr const*>(&server_address),
        sizeof(server_address)
    );
    if (bind_result == socket_error) {
        int const error_code = get_last_socket_error();
        std::cerr << "Error while binding address to the socket! Error code: " << error_code << "\n";
        close_socket(listening_socket);
        cleanup_networking();
        return error_code;
    }
    int const listen_result = listen(listening_socket, SOMAXCONN);
    if (listen_result == socket_error) {
        int const error_code = get_last_socket_error();
        std::cerr << "Error while listening! Error code: " << error_code << "\n";
        close_socket(listening_socket);
        cleanup_networking();
        return error_code;
    }
    std::cout << "ThreeVServiceBackend is running!\n";
    sock_type const client_socket = accept(listening_socket, nullptr, nullptr);
    if (client_socket == invalid_socket) {
        int const error_code = get_last_socket_error();
        std::cerr << "Error while accepting client connection! Error code: " << error_code << "\n";
        close_socket(listening_socket);
        cleanup_networking();
        return error_code;
    }
    std::cout << "Client connected!\n";
    std::array<char, 4096> request_buffer {};
    auto const recv_result = recv(
        client_socket,
        request_buffer.data(),
        static_cast<int>(request_buffer.size()),
        0
    );
    if (recv_result == socket_error) {
        int const error_code = get_last_socket_error();
        std::cerr << "Error while reading system buffer! Error code: " << error_code << "\n";
        close_socket(client_socket);
        close_socket(listening_socket);
        cleanup_networking();
        return error_code;
    } else if (recv_result == 0) {
        std::cout << "Client has not send any messages and closed the connection!\n";
    } else {
        std::cout << "Size of bytes from system's buffer: " << recv_result << "\n";
        std::cout.write(
            request_buffer.data(),
            static_cast<std::streamsize>(recv_result)
        ) << "\n";
        std::string_view const response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 2\r\nConnection: close\r\n\r\nOK";
        auto const send_result = send(client_socket, response.data(), static_cast<int>(response.size()), 0);
        if (send_result == socket_error) {
            int const error_code = get_last_socket_error();
            std::cerr << "Error while sending response! Error code: " << error_code << "\n";
            close_socket(listening_socket);
            close_socket(client_socket);
            cleanup_networking();
            return error_code;       
        }
        std::cout << "Size of bytes in server response: " << send_result << "\n";
    }
    int const close_client_result = close_socket(client_socket);
    if (close_client_result == socket_error) {
        int const error_code = get_last_socket_error();
        std::cerr << "Error while closing client socket! Error code: " << error_code << "\n";
        close_socket(listening_socket);
        cleanup_networking();
        return error_code;
    }
    int const close_listening_result = close_socket(listening_socket);
    if (close_listening_result == socket_error) {
        int const error_code = get_last_socket_error();
        std::cerr << "Error while closing socket! Error code: " << error_code << "\n";
        cleanup_networking();
        return error_code;
    }
    int const cleanup_result = cleanup_networking();
    if (cleanup_result == socket_error) {
        int const error_code = get_last_socket_error();
        std::cerr << "Error while doing cleanup! Error code: " << error_code << "\n";
        return error_code;
    }
    return 0;
}