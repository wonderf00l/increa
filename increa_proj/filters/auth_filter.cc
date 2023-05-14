/**
 *
 *  auth_filter.cc
 *
 */

#include "auth_filter.h"

using namespace drogon;

void auth_filter::doFilter(const HttpRequestPtr &req, FilterCallback &&fcb, FilterChainCallback &&fccb) {
    std::string token = req->getHeader("Authorization");

    std::string decoded = utils::base64Decode(token);

    if (token != "")  // && decoded is in login table in db
    {
        fccb();
        return;
    }

    Json::Value json_body;
    json_body["message"] = "no token has been provided";
    auto res = drogon::HttpResponse::newHttpJsonResponse(json_body);
    res->setStatusCode(k401Unauthorized);
    LOG_DEBUG << "Auth has failed";

    fcb(res);
}
