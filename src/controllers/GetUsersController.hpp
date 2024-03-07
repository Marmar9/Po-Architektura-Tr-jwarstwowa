#pragma once
#include "../User.h"
#include "../repositories/UserRepository.h"
#include <json/json.h>
#include <json/value.h>
#include <vector>

class GetUsersController {
public:
  GetUsersController(std::shared_ptr<UserRepository> repository);
  std::vector<User> getUsers();

private:
  std::shared_ptr<UserRepository> repository;
};
