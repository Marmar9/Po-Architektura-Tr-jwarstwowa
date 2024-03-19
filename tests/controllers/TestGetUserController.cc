#include "../../src/controllers/GetUserController.hpp"
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

class TestGetUserController : public ::testing::Test {
protected:
  TestGetUserController()
      : controller(std::make_shared<MockUserRepository>()){};

  void SetUp() override {
    repository = std::make_shared<MockUserRepository>();

    EXPECT_CALL(*repository, deleteUser(1)).Times(1);

    controller = GetUserController(repository);
  }

  void TearDown() override {
    ::testing::Mock::VerifyAndClearExpectations(repository.get());
  }
  std::shared_ptr<MockUserRepository> repository;
  GetUserController controller;
};

TEST_F(TestGetUserController, GetUser) { controller.getUser(1); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
