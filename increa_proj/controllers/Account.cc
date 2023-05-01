#include "Account.h"

void Account::signup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    Json::Value json;

    LOG_DEBUG << "User register";

    auto request_body = req->getJsonObject();

    if (!request->body->isMember("login") || !request_body->isMember("email") ||
        !request->body->isMember("password") || !request_body->isMember("repeated password")) {
        json["status"] = "error";
        json["message"] = "missing login/email/password";

        auto response = HttpResponse::newHttpJsonResponse(json);
        response->setStatusCode(HttpStatusCode::k400BadRequest);

        callback(response);
        return;
    }

    auto login = request_body->get("login").asString();

    json["status"] = HttpStatusCode::k200OK;
    // login = request_body["login"];
    // ...
    json["message"] = "registeted " + login;

    auto response = HttpResponse::newHttpJsonResponse(json);
    callback(response);
}

void Account::login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                    std::string &&user_id, const std::string &password) {
    LOG_DEBUG << "User " << user_id << " login";
    // Authentication algorithm, read database, verify, identify, etc...
    //...
    Json::Value json;
    json["status"] = HttpStatusCode::k200OK;
    json["result"] = "ok";
    json["token"] = drogon::utils::getUuid();
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}

void Account::get_info(const HttpRequestPtr &req, std::function<void(const HttpRequestPtr &)> &&callback,
                       std::string user_id, const std::string &token) {
    LOG_DEBUG << "User " << user_id << " get his information";

    // Verify the validity of the token, etc.
    // Read the database or cache to get user information
    Json::Value json;
    json["status"] = HttpStatusCode::k200OK;
    json["result"] = "ok";
    json["user_name"] = "Jack";
    json["user_id"] = user_id;
    json["gender"] = 1;
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}

void Account::resume(const HttpRequestPtr &req, std::function<void(const HttpRequestPtr &)> &&callback,
                     std::string user_id) {
    LOG_DEBUG << "User " << user_id << " get his resume";

    Json::Value json;
    json["status"] = HttpStatusCode::k200OK;
    json["description"] = "resume description";
    json["content"] = "resume content";
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}

void Account::groups(const HttpRequestPtr &req, std::function<void(const HttpRequestPtr &)> &&callback,
                std::string user_id) {

    LOG_DEBUG << "User " << user_id << " get his groups";                
    Json::Value json;

    if (req->getMethod() == HttpMethod::Get)
        json["status"] = HttpStatusCode::k200OK;
        json["groups_list"] = {"rockLovers", "pythonCoders", "flowersGrowers"};
        auto resp = HttpResponse::newHttpJsonResponse(json);
        callback(resp);
    else if (req->getMethod() == HttpMethod::Post) {
        auto request_body = req->getJsonObject();
        // go to db
        // group_name = request_body->get("group_name").asString()

        json["status"] = HttpStatusCode::k200OK;
        auto resp = HttpResponse::newHttpJsonResponse(json);
        callback(resp);
    }
}

//acc/settings
//acc/resume/group

