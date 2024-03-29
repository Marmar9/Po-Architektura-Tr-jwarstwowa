#include "../../src/controllers/GetUsersController.hpp"
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

class TestGetUsersController : public ::testing::Test {
protected:
  TestGetUsersController()
      : controller(std::make_shared<MockUserRepository>()){};

  void SetUp() override {
    repository = std::make_shared<MockUserRepository>();

    EXPECT_CALL(*repository, getUsers()).Times(1);

    controller = GetUsersController(repository);
  }

  void TearDown() override {
    ::testing::Mock::VerifyAndClearExpectations(repository.get());
  }
  std::shared_ptr<MockUserRepository> repository;
  GetUsersController controller;
};

TEST_F(TestGetUsersController, GetUsers) {

  ASSERT_EQ(controller.getUsers().size(), 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
