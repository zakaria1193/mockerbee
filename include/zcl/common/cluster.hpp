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
  cluster_id_t id;
  bool         is_msp;
  std::string  description;
};

class Cluster
{
  cluster_descriptor_t descriptor;
  attributes_list_t    attributes;

 public:
  // Constructor
  Cluster(cluster_descriptor_t                       descriptor,
          const std::vector<attribute_descriptor_t>& attribute_descriptors)
      : descriptor(std::move(descriptor)),
        attributes(create_attributes_list(attribute_descriptors))
  {
  }

  // Method to get the list of attributes
  [[nodiscard]] const attributes_list_t& get_attributes() const
  {
    return attributes;
  }

  // Method to get the cluster descriptor
  [[nodiscard]] const cluster_descriptor_t& get_descriptor() const
  {
    return descriptor;
  }

  [[nodiscard]] const Attribute& get_attribute_const(
      const attr_id_t attr_id) const
  {
    for (const auto& attr : attributes)
    {
      if (attr.get_id() == attr_id)
      {
        return attr;
      }
    }
    throw std::runtime_error("Attribute not found");
  }

  Attribute& get_attribute_not_const(const attr_id_t attr_id)
  {
    for (auto& attr : attributes)
    {
      if (attr.get_id() == attr_id)
      {
        return attr;
      }
    }
    throw std::runtime_error("Attribute not found");
  }

  [[nodiscard]] attr_value_t get_attribute_value(const attr_id_t attr_id) const
  {
    const Attribute& attr = get_attribute_const(attr_id);

    return attr.get_value();
  }

  // Generic attribute setter
  void set_attribute_value(const attr_id_t attr_id, const attr_value_t& value)
  {
    Attribute& attr = get_attribute_not_const(attr_id);

    attr.set_value(value);
  }

  // ZCL commands methods

  // readAttributeCommand
  ZclStatus readAttributeCommand(const attr_id_t& attribute_id,
                                 attr_value_t&    value) const;

  // writeAttributeCommand
  ZclStatus writeAttributeCommand(const attr_id_t&    attribute_id,
                                  const attr_value_t& value);

  // configureReportingCommand
  ZclStatus configureReportingCommand(
      const attr_id_t&              attribute_id,
      const ReportingConfiguration& reporting_configuration);

  // discoverAttributesCommand
  ZclStatus discoverAttributesCommand(
      std::vector<attribute_descriptor_t>& attribute_descriptors) const;

  // sendReportingCommand
  [[nodiscard]] ZclStatus sendReportingCommand(const attr_id_t&    attribute_id,
                                               const attr_value_t& value) const;
};
}  // namespace zcl

#endif  // ZCL_COMMON_CLUSTER_HPP
