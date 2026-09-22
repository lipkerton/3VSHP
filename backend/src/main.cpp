#include <drogon/drogon.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "You need to specify config file!\n";
        return 1;
    };
    drogon::HttpAppFramework& drogon_app = drogon::app();
    drogon_app.loadConfigFile(argv[1]);
    drogon_app.run();
}