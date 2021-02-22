
#ifndef NC_CSGOTOOL_FEATUREGROUP_HPP_
#define NC_CSGOTOOL_FEATUREGROUP_HPP_

#include <memory>

#include "feature.hpp"

namespace nc {

class FeatureGroup : public std::enable_shared_from_this<FeatureGroup>,
                     public Feature {
 protected:
 private:
 public:
  FeatureGroup(const std::string& name);
  ~FeatureGroup();
};

}  // namespace nc

#endif  // NC_CSGOTOOL_FEATUREGROUP_HPP_
