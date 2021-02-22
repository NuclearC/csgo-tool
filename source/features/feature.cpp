
#include "feature.hpp"

#include "config/config.hpp"
#include "config/confvar.hpp"
#include "featuregroup.hpp"

namespace nc {

void Feature::Config(const std::string& varname, config::ConfVarType type,
                     void* ptr, std::size_t buflen) {
  using namespace config;

  if (GetParent() != nullptr) {
    const auto parent_name = GetParent()->GetName();
    const auto full_name = parent_name + "." + name_ + "." + varname;
    ConfigHolder::GetInstance()->RegisterConfVar(
        ConfVar(full_name, type, ptr, buflen));
  } else {
    ConfigHolder::GetInstance()->RegisterConfVar(
        ConfVar(name_ + "." + varname, type, ptr, buflen));
  }
}

Feature::Feature(const std::string& name,
                 const std::shared_ptr<FeatureGroup>& parent)
    : name_(name), parent_(parent) {}
Feature::~Feature() {}

std::shared_ptr<FeatureGroup> Feature::GetParent() { return parent_; }
const std::string& Feature::GetName() const { return name_; }

}  // namespace nc
