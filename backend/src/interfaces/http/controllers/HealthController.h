#pragma once
#include <functional>
#include <drogon/HttpSimpleController.h>

namespace three_v_service::interfaces::http {
    class HealthController final : public drogon::HttpSimpleController<HealthController> {
        public: void asyncHandleHttpRequest(
            drogon::HttpRequestPtr const&,
            std::function<void(drogon::HttpResponsePtr const&)>&& callback
        )override;
        PATH_LIST_BEGIN
        PATH_ADD("/health", drogon::Get);
        PATH_LIST_END
    };
}