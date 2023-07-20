#ifndef ZCL_CLUSTERS_GLOBAL_COMMANDS_HPP
#define ZCL_CLUSTERS_GLOBAL_COMMANDS_HPP

#include <zcl/common/command_descriptor.hpp>
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

// Write attribute command
const CommandDescriptor write_attribute_command_descriptor{
    /*id*/ 0x02,
    /*is_common*/ true,
    /*is_mandatory*/ true,
    /*description*/ "Write attribute"};

// Configure reporting command
const CommandDescriptor configure_reporting_command_descriptor{
    /*id*/ 0x06,
    /*is_common*/ true,
    /*is_mandatory*/ true,
    /*description*/ "Configure reporting"};

// Discover attributes command
const CommandDescriptor discover_attributes_command_descriptor{
    /*id*/ 0x0C,
    /*is_common*/ true,
    /*is_mandatory*/ true,
    /*description*/ "Discover attributes"};

// FIXME This command requires a special handling
// since it is send by the device
const CommandDescriptor report_attributes_command_descriptor{
    /*id*/ 0x0A,
    /*is_common*/ true,
    /*is_mandatory*/ true,
    /*description*/ "Report attributes"};

}  // namespace zcl

#endif  // ZCL_CLUSTERS_GLOBAL_COMMANDS_HPP
