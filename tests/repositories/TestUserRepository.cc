#include "../../src/repositories/UserRepository.h"
#include <gtest/gtest.h>

class TestUserRepository : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}

  UserRepository userRepository;
};

TEST_F(TestUserRepository, AddUser) {
  //  UserRepository UserRepository;
  User newUser;
  newUser.id = 11;
  newUser.firstName = "John";
  newUser.lastName = "Doe";
  newUser.age = 30;
  newUser.group = "Group1";
  userRepository.addUser(newUser);

  ASSERT_EQ(userRepository.getUsers().size(), 11);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
