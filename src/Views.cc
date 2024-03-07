#include "Views.hpp"
#include "controllers/DeleteUserController.hpp"
#include "controllers/GetUserController.hpp"
#include "controllers/GetUsersController.hpp"
#include "controllers/PostUserController.hpp"
#include "drogon/HttpTypes.h"
#include <iostream>
#include <json/json.h>
#include <json/value.h>

#include <nlohmann/json-schema.hpp>
#include <nlohmann/json.hpp>
#include <random>

#define SEND_JSON_RESPONSE                                                     \
  [&callback](std::string responseBody) {                                      \
    auto response = drogon::HttpResponse::newHttpResponse();                   \
    response->setStatusCode(drogon::HttpStatusCode::k200OK);                   \
    response->addHeader("Content-Type", "application/json");                   \
    response->setBody(responseBody);                                           \
    callback(response);                                                        \
  }

int get_random_int_id(int min_value, int max_value) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<int> distrib(min_value, max_value);

  int random_int = distrib(gen);
  return random_int;
}

void Views::handleDeleteUser(
    [[maybe_unused]] const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback, int id) {

  DeleteUserController controller = DeleteUserController(this->repository);

  try {
    controller.deleteUser(id);

    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(drogon::HttpStatusCode::k200OK);

    callback(response);
    return;
  } catch (std::runtime_error &) {

    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(drogon::k400BadRequest);
    response->setBody("Bad Request");
    callback(response);
    return;
  }
}

void Views::handlePostUser(
    const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback) {

  std::string body = std::string(req->body());
  std::cout << body << std::endl;

  nlohmann::json user_schema = R"({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "A person",
    "properties": {
        "age": {
            "description": "Age of the person",
            "type": "number",
            "minimum": 1,
            "maximum": 200
        },
        "firstName": {
            "description": "Name",
            "type": "string"
        },
        "lastName": {
            "description": "Last name of the person",
            "type": "string"
        },
        "group": {
            "description": "Group of user",
            "type": "string",
            "enum": ["user", "premium", "admin"]
        }
    },
    "required": [
        "age",
        "firstName",
        "lastName",
        "group"
    ],
    "type": "object"
})"_json;

  nlohmann::json_schema::json_validator validator; // create validator
  validator.set_root_schema(user_schema);          // insert root-schema

  try {
    nlohmann::json jsonBody = nlohmann::json::parse(body);
    // ---
    try {
      validator.validate(jsonBody);
      // ---
    } catch (const std::exception &) {
      auto response = drogon::HttpResponse::newHttpResponse();
      response->setStatusCode(drogon::k400BadRequest);
      response->setBody("Wrong Format");
      callback(response);
      return;
    }

    User newUser;
    newUser.id = get_random_int_id(1, 1000);
    newUser.age = jsonBody["age"].get<int>();
    newUser.firstName = jsonBody["firstName"].get<std::string>();
    newUser.lastName = jsonBody["lastName"].get<std::string>();
    newUser.group = jsonBody["group"].get<std::string>();

    PostUserController controller = PostUserController(this->repository);

    controller.addUser(newUser);

    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(drogon::HttpStatusCode::k200OK);
    response->setBody("Test1-OK");
    callback(response);

  } catch (std::runtime_error &) {
    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(drogon::k400BadRequest);
    response->setBody("Wrong Format");
    callback(response);
    return;
  }
}

void Views::handleGetUser(
    [[maybe_unused]] const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    int id) const {

  GetUserController controller = GetUserController(this->repository);

  try {
    User user = controller.getUser(id);

    nlohmann::json jsonUser;
    jsonUser["id"] = user.id;
    jsonUser["firstName"] = user.firstName;
    jsonUser["lastName"] = user.lastName;
    jsonUser["age"] = user.age;
    jsonUser["group"] = user.group;

    SEND_JSON_RESPONSE(jsonUser.dump());
    return;
  } catch (std::runtime_error &) {

    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(drogon::k400BadRequest);
    response->setBody("Bad Request");
    callback(response);
    return;
  }
}

void Views::handleGetUsers(
    [[maybe_unused]] const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback) const {

  GetUsersController controller = GetUsersController(this->repository);

  std::vector<User> userVector = controller.getUsers();

  // Json::Value jsonResponse = Json::Value(Json::arrayValue);

  // for (const auto &user : userVector) {
  //   Json::Value jsonUser;
  //   jsonUser["id"] = user.id;
  //   jsonUser["firstName"] = user.firstName;
  //   jsonUser["lastName"] = user.lastName;
  //   jsonUser["age"] = user.age;
  //   jsonUser["group"] = user.group;
  //   jsonResponse.append(jsonUser);
  // };

  nlohmann::json jsonResponse = nlohmann::json::array();
  for (const auto &user : userVector) {
    nlohmann::json jsonUser;
    jsonUser["id"] = user.id;
    jsonUser["firstName"] = user.firstName;
    jsonUser["lastName"] = user.lastName;
    jsonUser["age"] = user.age;
    jsonUser["group"] = user.group;
    jsonResponse.push_back(jsonUser);
  }

  //  auto response =
  //      drogon::HttpResponse::newHttpJsonResponse(jsonResponse.dump());

  SEND_JSON_RESPONSE(jsonResponse.dump());
}
