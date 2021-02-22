#include "main.hpp"

#include <iostream>

#include "config/config.hpp"
#include "features/feature.hpp"
#include "features/featuregroup.hpp"

#define NOMINMAX
#include <windows.h>

class Test : private nc::Feature {
  using ConfType = nc::config::ConfVarType;

 private:
  int some_int_;
  float some_float_;
  std::string some_string_;

 public:
  Test(const std::shared_ptr<nc::FeatureGroup>& parent_)
      : nc::Feature("Test", parent_) {
    Config("SomeInt", ConfType::kInt32, &some_int_);
    Config("SomeFloat", ConfType::kFloat, &some_float_);
    Config("SomeString", ConfType::kString, &some_string_);

    Config("binaryData", ConfType::kBinaryBlob, &some_float_, sizeof(float));

    some_int_ = 2;
    some_float_ = 32.4f;
    some_string_ = "adfnasdfasdf";
  }
  ~Test() {}
};

class Test2 : private nc::Feature {
  using ConfType = nc::config::ConfVarType;

 private:
  int some_int_;
  float some_float_;
  std::string some_string_;

 public:
  Test2(const std::shared_ptr<nc::FeatureGroup>& parent_)
      : nc::Feature("Test2", parent_) {
    Config("SomeInt", ConfType::kInt32, &some_int_);
    Config("SomeFloat44", ConfType::kFloat, &some_float_);
    Config("SomeString52", ConfType::kString, &some_string_);

    some_int_ = 5;
    some_float_ = 111.430f;
    some_string_ = "dadsadasdasd";
  }
  ~Test2() {}
};

class TestGroup : public nc::FeatureGroup {
  using ConfType = nc::config::ConfVarType;

 private:
  std::unique_ptr<Test> t1;
  std::unique_ptr<Test2> t2;

 public:
  TestGroup() : nc::FeatureGroup("TestGroup") {}
  void Init() {
    t1 = std::make_unique<Test>(shared_from_this());
    t2 = std::make_unique<Test2>(shared_from_this());
  }
};

int main() {
  using namespace nc;
  using namespace nc::config;

  std::shared_ptr<TestGroup> group = std::make_shared<TestGroup>();
  group->Init();

  nlohmann::json out;
  ConfigHolder::GetInstance()->SaveToJSON(out);
  std::cout << out.dump(2) << std::endl;

  return 0;
}

//
// BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
//  switch (fdwReason) {
//    case DLL_PROCESS_ATTACH:
//      break;
//    case DLL_THREAD_ATTACH:
//      break;
//    case DLL_THREAD_DETACH:
//      break;
//    case DLL_PROCESS_DETACH:
//      break;
//  }
//  return TRUE;
//}
