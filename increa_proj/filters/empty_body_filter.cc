/**
 *
 *  empty_body_filter.cc
 *
 */

#include "empty_body_filter.h"

using namespace drogon;

void empty_body_filter::doFilter(const HttpRequestPtr &req, FilterCallback &&fcb,
                                 FilterChainCallback &&fccb) {
    Json::Value json_body;
    if (auto req_body = req->getJsonObject(); req_body) {
        fccb();
        return;
    }

    json_body["status"] = "error";
    json_body["message"] = "body is required";
    auto response = HttpResponse::newJsonHttpResponse(json_body);
    response->setStatusCode(HttpStatusCode::k400BadRequest);
    fcb(response);
    return;
}
