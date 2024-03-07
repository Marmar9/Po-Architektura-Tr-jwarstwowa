#pragma once
#include "../repositories/UserRepository.h"
#include <memory>

class PostUserController {

public:
  PostUserController(std::shared_ptr<UserRepository> repository)
      : repository(repository) {}

  void addUser(User newUser);

private:
  std::shared_ptr<UserRepository> repository;
};
