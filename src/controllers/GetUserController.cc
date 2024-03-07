#include "GetUserController.hpp"
#include <stdexcept>

User GetUserController::getUser(int id) {
  try {
    User user = this->repository->getUser(id);
    return user;
  } catch (std::runtime_error) {
    throw std::runtime_error("User not found");
  }
  return this->repository->getUser(id);
}
