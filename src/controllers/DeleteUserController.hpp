#pragma once
#include "../repositories/UserRepository.h"
#include <memory>
class DeleteUserController {
public:
  DeleteUserController(std::shared_ptr<UserRepository> repository)
      : repository(repository) {}

  void deleteUser(int id);

private:
  std::shared_ptr<UserRepository> repository;
};
