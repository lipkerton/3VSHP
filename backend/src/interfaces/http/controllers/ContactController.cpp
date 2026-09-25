#include "ContactController.h"
#include <json/json.h>

namespace three_v_service::interfaces::http {
    void ContactController::asyncHandleHttpRequest(
        drogon::HttpRequestPtr const&,
        std::function<void(drogon::HttpResponsePtr const&)>&& callback
    ) {
        Json::Value json_value = Json::Value(Json::objectValue);
        json_value["status"] = "ok";
        drogon::HttpResponsePtr response = drogon::HttpResponse::newHttpJsonResponse(json_value);
        callback(response);
    }
}