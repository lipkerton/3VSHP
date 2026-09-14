#include <drogon/drogon.h>

int main() {
    drogon::HttpAppFramework& drogon_app = drogon::app();
    drogon_app.addListener("127.0.0.1", 8080);
    drogon_app.run();
}