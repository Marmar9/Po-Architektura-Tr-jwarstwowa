#include "PatchUserController.hpp"

void PatchUserController::updateUser(User newUser, int id) {
  this->repository->updateUser(id, newUser);
}
