#pragma once
#include <zcl/common/commands.hpp>
#include <zcl/common/attributes.hpp>
#include <zcl/common/cluster.hpp>
#include <zcl/common/reporting_configuration.hpp>
#include <zcl/common/zcl_status.hpp>

namespace zcl {

  // Default commands
  // For each command we need to define:
  // 1. Command descriptor
  // 2. Command executer
  // 3. Command object

  const command_descriptor_t read_attribute_command_descriptor{
      /*id*/ 0x00,
      /*is_common*/ true,
      /*is_mandatory*/ true,
      /*description*/ "Read attribute"
  };
  ZclStatus readAttributeCommandExecuter(const Cluster &cluster,
                                         const attr_id_t attribute_id,
                                         attr_value_t &value);
  const Command readAttributeCommand {
      /*executer=*/readAttributeCommandExecuter
  };

  const command_descriptor_t write_attribute_command_descriptor{
      /*id*/ 0x02,
      /*is_common*/ true,
      /*is_mandatory*/ true,
      /*description*/ "Write attribute"
  };
  ZclStatus writeAttributeCommandExecuter(Cluster &cluster,
                                          const attr_id_t attribute_id,
                                          const attr_value_t &value);
  const Command writeAttributeCommand {
      /*executer=*/writeAttributeCommandExecuter
  };

  const command_descriptor_t configure_reporting_command_descriptor{
      /*id*/ 0x06,
      /*is_common*/ true,
      /*is_mandatory*/ true,
      /*description*/ "Configure reporting"
  };
  ZclStatus configureReportingCommandExecuter(Cluster &cluster,
                                              const attr_id_t attribute_id,
                                              const ReportingConfiguration &reporting_configuration);
  const Command configureReportingCommand {
      /*executer=*/configureReportingCommandExecuter
  };

  const command_descriptor_t discover_attributes_command_descriptor{
      /*id*/ 0x0C,
      /*is_common*/ true,
      /*is_mandatory*/ true,
      /*description*/ "Discover attributes"
  };
  ZclStatus discoverAttributesCommandExecuter(const Cluster &cluster,
                                              std::vector<AttributeDescriptor> &attribute_descriptors);
  const Command discoverAttributesCommand {
      /*executer=*/discoverAttributesCommandExecuter
  };

  // FIXME This command requires a special handling
  // since it is send by the device
  const command_descriptor_t report_attributes_command_descriptor{
      /*id*/ 0x0A,
      /*is_common*/ true,
      /*is_mandatory*/ true,
      /*description*/ "Report attributes"
  };
  ZclStatus reportAttributesCommandExecuter(const Cluster &cluster,
                                            const Attribute &attribute);
  const Command reportAttributesCommand {
      /*executer=*/reportAttributesCommandExecuter
  };

}


