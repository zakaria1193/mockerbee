#ifndef ZCL_COMMON_ATTRIBUTES_HPP
#define ZCL_COMMON_ATTRIBUTES_HPP

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

// write AttributeDescriptor as struct
struct attribute_descriptor_t
{
  attr_id_t   id{0};
  bool        is_msp{false};
  bool        is_reportable{false};
  bool        is_readable{false};
  bool        is_writable{false};
  bool        is_mandatory{false};
  std::string description;
};

class Attribute
{
  attribute_descriptor_t descriptor;
  attr_value_t           value;
  ReportingConfiguration reporting_config;

 public:
  // Method to retrieve the attribute value
  [[nodiscard]] const auto& get_value() const
  {
    return value;
  }

  // Method to set the attribute value
  void set_value(const attr_value_t& value)
  {
    this->value = value;
  }

  // Attribute read
  [[nodiscard]] auto read() const
  {
    if (!descriptor.is_readable)
    {
      throw std::runtime_error("Attribute is not readable");
    }
    return value;
  }

  // Attribute write
  void write(const attr_value_t& value)
  {
    if (!descriptor.is_writable)
    {
      throw std::runtime_error("Attribute is not writable");
    }
    this->value = value;
  }

  // Reporting configuration getter
  [[nodiscard]] const auto& get_reporting_config() const
  {
    return reporting_config;
  }

  // Reporting configuration setter
  void set_reporting_config(const ReportingConfiguration& config)
  {
    reporting_config = config;
  }

  // ID getter
  [[nodiscard]] auto get_id() const { return descriptor.id; }

  // Constructor
  explicit Attribute(attribute_descriptor_t descriptor)
      : descriptor(std::move(descriptor))
  {
  }

  // Constructor with default value
  Attribute(attribute_descriptor_t descriptor, attr_value_t value)
      : descriptor(std::move(descriptor)), value(std::move(value))
  {
  }

  // Default constructor
  Attribute() = default;
};

using attributes_list_t = std::vector<Attribute>;
}  // namespace zcl

#endif  // ZCL_COMMON_ATTRIBUTES_HPP
