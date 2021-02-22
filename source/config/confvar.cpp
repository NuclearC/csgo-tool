
#include "confvar.hpp"

namespace nc {
namespace config {

ConfVar::ConfVar(const std::string& fullname, ConfVarType type, void* ptr,
                 std::size_t buflen)
    : fullname_(fullname), type_(type), ptr_(ptr), buflen_(buflen) {}
ConfVar::~ConfVar() {}

const ConfVarType ConfVar::GetType() const { return type_; }
const std::string& ConfVar::GetName() const { return fullname_; }
void* ConfVar::GetPtr() const { return ptr_; }
const std::size_t ConfVar::GetLen() const { return buflen_; }

std::vector<std::string> ConfVar::GetPath() const {
  std::vector<std::string> res;
  std::string tmp = fullname_;
  std::size_t last = 0, cur = 0;

  while ((cur = tmp.find('.', last)) != tmp.npos) {
    res.push_back(tmp.substr(last, cur - last));
    last = cur + 1;
  }

  res.push_back(tmp.substr(last));

  return res;
}

}  // namespace config
}  // namespace nc
