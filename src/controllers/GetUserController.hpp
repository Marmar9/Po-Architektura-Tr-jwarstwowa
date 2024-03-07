#pragma once
#include "../repositories/UserRepository.h"
#include <memory>

class GetUserController {
public:
  GetUserController(std::shared_ptr<UserRepository> repository)
      : repository(repository) {}

  User getUser(int id);

private:
  std::shared_ptr<UserRepository> repository;
};
