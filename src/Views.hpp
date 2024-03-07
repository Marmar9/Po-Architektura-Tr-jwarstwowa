#pragma once
#include "repositories/UserRepository.h"
#include <drogon/HttpController.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <memory>

class Views : public drogon::HttpController<Views, false> {
public:
  void
  handleGetUser(const drogon::HttpRequestPtr &req,
                std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                int id) const;

  void handleGetUsers(
      const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;

  void handlePostUser(
      const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback);

  void handleDeleteUser(
      const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback, int id);

  Views(std::shared_ptr<UserRepository> repository) : repository(repository) {}

  METHOD_LIST_BEGIN
  ADD_METHOD_TO(Views::handleGetUser, "/users/{id}", drogon::Get);
  ADD_METHOD_TO(Views::handleGetUsers, "/users", drogon::Get);
  ADD_METHOD_TO(Views::handlePostUser, "/users", drogon::Post);
  ADD_METHOD_TO(Views::handleDeleteUser, "/users/{id}", drogon::Delete);
  METHOD_LIST_END
private:
  std::shared_ptr<UserRepository> repository;
};
