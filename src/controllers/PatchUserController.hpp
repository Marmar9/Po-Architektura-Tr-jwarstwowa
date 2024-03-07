#pragma once
#include "../repositories/UserRepository.h"
#include <memory>

class PatchUserController {
public:
  PatchUserController(std::shared_ptr<UserRepository> repository)
      : repository(repository) {}
  void updateUser(User newUser, int id);

private:
  std::shared_ptr<UserRepository> repository;
};
