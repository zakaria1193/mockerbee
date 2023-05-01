#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "reporting_configuration.hpp"

namespace zcl
{
using attr_id_t    = uint16_t;
using attr_value_t = std::variant<int8_t, uint8_t, int16_t, uint16_t, int32_t,
                                  uint32_t, std::string>;

class AttributeDescriptor
{
 public:
  AttributeDescriptor()
      : id(0),  // FIXME: should be an invalid value
        is_msp(false),
        is_reportable(false),
        is_readable(false),
        is_writable(false),
        is_mandatory(false),
        description("")
  {
  }

  // Constructor
  AttributeDescriptor(attr_id_t id, bool is_msp, bool is_reportable,
                      bool is_readable, bool is_writable, bool is_mandatory,
                      std::string description)
      : id(id),
        is_msp(is_msp),
        is_reportable(is_reportable),
        is_readable(is_readable),
        is_writable(is_writable),
        is_mandatory(is_mandatory),
        description(description)
  {
  }

  // Static attributes to fill from cluster descriptors
  const attr_id_t id;
  const bool      is_msp;
  const bool      is_reportable;
  const bool      is_readable;
  const bool      is_writable;
  const bool      is_mandatory;

  const std::string description;
};

class Attribute
{
 public:
  AttributeDescriptor    descriptor;
  attr_value_t           value;
  ReportingConfiguration reporting_config;

  // Method to retrieve the attribute value
  const auto& get_value() const
  {
    if (descriptor.is_readable)
      return value;
    else
      throw std::runtime_error("Attribute is not readable");
  }

  // Method to set the attribute value
  void set_value(const attr_value_t& value)
  {
    if (descriptor.is_writable)
      this->value = value;
    else
      throw std::runtime_error("Attribute is not writable");
  }

  // Constructor
  Attribute(const AttributeDescriptor& descriptor) : descriptor(descriptor) {}
  // Constructor with default value
  Attribute(const AttributeDescriptor& descriptor, const attr_value_t& value)
      : descriptor(descriptor), value(value)
  {
  }
  Attribute() = default;
};

using attributes_list_t = std::vector<Attribute>;
}  // namespace zcl
