#include "zcl/common/command_descriptor.hpp"

namespace zcl
{
bool CommandDescriptor::operator<(const CommandDescriptor& other) const
{
  return id < other.id;
}

CommandDescriptor::CommandDescriptor(command_id_t cmd_id, bool is_common,
                                     bool is_mandatory, std::string description)
    : id(cmd_id),
      is_common(is_common),
      is_mandatory(is_mandatory),
      description(std::move(description))
{
}

bool CommandDescriptor::check_match(command_id_t cmd_id, bool is_common) const
{
  return id == cmd_id && this->is_common == is_common;
}

command_id_t CommandDescriptor::get_id() const { return id; }

const std::string& CommandDescriptor::get_description() const
{
  return description;
}

}  // namespace zcl
