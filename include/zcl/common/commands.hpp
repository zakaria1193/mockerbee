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

class CommandBase
{
 public:
  CommandBase()          = default;
  virtual ~CommandBase() = default;

  // cppcoreguidelines-special-member-functions implies these definitions:
  CommandBase(const CommandBase&)            = delete;
  CommandBase& operator=(const CommandBase&) = delete;
  CommandBase(CommandBase&&)                 = delete;
  CommandBase& operator=(CommandBase&&)      = delete;
};

template <typename... Args>
class Command : public CommandBase
{
  using exec_t = ZclStatus (*)(Args...);
  exec_t exec_;

 public:
  explicit Command(exec_t exec) : exec_(exec) {}

  ZclStatus operator()(Args... args) const
  {
    if (exec_ == nullptr)
    {
      std::cout << "Command operator() exec_ == nullptr" << '\n';
      return ZclStatus::null_pointer;
    }

    std::cout << "Command operator()" << exec_ << '\n';
    return exec_(args...);
  }
};

using command_generic_ptr_t = const CommandBase* const;


using commands_map_t = std::map<CommandDescriptor, command_generic_ptr_t>;

/**
 * @brief Emplace command into commands map
 *
 * @tparam Args
 * @param commands_map
 * @param cmd_descriptor
 * @param cmd
 */
template <typename... Args>
constexpr void emplace_command(commands_map_t& commands_map,
                               const CommandDescriptor& cmd_descriptor,
                               std::function<ZclStatus(Args...)> cmd)
{

  commands_map.emplace(cmd_descriptor, new Command<Args...>(cmd)); 
}

}  // namespace zcl

#endif  // ZCL_COMMON_COMMANDS_HPP
