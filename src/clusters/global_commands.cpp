#include <iostream>
#include <zcl/clusters/global_commands.hpp>

namespace zcl
{
ZclStatus Cluster::readAttributeCommand(const attr_id_t& attribute_id,
                                        attr_value_t&    value) const
{
  const Attribute& attribute = this->get_attribute_const(attribute_id);

  std::cout << "Read attribute command" << '\n';

  value = attribute.read();

  return ZclStatus::success;
}

ZclStatus Cluster::writeAttributeCommand(const attr_id_t&    attribute_id,
                                         const attr_value_t& value)
{
  std::cout << "Write attribute command" << '\n';

  // Update the attribute value
  Attribute& attribute = this->get_attribute_not_const(attribute_id);
  attribute.write(value);

  return ZclStatus::success;
}

ZclStatus Cluster::configureReportingCommand(
    const attr_id_t&              attribute_id,
    const ReportingConfiguration& reporting_configuration)
{
  Attribute attribute = this->get_attribute_not_const(attribute_id);

  std::cout << "Configure reporting command" << '\n';

  // Update the attribute reporting configuration
  attribute.set_reporting_config(reporting_configuration);

  return ZclStatus::success;
}

ZclStatus reportAttributesCommand(Cluster& cluster, const Attribute& attribute)
{
  std::cout << "Report attributes command" << '\n';

  return ZclStatus::success;
}

ZclStatus discoverAttributesCommand(
    Cluster&                             cluster,
    std::vector<attribute_descriptor_t>& attribute_descriptors)
{
  std::cout << "Discover attributes command" << '\n';

  return ZclStatus::success;
}

}  // namespace zcl
