#include "GetUsersController.hpp"
#include <vector>

GetUsersController::GetUsersController(
    std::shared_ptr<UserRepository> repository)
    : repository(repository) {}

std::vector<User> GetUsersController::getUsers() {
  return this->repository->getUsers();
}
