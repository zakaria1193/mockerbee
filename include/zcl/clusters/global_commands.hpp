#ifndef ZCL_CLUSTERS_GLOBAL_COMMANDS_HPP
#define ZCL_CLUSTERS_GLOBAL_COMMANDS_HPP

#include <zcl/common/attributes.hpp>
#include <zcl/common/cluster.hpp>
#include <zcl/common/commands.hpp>
#include <zcl/common/reporting_configuration.hpp>
#include <zcl/common/zcl_status.hpp>

namespace zcl
{
// Default commands
// For each command we need to define:
// 1. Command descriptor
// 2. Command executer
// 3. Command object

// Read attribute command
const CommandDescriptor read_attribute_command_descriptor{
    /*id*/ 0x00,
    /*is_common*/ true,
    /*is_mandatory*/ true,
    /*description*/ "Read attribute"};
ZclStatus     readAttributeCommandExecuter(Cluster&         cluster,
                                           const attr_id_t& attribute_id,
                                           attr_value_t&    value);
const Command readAttributeCommand{/*exec=*/readAttributeCommandExecuter};

// Write attribute command
const CommandDescriptor write_attribute_command_descriptor{
    /*id*/ 0x02,
    /*is_common*/ true,
    /*is_mandatory*/ true,
    /*description*/ "Write attribute"};
ZclStatus     writeAttributeCommandExecuter(Cluster&            cluster,
                                            const attr_id_t&    attribute_id,
                                            const attr_value_t& value);
const Command writeAttributeCommand{/*exec=*/writeAttributeCommandExecuter};

// Configure reporting command
const CommandDescriptor configure_reporting_command_descriptor{
    /*id*/ 0x06,
    /*is_common*/ true,
    /*is_mandatory*/ true,
    /*description*/ "Configure reporting"};
ZclStatus configureReportingCommandExecuter(
    Cluster& cluster, const attr_id_t& attribute_id,
    const ReportingConfiguration& reporting_configuration);
const Command configureReportingCommand{
    /*exec=*/configureReportingCommandExecuter};

// Discover attributes command
const CommandDescriptor discover_attributes_command_descriptor{
    /*id*/ 0x0C,
    /*is_common*/ true,
    /*is_mandatory*/ true,
    /*description*/ "Discover attributes"};
ZclStatus discoverAttributesCommandExecuter(
    Cluster&                             cluster,
    std::vector<attribute_descriptor_t>& attribute_descriptors);
const Command discoverAttributesCommand{
    /*exec=*/discoverAttributesCommandExecuter};

// FIXME This command requires a special handling
// since it is send by the device
const CommandDescriptor report_attributes_command_descriptor{
    /*id*/ 0x0A,
    /*is_common*/ true,
    /*is_mandatory*/ true,
    /*description*/ "Report attributes"};
ZclStatus     reportAttributesCommandExecuter(Cluster&         cluster,
                                              const Attribute& attribute);
const Command reportAttributesCommand{/*exec=*/reportAttributesCommandExecuter};

}  // namespace zcl

#endif  // ZCL_CLUSTERS_GLOBAL_COMMANDS_HPP
