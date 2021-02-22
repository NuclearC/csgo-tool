
#include "config.hpp"

#include "cppcodec/base64_rfc4648.hpp"

namespace nc {
namespace config {

static std::unique_ptr<ConfigHolder> configholder_instance_ = nullptr;

void ConfigHolder::RegisterConfVar(const ConfVar& confvar) {
  confvars_.push_back(confvar);
}

const ConfVar ConfigHolder::FindByName(const std::string& name) {
  for (auto& confvar : confvars_) {
    if (name == confvar.GetName()) return confvar;
  }
  return ConfVar("null", ConfVarType::kInt32, nullptr, 0);
}

const ConfVar ConfigHolder::FindByNameType(const std::string& name,
                                           ConfVarType type) {
  for (auto& confvar : confvars_) {
    if (name == confvar.GetName() && type == confvar.GetType()) return confvar;
  }
  return ConfVar("null", ConfVarType::kInt32, nullptr, 0);
}

const std::vector<ConfVar>& ConfigHolder::GetAllConfVars() { return confvars_; }

std::unique_ptr<ConfigHolder>& ConfigHolder::GetInstance() {
  if (configholder_instance_ == nullptr) {
    configholder_instance_ = std::make_unique<ConfigHolder>();
  }

  return configholder_instance_;
}

void ConfigHolder::WriteConfVarToJSON(nlohmann::json& out,
                                      const std::string& name,
                                      const ConfVar& confvar) {
  switch (confvar.GetType()) {
    case ConfVarType::kInt32: {
      std::int32_t* iptr = reinterpret_cast<std::int32_t*>(confvar.GetPtr());
      out[name] = *iptr;
    } break;
    case ConfVarType::kUInt32: {
      std::uint32_t* uiptr = reinterpret_cast<std::uint32_t*>(confvar.GetPtr());
      out[name] = *uiptr;
    } break;
    case ConfVarType::kFloat: {
      float* fptr = reinterpret_cast<float*>(confvar.GetPtr());
      out[name] = *fptr;
    } break;
    case ConfVarType::kBinaryBlob: {
      if (confvar.GetLen() > 0x7ff) {
        break;
      }
      out[name] = cppcodec::base64_rfc4648::encode(
          reinterpret_cast<const char*>(confvar.GetPtr()), confvar.GetLen());
    } break;
    case ConfVarType::kString:
      std::string* strptr = reinterpret_cast<std::string*>(confvar.GetPtr());
      out[name] = *strptr;
      break;
  }
}

void ConfigHolder::WriteConfVarToJSON(nlohmann::json& out,
                                      const std::vector<std::string>& path,
                                      int path_start_idx,
                                      const ConfVar& confvar) {
  if (path_start_idx == static_cast<int>(path.size() - 1)) {
    WriteConfVarToJSON(out, path[path_start_idx], confvar);
  } else {
    WriteConfVarToJSON(out[path[path_start_idx]], path, path_start_idx + 1,
                       confvar);
  }
}

void ConfigHolder::ReadConfVarFromJSON(const nlohmann::json& in,
                                       const std::string& name,
                                       ConfVar& confvar) {
  const auto& item = in[name];
  switch (confvar.GetType()) {
    case ConfVarType::kInt32: {
      if (!item.is_number_integer()) break;
      std::int32_t* iptr = reinterpret_cast<std::int32_t*>(confvar.GetPtr());
      *iptr = item.get<std::int32_t>();
    } break;
    case ConfVarType::kUInt32: {
      if (!item.is_number_unsigned()) break;
      std::uint32_t* uiptr = reinterpret_cast<std::uint32_t*>(confvar.GetPtr());
      *uiptr = item.get<std::uint32_t>();
    } break;
    case ConfVarType::kFloat: {
      if (!item.is_number_float()) break;
      float* fptr = reinterpret_cast<float*>(confvar.GetPtr());
      *fptr = item.get<float>();
    } break;
    case ConfVarType::kBinaryBlob: {
      if (confvar.GetLen() > 0x7ff) {
        break;
      }
      if (!item.is_string()) break;
      auto str = item.get<std::string>();
      auto decoded = cppcodec::base64_rfc4648::decode(str);
      if (decoded.size() != confvar.GetLen()) break;

      std::memcpy(confvar.GetPtr(), decoded.data(), decoded.size());
    } break;
    case ConfVarType::kString:
      if (!item.is_string()) break;
      std::string* strptr = reinterpret_cast<std::string*>(confvar.GetPtr());
      *strptr = in.get<std::string>();
      break;
  }
}

void ConfigHolder::ReadConfVarFromJSON(const nlohmann::json& in,
                                       const std::vector<std::string>& path,
                                       int path_start_idx, ConfVar& confvar) {
  if (in.find(path[path_start_idx]) != in.end()) {
    if (path_start_idx == static_cast<int>(path.size() - 1)) {
      ReadConfVarFromJSON(in, path[path_start_idx], confvar);
    } else {
      ReadConfVarFromJSON(in, path, path_start_idx + 1, confvar);
    }
  }
}

void ConfigHolder::SaveToJSON(nlohmann::json& out) {
  for (auto& confvar : confvars_) {
    const auto path = confvar.GetPath();
    if (path.empty()) continue;
    WriteConfVarToJSON(out, path, 0, confvar);
  }
}

void ConfigHolder::LoadFromJSON(const nlohmann::json& in) {
  for (auto& confvar : confvars_) {
    const auto path = confvar.GetPath();
    if (path.empty()) continue;
    ReadConfVarFromJSON(in, path, 0, confvar);
  }
}

}  // namespace config
}  // namespace nc
