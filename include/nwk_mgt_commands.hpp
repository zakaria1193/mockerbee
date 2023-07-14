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
const zcl::CommandDescriptor requestNwkAddressCmdDescriptor{
    /*cmd_id=*/0,
    /*is_common=*/true,
    /*is_mandatory=*/true,
    /*description=*/"Request NWK address"};

zcl::ZclStatus requestNwkAddressExecuter(
    device::Pool& pool, const device::mac_address_t& input_mac_address,
    device::short_address_t& output_nwk_address);

const zcl::Command requestNwkAddressCommand{/*exec=*/requestNwkAddressExecuter};

// Request mac address command
const zcl::CommandDescriptor requestMacAddressCmdDescriptor{
    /*cmd_id=*/1,
    /*is_common=*/true,
    /*is_mandatory=*/true,
    /*description=*/"Request MAC address"};

zcl::ZclStatus requestMacAddressExecuter(
    device::Pool& pool, const device::short_address_t& input_nwk_address,
    device::mac_address_t& output_mac_address);

const zcl::Command requestMacAddressCommand{/*exec=*/requestMacAddressExecuter};

// Leave command
const zcl::CommandDescriptor leaveCmdDescriptor{/*cmd_id=*/0x34,
                                                /*is_common=*/true,
                                                /*is_mandatory=*/true,
                                                /*description=*/"leave"};

zcl::ZclStatus               leaveExecuter(device::Device& device);

const zcl::Command           leaveCommand{/*exec=*/leaveExecuter};

}  // namespace nwk

#endif  // NWK_MGT_COMMANDS_HPP
