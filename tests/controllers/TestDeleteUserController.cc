#include "../../src/controllers/DeleteUserController.hpp"
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

class TestDeleteUserController : public ::testing::Test {
protected:
  TestDeleteUserController()
      : controller(std::make_shared<MockUserRepository>()){};

  void SetUp() override {
    repository = std::make_shared<MockUserRepository>();

    EXPECT_CALL(*repository, deleteUser(1)).Times(1);

    controller = DeleteUserController(repository);
  }

  void TearDown() override {
    ::testing::Mock::VerifyAndClearExpectations(repository.get());
  }
  std::shared_ptr<MockUserRepository> repository;
  DeleteUserController controller;
};

TEST_F(TestDeleteUserController, DeleteUser) { controller.deleteUser(1); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
