#include <drogon/drogon.h>

int main(int argc, char* argv[]) {
    drogon::HttpAppFramework& drogon_app = drogon::app();
    drogon_app.loadConfigFile("./config.json");
    drogon_app.run();
}