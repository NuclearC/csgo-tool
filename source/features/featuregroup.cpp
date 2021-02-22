
#include "featuregroup.hpp"

namespace nc {

FeatureGroup::FeatureGroup(const std::string& name)
    : nc::Feature(name, nullptr) {}
FeatureGroup::~FeatureGroup() {}

}  // namespace nc
