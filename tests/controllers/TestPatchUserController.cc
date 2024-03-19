#include "../../src/controllers/PatchUserController.hpp"
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

class TestPatchUserController : public ::testing::Test {
protected:
  TestPatchUserController()
      : controller(std::make_shared<MockUserRepository>()){};

  void SetUp() override {
    repository = std::make_shared<MockUserRepository>();

    User newUser{-1, "Jane", "Doe", 35, "user"};
    EXPECT_CALL(*repository, updateUser(1, newUser)).Times(1);

    controller = PatchUserController(repository);
  }

  void TearDown() override {
    ::testing::Mock::VerifyAndClearExpectations(repository.get());
  }
  std::shared_ptr<MockUserRepository> repository;
  PatchUserController controller;
};

TEST_F(TestPatchUserController, PatchUser) {

  User newUser{-1, "Jane", "Doe", 35, "user"};

  controller.updateUser(newUser, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
