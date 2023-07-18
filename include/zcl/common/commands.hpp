#ifndef ZCL_COMMON_COMMANDS_HPP
#define ZCL_COMMON_COMMANDS_HPP

#include <functional>
#include <map>
#include <string>
#include <utility>

#include "iostream"
#include "zcl/common/zcl_status.hpp"

namespace zcl
{
using command_id_t = uint8_t;

class CommandDescriptor
{
  // Static attributes to fill from cluster descriptors
  command_id_t id;
  bool         is_common;
  bool         is_mandatory;
  std::string  description;

 public:
  // Custom comparison operator for command_descriptor_t as a key in std::map
  bool operator<(const CommandDescriptor& other) const { return id < other.id; }

  CommandDescriptor(command_id_t cmd_id, bool is_common, bool is_mandatory,
                    std::string description)
      : id(cmd_id),
        is_common(is_common),
        is_mandatory(is_mandatory),
        description(std::move(description))
  {
  }

  [[nodiscard]] bool check_match(command_id_t cmd_id, bool is_common) const
  {
    return id == cmd_id && this->is_common == is_common;
  }

  // ID getter
  [[nodiscard]] command_id_t get_id() const { return id; }

  // Get description
  [[nodiscard]] const std::string& get_description() const
  {
    return description;
  }
};
}  // namespace zcl

#endif  // ZCL_COMMON_COMMANDS_HPP
