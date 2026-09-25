#pragma once
#include <functional>
#include <drogon/HttpSimpleController.h>

namespace three_v_service::interfaces::http {
    class ContactController final : public drogon::HttpSimpleController<ContactController> {
        public: void asyncHandleHttpRequest(
            drogon::HttpRequestPtr const& request,
            std::function<void(drogon::HttpResponsePtr const&)>&& callback
        )override;
        PATH_LIST_BEGIN
        PATH_ADD("/api/contact", drogon::Post);
        PATH_LIST_END
    };
}