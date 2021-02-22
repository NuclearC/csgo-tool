
#ifndef NC_CSGOTOOL_FEATURE_HPP_
#define NC_CSGOTOOL_FEATURE_HPP_

#include <memory>
#include <string>

#include "config/confvar.hpp"

namespace nc {

class FeatureGroup;

// interface class Feature (IFeature)
class Feature {
 private:
  std::shared_ptr<FeatureGroup> parent_;

 protected:
  const std::string name_;

  void Config(const std::string& varname, config::ConfVarType type, void* ptr,
              std::size_t buflen = 0);

 public:
  Feature(const std::string& name, const std::shared_ptr<FeatureGroup>& parent);
  ~Feature();

  const std::string& GetName() const;
  virtual std::shared_ptr<FeatureGroup> GetParent();
};

typedef Feature IFeature;

}  // namespace nc

#endif  // NC_CSGOTOOL_FEATURE_HPP_
