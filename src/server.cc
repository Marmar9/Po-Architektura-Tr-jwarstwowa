#include "Views.hpp"
#include <drogon/HttpAppFramework.h>
#include <drogon/drogon.h>
int main() {
  std::cout << "Server running on port localhost:8080" << std::endl;

  std::shared_ptr<UserRepository> repository =
      std::make_shared<UserRepository>();

  drogon::app()
      .loadConfigFile("config.json")
      .registerController(std::make_shared<Views>(repository))
      .run();

  return 0;
}
