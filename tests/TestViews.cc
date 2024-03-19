#include "../src/Views.hpp"
#include "drogon/HttpClient.h"
#include <drogon/drogon_test.h>
#include <gtest/gtest.h>

class ViewsTest : public ::testing::Test {
protected:
  static std::atomic<bool> serverRunning;

  virtual void SetUp() override {
    std::shared_ptr<UserRepository> repository =
        std::make_shared<UserRepository>();

    serverRunning = true;
    drogon::app().loadConfigFile("config.json");

    std::thread serverThread([repository] {
      drogon::app()
          .loadConfigFile("config.json")
          .registerController(std::make_shared<Views>(repository))
          .run();

      serverRunning = false;
    });

    serverThread.detach();
  }

  virtual void TearDown() override {
    drogon::app().quit();
    while (serverRunning) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
};

std::atomic<bool> ViewsTest::serverRunning(false);

TEST_F(ViewsTest, TestGetUsers) {

  auto client = drogon::HttpClient::newHttpClient("http://127.0.0.1:8080");

  auto req = drogon::HttpRequest::newHttpRequest();
  req->setPath("/users");

  // client->sendRequest(
  // req, [](drogon::ReqResult res, const drogon::HttpResponsePtr &resp) {});
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
