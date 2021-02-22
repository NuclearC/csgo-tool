
#ifndef NC_CSGOTOOL_CONFIG_CONFIG_HPP_
#define NC_CSGOTOOL_CONFIG_CONFIG_HPP_

#include <map>
#include <memory>
#include <vector>

#include "config/confvar.hpp"
#include "nlohmann/json.hpp"

namespace nc {
namespace config {

class ConfigHolder {
 private:
  std::vector<ConfVar> confvars_;

 public:
  void RegisterConfVar(const ConfVar& confvar);

  const ConfVar FindByName(const std::string& name);
  const ConfVar FindByNameType(const std::string& name, ConfVarType type);

  const std::vector<ConfVar>& GetAllConfVars();

  void WriteConfVarToJSON(nlohmann::json& out, const std::string& name,
                          const ConfVar& confvar);

  void WriteConfVarToJSON(nlohmann::json& out,
                          const std::vector<std::string>& path,
                          int path_start_idx, const ConfVar& confvar);

  void ReadConfVarFromJSON(const nlohmann::json& in,
                           const std::vector<std::string>& path,
                           int path_start_idx, ConfVar& confvar);
  void ReadConfVarFromJSON(const nlohmann::json& in, const std::string& name,
                           ConfVar& confvar);

  void SaveToJSON(nlohmann::json& out);
  void LoadFromJSON(const nlohmann::json& in);

  static std::unique_ptr<ConfigHolder>& GetInstance();
};

}  // namespace config
}  // namespace nc

#endif  // NC_CSGOTOOL_CONFIG_CONFIG_HPP_
