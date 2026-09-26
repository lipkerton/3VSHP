#include "ContactController.h"
#include <memory>
#include <json/json.h>

namespace three_v_service::interfaces::http {
    void ContactController::asyncHandleHttpRequest(
        drogon::HttpRequestPtr const& request,
        std::function<void(drogon::HttpResponsePtr const&)>&& callback
    ) {
        std::shared_ptr<Json::Value> const& request_json = request->getJsonObject();
        Json::Value const& request_data = *request_json;
        Json::Value json_value = Json::Value(Json::objectValue);
        drogon::HttpResponsePtr response {};
        if (!request_json) {
            json_value["error"] = "invalid_json";
            response = drogon::HttpResponse::newHttpJsonResponse(json_value);
            response->setStatusCode(drogon::k400BadRequest);
        } else if (
            !request_data.isObject() 
            || !request_data.isMember("email")
            || !request_data["email"].isString()
            || request_data["email"].asString() == ""
        ) {
            json_value["error"] = "invalid_email";
            response = drogon::HttpResponse::newHttpJsonResponse(json_value);
            response->setStatusCode(drogon::k422UnprocessableEntity);
        } else {
            json_value["status"] = "ok";
            response = drogon::HttpResponse::newHttpJsonResponse(json_value);
        }
        callback(response);
    }
}