#include "DeleteUserController.hpp"

void DeleteUserController::deleteUser(int id) {
  try {
    this->repository->getUser(id);
    this->repository->deleteUser(id);
  } catch (std::runtime_error) {
    throw std::runtime_error("User not found");
  }
}
