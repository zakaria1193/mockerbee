#ifndef ZCL_COMMON_CLUSTER_HPP
#define ZCL_COMMON_CLUSTER_HPP

#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <variant>

#include "attributes.hpp"
#include "commands.hpp"
#include "iostream"

namespace zcl
{
using cluster_id_t = uint16_t;

struct cluster_descriptor_t
{
  // Static attributes to fill from cluster descriptors
  const cluster_id_t id;
  const bool         is_msp;
  const std::string  description;
};

class Cluster
{
  attributes_list_t           attributes;
  const commands_map_t        commands_map;
  static const commands_map_t common_commands_map;

  static attributes_list_t create_attributes(
      const std::vector<AttributeDescriptor>& attribute_descriptors)
  {
    std::vector<Attribute> attributes;
    for (const auto& attr_desc : attribute_descriptors)
    {
      attributes.emplace_back(attr_desc);
    }
    return attributes;
  }

 public:
  // Constructor
  Cluster(cluster_descriptor_t                    descriptor,
          const std::vector<AttributeDescriptor>& attribute_descriptors,
          const commands_map_t                    commands_map)
      : descriptor(std::move(descriptor)),
        attributes(create_attributes(attribute_descriptors)),
        commands_map(commands_map)
  {
  }

  // Method to get the list of attributes
  const attributes_list_t& get_attributes() const { return attributes; }

  // Method to get the list of commands
  const commands_map_t& get_commands() const { return commands_map; }

  // Cluster descriptor
  const cluster_descriptor_t descriptor;

  // Generir attribute value

  const Attribute& get_attribute_const(const attr_id_t id) const
  {
    for (const auto& attr : attributes)
    {
      if (attr.descriptor.id == id)
      {
        return attr;
      }
    }
    throw std::runtime_error("Attribute not found");
  }

  Attribute& get_attribute_not_const(const attr_id_t id)
  {
    for (auto& attr : attributes)
    {
      if (attr.descriptor.id == id)
      {
        return attr;
      }
    }
    throw std::runtime_error("Attribute not found");
  }

  attr_value_t get_attribute_value(const attr_id_t id) const
  {
    const Attribute& attr = get_attribute_const(id);

    return attr.get_value();
  }

  // Generic attribute setter
  void set_attribute_value(const attr_id_t id, const attr_value_t& value)
  {
    Attribute& attr = get_attribute_not_const(id);

    attr.set_value(value);
  }

  // Generic command executer
  template <typename... Args>
  ZclStatus execute_cluster_command(command_id_t id, const bool is_common,
                                    Args... args)
  {
    const commands_map_t* target_commands_map = nullptr;

    if (is_common)
    {
      target_commands_map = &common_commands_map;
    }
    else
    {
      target_commands_map = &commands_map;
    }

    for (const auto& [descriptor, gen_cmd_ptr] : *target_commands_map)
    {
      if (descriptor.id == id && descriptor.is_common == is_common)
      {
        if (gen_cmd_ptr == nullptr)
        {
          throw std::runtime_error("Command null pointer");
        }
        // Downcast from CommandBase to a cluster command
        using target_type = const Command<Cluster&, Args...>* const;

        auto cmd_ptr = dynamic_cast<target_type>(gen_cmd_ptr);
        if (cmd_ptr == nullptr)
        {
          throw std::runtime_error(
              "Command downcast failed,"
              "make sure the template arguments are correct");
        }

        return (*cmd_ptr)(*this, args...);
      }
    }
    throw std::runtime_error("Command not found");
  }
};
}  // namespace zcl

#endif  // ZCL_COMMON_CLUSTER_HPP
