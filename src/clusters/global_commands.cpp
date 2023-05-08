#include <iostream>
#include <zcl/clusters/global_commands.hpp>

namespace zcl
{
const commands_map_t Cluster::common_commands_map = {
    {read_attribute_command_descriptor,
     static_cast<const CommandBase*>(&readAttributeCommand)},
    {write_attribute_command_descriptor,
     static_cast<const CommandBase*>(&writeAttributeCommand)},
    {configure_reporting_command_descriptor,
     static_cast<const CommandBase*>(&configureReportingCommand)},
    {discover_attributes_command_descriptor,
     static_cast<const CommandBase*>(&discoverAttributesCommand)},
    {report_attributes_command_descriptor,
     static_cast<const CommandBase*>(&reportAttributesCommand)}};

ZclStatus readAttributeCommandExecuter(const Cluster&   cluster,
                                       const attr_id_t& attribute_id,
                                       attr_value_t&    value)
{
  const Attribute& attribute = cluster.get_attribute_const(attribute_id);

  std::cout << "Read attribute command" << '\n';

  value = attribute.read();

  return ZclStatus::success;
}

ZclStatus writeAttributeCommandExecuter(Cluster&            cluster,
                                        const attr_id_t&    attribute_id,
                                        const attr_value_t& value)
{
  std::cout << "Write attribute command" << '\n';

  // Update the attribute value
  Attribute& attribute = cluster.get_attribute_not_const(attribute_id);
  attribute.write(value);

  return ZclStatus::success;
}

ZclStatus configureReportingCommandExecuter(
    Cluster& cluster, const attr_id_t& attribute_id,
    const ReportingConfiguration& reporting_configuration)
{
  Attribute attribute = cluster.get_attribute_not_const(attribute_id);

  std::cout << "Configure reporting command" << '\n';

  // Update the attribute reporting configuration
  attribute.set_reporting_config(reporting_configuration);

  return ZclStatus::success;
}

ZclStatus reportAttributesCommandExecuter(const Cluster&   cluster,
                                          const Attribute& attribute)
{
  std::cout << "Report attributes command" << '\n';

  return ZclStatus::success;
}

ZclStatus discoverAttributesCommandExecuter(
    const Cluster&                       cluster,
    std::vector<attribute_descriptor_t>& attribute_descriptors)
{
  std::cout << "Discover attributes command" << '\n';

  return ZclStatus::success;
}

}  // namespace zcl
