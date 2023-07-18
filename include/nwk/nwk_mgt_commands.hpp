#ifndef NWK_MGT_COMMANDS_HPP
#define NWK_MGT_COMMANDS_HPP

#include <device/device.hpp>
#include <device_pool/pool.hpp>
#include <zcl/common/commands.hpp>

//////////////////////////////
// Command descriptors
//////////////////////////////

namespace nwk
{

// Request NWK address command
const zcl::CommandDescriptor requestNwkAddressCommandDescriptor{
    /*cmd_id=*/0,
    /*is_common=*/true,
    /*is_mandatory=*/true,
    /*description=*/"Request NWK address"};
zcl::ZclStatus requestNwkAddressCommand(
    device::Pool& pool, const device::MacAddress& input_mac_address,
    device::short_address_t& output_nwk_address);

// Request mac address command
const zcl::CommandDescriptor requestMacAddressCommandDescriptor{
    /*cmd_id=*/1,
    /*is_common=*/true,
    /*is_mandatory=*/true,
    /*description=*/"Request MAC address"};
zcl::ZclStatus requestMacAddressCommand(
    device::Pool& pool, const device::short_address_t& input_nwk_address,
    device::MacAddress& output_mac_address);

// Leave command
const zcl::CommandDescriptor leaveCommandDescriptor{/*cmd_id=*/0x34,
                                                    /*is_common=*/true,
                                                    /*is_mandatory=*/true,
                                                    /*description=*/"leave"};
zcl::ZclStatus               leaveCommand(device::Device& device);

}  // namespace nwk

#endif  // NWK_MGT_COMMANDS_HPP
