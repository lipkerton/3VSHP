#include "HealthController.h"


void HealthController::asyncHandleHttpRequest(
    drogon::HttpRequestPtr const&,
    std::function<void(drogon::HttpResponsePtr const&)>&& callback
) {
    drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpResponse(
        drogon::k200OK, drogon::CT_TEXT_PLAIN
    );
    response->setBody("OK");
    callback(response);
}