/**
 *
 *  signup_filter.cc
 *
 */

#include "signup_filter.h"

using namespace drogon;

void signup_filter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    
    auto request_body = req->getJsonObject();

    if (!(request_body->isMember("login")) || !(request_body->isMember("email")) ||
        !(request_body->isMember("password")) || !(request_body->isMember("repeated password"))) {
        json["status"] = "error";
        json["message"] = "missing login/email/password";

        auto response = HttpResponse::newHttpJsonResponse(json);
        response->setStatusCode(HttpStatusCode::k400BadRequest);

        fcb(res);
        return;
    }

    if ((*request_body)["password"] != (*request_body)["repeated password"]) {
        json["status"] = "error";
        json["message"] = "wrong data";

        auto response = HttpResponse::newHttpJsonResponse(json);
        response->setStatusCode(HttpStatusCode::k400BadRequest);

        fcb(res);
        return;
    }
    
    fccb();
}
