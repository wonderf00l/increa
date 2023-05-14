#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Account : public drogon::HttpController<Account> {
   public:
    void signup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void settings(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void resume(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                std::string user_id);

    void groups(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                std::string user_id);

    METHOD_LIST_BEGIN
    METHOD_ADD(Account::signup, "/signup", Post, "empty_body_filter", "signup_filter");
    METHOD_ADD(Account::login, "/login", Post, "empty_body_filter");  // url: /account/login
    METHOD_ADD(Account::settings, "/settings/", Post, Get,
               "auth_filter");  // /account/{account_id}/settings?token=tok
    METHOD_ADD(Account::resume, "/{1}/resume", Get, "auth_filter");
    METHOD_ADD(Account::groups, "/{1}/groups", Get, "auth_filter");
    METHOD_LIST_END
};
