#include "Account.h"

#include <trantor/utils/Date.h>

#include <unordered_map>

void Account::signup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    Json::Value json;

    LOG_DEBUG << "User is trying to register";

    // id ?
    std::string login = req->getParameter("login");
    std::string password = req->getParameter("password");
    std::string email = req->getParameter("email");
    trantor::Date date = trantor::Date::date();
    std::string creation_date = date.toDbString();
    bool is_logged_in = 0;

    std::unordered_map<std::string, std::string> db_field;
    db_field["login"] = login;
    db_field["password"] = password;
    db_field["email"] = email;
    db_field["creation_date"] = creation_date;
    db_field["logged_in"] = is_logged_in;
    // serialize
    // GO TO DB and register

    json["status"] = "ok";
    json["message"] = "registeted " + login;
    json["email"] = email;
    json["creation_date"] = creation_date;

    LOG_DEBUG << "User " << login << "registered successfully";

    auto response = HttpResponse::newHttpJsonResponse(json);
    response->setStatusCode(HttpStatusCode::k200OK);
    callback(response);
}

void Account::login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    // Authentication algorithm, read database, verify, identify, etc...
    //...

    std::string login = req->getParameter("login");
    std::string password = req->getParameter("password");

    LOG_DEBUG << "User " << login << " trying to log in";
    Json::Value json;

    // GO TO DB AND CHECK LOGIN&PASSW

    bool is_logged_in = 1;

    json["status"] = "ok";
    json["message"] = "got verification";
    json["token"] =
        drogon::utils::base64Encode(reinterpret_cast<const unsigned char *>(login.c_str()), login.size());
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(HttpStatusCode::k200OK);
    LOG_DEBUG << "User " << login << " logged in successfully";
    callback(resp);
}

void Account::logout(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    LOG_DEBUG << "User is trying to log out";

    bool is_logged_in = 0;

    // WRITE TO DB

    Json::Value json;
    json["status"] = "ok";
    json["message"] = "log out: success";
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(HttpStatusCode::k200OK);
    LOG_DEBUG << "User logged out successfully";
    callback(resp);
}

void Account::settings(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    // Verify the validity of the token, etc.
    // Read the database or cache to get user information

    // also post/put/patch to edit profile settings

    Json::Value json;
    auto request_body = req->getJsonObject();
    std::string login, first_name, last_name, creative_fields, creation_date, birthday, gender;

    if (req->getMethod() == HttpMethod::Get) {
        LOG_DEBUG << "User " << login << " is getting his account settings";

        // first_name = ... , etc

        // json["first_name"] = first_name
        json["status"] = "ok";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        callback(resp);
    } else if (req->getMethod() == HttpMethod::Post) {
        LOG_DEBUG << "User " << login << " is trying to define account settings";

        //...
        // check if cluster is in db, birth date format

        json["status"] = "ok";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        callback(resp);
    } else if (req->getMethod() == HttpMethod::Patch) {
        LOG_DEBUG << "User " << login << " is trying to edit account settings";

        if (request_body->isMember("login")) {
            std::string new_login = req->getParameter("login");
            // go to db and change login
            //  ...
        }

        json["status"] = "ok";
        json["message"] = "settings fields have been edited";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        callback(resp);
    }
    // groups and posts in separate endpoint
}

void Account::resume(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string user_id) {
    LOG_DEBUG << "User " << user_id << " get his resume";

    Json::Value json;
    json["status"] = HttpStatusCode::k200OK;
    json["description"] = "resume description";
    json["content"] = "resume content";
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}

void Account::groups(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string user_id) {
    LOG_DEBUG << "User " << user_id << " get his groups";
    Json::Value json;

    if (req->getMethod() == HttpMethod::Get) {
        json["status"] = HttpStatusCode::k200OK;
        json["groups_list_description"] = "group's list page";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        callback(resp);
    } else if (req->getMethod() == HttpMethod::Post) {
        auto request_body = req->getJsonObject();
        // go to db
        // group_name = request_body->get("group_name").asString()
        json["message"] = "edited group list";
        json["status"] = HttpStatusCode::k200OK;
        auto resp = HttpResponse::newHttpJsonResponse(json);
        callback(resp);
    }
}

// acc/settings
// acc/resume/group
