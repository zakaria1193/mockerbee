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
#include "command_descriptor.hpp"
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

  [[nodiscard]] const attributes_list_t&    get_attributes() const;
  [[nodiscard]] const cluster_descriptor_t& get_descriptor() const;
  [[nodiscard]] const Attribute& get_attribute_const(attr_id_t attr_id) const;
  Attribute&                     get_attribute_not_const(attr_id_t attr_id);
  [[nodiscard]] attr_value_t     get_attribute_value(attr_id_t attr_id) const;
  void set_attribute_value(attr_id_t attr_id, const attr_value_t& value);

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
