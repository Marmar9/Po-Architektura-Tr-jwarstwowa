#include "../../src/controllers/PostUserController.hpp"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

class MockUserRepository : public UserRepository {
public:
  MOCK_METHOD0(UserRepository, void());
  MOCK_METHOD1(deleteUser, void(int));
  MOCK_METHOD1(addUser, void(const User &));
  MOCK_METHOD2(updateUser, void(int, const User &));
  MOCK_CONST_METHOD1(getUser, User(int));
  MOCK_CONST_METHOD0(getUsers, std::vector<User>());
};

class TestPostUserController : public ::testing::Test {
protected:
  TestPostUserController()
      : controller(std::make_shared<MockUserRepository>()){};

  void SetUp() override {
    repository = std::make_shared<MockUserRepository>();

    User newUser{1, "Jane", "Doe", 35, "user"};

    EXPECT_CALL(*repository, addUser(newUser)).Times(1);

    controller = PostUserController(repository);
  }

  void TearDown() override {
    ::testing::Mock::VerifyAndClearExpectations(repository.get());
  }
  std::shared_ptr<MockUserRepository> repository;
  PostUserController controller;
};

TEST_F(TestPostUserController, PatchUser) {

  User newUser{-1, "Jane", "Doe", 35, "user"};

  controller.addUser(newUser);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
