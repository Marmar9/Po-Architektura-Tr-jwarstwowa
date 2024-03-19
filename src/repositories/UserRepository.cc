#include "UserRepository.h"
#include <mutex>
#include <stdexcept>
#include <vector>
UserRepository::UserRepository() {

  for (int i = 0; i < 1; ++i) {
    User newUser;
    newUser.id = i + 1;
    newUser.firstName = "Firstnamaa" + std::to_string(i);
    newUser.lastName = "Last" + std::to_string(i);
    newUser.age = 1990 + i;
    newUser.group = "Group" + std::to_string(i);
    this->usersArray.push_back(newUser);
  }
}

void UserRepository::deleteUser(int id) {

  std::unique_lock<std::shared_mutex> lock(this->mutex);

  for (auto it = usersArray.begin(); it != usersArray.end(); ++it) {
    if (it->id == id) {
      usersArray.erase(it);
      return;
    }
  }

  throw std::runtime_error("User does not exist");
}

void UserRepository::addUser(User newUser) {

  std::unique_lock<std::shared_mutex> lock(this->mutex);
  usersArray.push_back(newUser);
}

void UserRepository::updateUser(int id, User newUser) {
  std::unique_lock<std::shared_mutex> lock(this->mutex);
  for (User &user : usersArray) {
    if (user.id == id) {
      newUser.id = id;
      user = newUser;
      return;
    }
  }

  throw std::runtime_error("User does not exist");
}
User UserRepository::getUser(int id) const {

  std::shared_lock<std::shared_mutex> lock(this->mutex);

  for (User user : usersArray) {
    if (user.id == id) {
      return user;
    }
  }
  throw std::runtime_error("User does not exist");
}

std::vector<User> UserRepository::getUsers() const {

  std::shared_lock<std::shared_mutex> lock(this->mutex);
  return usersArray;
}
