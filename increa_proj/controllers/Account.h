#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Account : public drogon::HttpController<Account> {
    void signup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
               std::string &&user_id, const std::string &password);

    void get_info(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                  std::string user_id, const std::string &token);

    void resume(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                std::string user_id);

    void groups(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                std::string user_id);

   public:
    METHOD_LIST_BEGIN
    METHOD_ADD(Account::signup, "/signup", Post, "empty_body_filter");
    METHOD_ADD(Account::login, "/login?userId={1}&passwd={2}",  // add filter
               Post);                                           // url: /account/login
    METHOD_ADD(Account::get_info, "/{1}/?token={2}", Get);      // /account/{account_id}/info?token=tok
    METHOD_ADD(Account::resume, "/{1}/resume", Get);
    METHOD_ADD(Account::groups, "/{1}/groups", Get);
    METHOD_LIST_END
};
