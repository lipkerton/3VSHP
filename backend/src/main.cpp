#if defined(_WIN32)
    #include <winsock2.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
#endif
#include <iostream>

#if defined(_WIN32)
    using sock_type = SOCKET;
    SOCKET const invalid_socket = INVALID_SOCKET;
#elif defined(__linux__) || defined(__APPLE__)
    using sock_type = int;
    int const invalid_socket = -1;
#endif

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
        int const wsa_error = WSAGetLastError();
        std::cerr << "Error while initializing socket! Error code: " << wsa_error << "\n";
        WSACleanup();
        return wsa_error;
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
    if (bind_result == SOCKET_ERROR) {
        int const wsa_error = WSAGetLastError();
        std::cerr << "Error while binding address to the socket! Error code: " << wsa_error << "\n";
        closesocket(listening_socket);
        WSACleanup();
        return wsa_error;
    }
    int const listen_result = listen(listening_socket, SOMAXCONN);
    if (listen_result == SOCKET_ERROR) {
        int const wsa_error = WSAGetLastError();
        std::cerr << "Error while listening! Error code: " << wsa_error << "\n";
        closesocket(listening_socket);
        WSACleanup();
        return wsa_error;
    }
    std::cout << "ThreeVServiceBackend is running!\n";
    sock_type const client_socket = accept(listening_socket, nullptr, nullptr);
    if (client_socket == invalid_socket) {
        int const wsa_error = WSAGetLastError();
        std::cerr << "Error while accepting client connection! Error code: " << wsa_error << "\n";
        closesocket(listening_socket);
        WSACleanup();
        return wsa_error;
    }
    std::cout << "Client connected!\n";
    int const close_client_result = closesocket(client_socket);
    if (close_client_result == SOCKET_ERROR) {
        int const wsa_error = WSAGetLastError();
        std::cerr << "Error while closing client socket! Error code: " << wsa_error << "\n";
        closesocket(listening_socket);
        WSACleanup();
        return wsa_error;
    }
    int const close_listening_result = closesocket(listening_socket);
    if (close_listening_result == SOCKET_ERROR) {
        int const wsa_error = WSAGetLastError();
        std::cerr << "Error while closing socket! Error code: " << wsa_error << "\n";
        WSACleanup();
        return wsa_error;
    }
    int const cleanup_result = WSACleanup();
    if (cleanup_result == SOCKET_ERROR) {
        int const wsa_error = WSAGetLastError();
        std::cerr << "Error while doing cleanup! Error code: " << wsa_error << "\n";
        return wsa_error;
    }
    return 0;
}