#include "PostUserController.hpp"

void PostUserController::addUser(User newUser) {
  this->repository->addUser(newUser);
}
