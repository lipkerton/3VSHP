#include <drogon/drogon.h>

int main() {
    drogon::HttpAppFramework& drogon_app = drogon::app();
    drogon_app.registerHandler(
        "/health",
        [](
            drogon::HttpRequestPtr const&, std::function<void(drogon::HttpResponsePtr const&)>&& callback
        ){
            drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpResponse(
                drogon::k200OK, drogon::CT_TEXT_PLAIN
            );
            response->setBody("OK");
            callback(response);
        },
        {drogon::Get}
    );
    drogon_app.addListener("127.0.0.1", 8080);
    drogon_app.run();
}