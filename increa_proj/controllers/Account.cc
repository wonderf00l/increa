#include "Account.h"

#include <trantor/utils/Date.h>

void Account::signup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    Json::Value json;

    LOG_DEBUG << "User is trying to register";

    std::string login = req->getParameter("login");
    std::string password = req->getParameter("password");
    std::string email = req->getParameter("email");
    std::string creation_date = trantor::Date::toDbString();
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

    if (!(request_body->isMember("login")) || !(request_body->isMember("email"))) {
        json["status"] = "error";
        json["message"] = "missing login/email/password";

        auto response = HttpResponse::newHttpJsonResponse(json);
        response->setStatusCode(HttpStatusCode::k400BadRequest);

        callback(response);
        return;
    }

    std::string login = req->getParameter("login");
    std::string password = req->getParameter("password");

    LOG_DEBUG << "User " << login << " trying to log in";
    Json::Value json;

    // GO TO DB AND CHECK LOGIN&PASSW

    json["status"] = "ok";
    json["message"] = "got verification";
    json["token"] = drogon::utils::base64Encode(login, login.size());
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(HttpStatusCode::k200OK);
    LOG_DEBUG << "User " << login << " logged in successfully";
    callback(resp);
}

void Account::settings(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    LOG_DEBUG << "User " << user_id << " get his information";
    // Verify the validity of the token, etc.
    // Read the database or cache to get user information

    // also post/put/patch to edit profile settings

    Json::Value json;
    std::string first_name, last_name, creative_fields, creation_date, birthday, gender;


    if (req->getMethod() == HttpMethod::Get) {
        std::string login;
        // first_name = ... , etc

        //json["first_name"] = first_name
        json["status"] = "ok";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        callback(resp);
    }
    else if (req->getMethod() == HttpMethod::Post) {
        //...
        //check if cluster is in db, birth date format

        json["status"] = "ok";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        callback(resp);
    }



    // groups and posts in separate endpoint

    json["status"] = "ok";
    json["login"] = login;
    json["date of birth"] = birth_date;
    json["gender"] = gender;
    json["cluster"] = cluster;
    json["activity"] = activity;

    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(HttpStatusCode::k200OK);
    callback(resp);
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
