#ifndef ZCL_COMMON_COMMANDS_HPP
#define ZCL_COMMON_COMMANDS_HPP

#include <functional>
#include <map>
#include <string>

#include "iostream"
#include "zcl/common/zcl_status.hpp"

namespace zcl
{
using command_id_t = uint8_t;

struct command_descriptor_t
{
  // Static attributes to fill from cluster descriptors
  const command_id_t id;
  const bool         is_common;
  const bool         is_mandatory;
  const std::string  description;

  // Custom comparison operator for command_descriptor_t as a key in std::map
  bool operator<(const command_descriptor_t& other) const
  {
    return id < other.id;
  }
};

class CommandBase
{
 public:
  virtual ~CommandBase() = default;
};

template <typename... Args>
class Command : public CommandBase
{
  using exec_t = ZclStatus (*)(Args...);

 public:
  Command(exec_t exec) : exec_(exec) {}

  ZclStatus operator()(Args... args) const
  {
    if (exec_ == nullptr)
    {
      std::cout << "Command operator() exec_ == nullptr" << std::endl;
      return ZclStatus::null_pointer;
    }

    std::cout << "Command operator()" << exec_ << std::endl;
    return exec_(args...);
  }

  exec_t exec_;
};

using commands_map_t = std::map<command_descriptor_t, const CommandBase* const>;
}  // namespace zcl

#endif  // ZCL_COMMON_COMMANDS_HPP
