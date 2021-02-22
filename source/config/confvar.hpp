
#ifndef NC_CSGOTOOL_CONFIG_CONFVAR_HPP_
#define NC_CSGOTOOL_CONFIG_CONFVAR_HPP_

#include <string>
#include <vector>

namespace nc {
namespace config {

enum class ConfVarType { kInt32, kUInt32, kFloat, kString, kBinaryBlob };

// ConfVar - adds the ability to store certain settings
// in the Json file
class ConfVar {
 private:
  std::string fullname_;
  ConfVarType type_;
  void* ptr_;
  std::size_t buflen_;

 public:
  ConfVar(const std::string& fullname, ConfVarType type, void* ptr,
          std::size_t buflen = 0);
  ~ConfVar();

  const ConfVarType GetType() const;
  const std::string& GetName() const;
  void* GetPtr() const;
  const std::size_t GetLen() const;

  std::vector<std::string> GetPath() const;
};

}  // namespace config
}  // namespace nc

#endif  // NC_CSGOTOOL_CONFIG_CONFVAR_HPP_
