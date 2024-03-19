#include "../../src/repositories/UserRepository.h"
#include <gtest/gtest.h>

class TestUserRepository : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
  UserRepository userRepository;
};

TEST_F(TestUserRepository, AddUser) {
  // Add new user
  User newUser;
  newUser.id = 11;
  newUser.firstName = "John";
  newUser.lastName = "Doe";
  newUser.age = 30;
  newUser.group = "Group1";
  userRepository.addUser(newUser);
  ASSERT_EQ(userRepository.getUsers().size(), 2);
}

TEST_F(TestUserRepository, GetUsers) {
  // Get Users
  ASSERT_EQ(userRepository.getUsers().size(), 1);
}

TEST_F(TestUserRepository, GetUser) {
  // Get User
  ASSERT_EQ(sizeof(userRepository.getUser(1)), sizeof(User));
}

TEST_F(TestUserRepository, GetUserThatDoesNotExist) {
  //  Get User that does not exits
  EXPECT_THROW(userRepository.getUser(222), std::runtime_error);
}

TEST_F(TestUserRepository, DeleteUser) {
  // Delete User
  userRepository.deleteUser(1);
  ASSERT_EQ(userRepository.getUsers().size(), 0);
}

TEST_F(TestUserRepository, DeleteUserThatDoesNotExist) {
  // Delete User that not exist
  EXPECT_THROW(userRepository.deleteUser(15), std::runtime_error);
}

TEST_F(TestUserRepository, UpdateUser) {
  // Update user
  User newUser{-1, "Jane", "Doe", 35, "user"};
  userRepository.updateUser(1, newUser);
  ASSERT_EQ(userRepository.getUser(1).firstName, "Jane");
}

TEST_F(TestUserRepository, UpdateUserThatDoesNotExist) {
  // Update User that does not exist
  const int userId = 123;
  User newUser;
  EXPECT_THROW(userRepository.updateUser(userId, newUser), std::runtime_error);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
