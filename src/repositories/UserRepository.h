
#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H
#include "../User.h"
#include <shared_mutex>
#include <vector>
class UserRepository {
private:
  std::vector<User> usersArray;
  mutable std::shared_mutex mutex;

public:
  UserRepository();
  User getUser(int id) const;
  std::vector<User> getUsers() const;
  void addUser(User newUser);
  void updateUser(int id, User newUser);
  void deleteUser(int id);
};
#endif // !USER_REPOSITORY_H
