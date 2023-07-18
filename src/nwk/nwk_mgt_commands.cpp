#include <nwk/nwk_mgt_commands.hpp>

namespace nwk
{

zcl::ZclStatus requestNwkAddressCommand(
    device::Pool& pool, const device::MacAddress& input_mac_address,
    device::short_address_t& output_nwk_address)
{
  auto device = pool.get_device_by_mac(input_mac_address);

  output_nwk_address = device.get_short_address();

  return zcl::ZclStatus::success;
}

zcl::ZclStatus requestMacAddressCommand(
    device::Pool& pool, const device::short_address_t& input_nwk_address,
    device::MacAddress& output_mac_address)
{
  auto device = pool.get_device_by_short(input_nwk_address);

  output_mac_address = device.get_mac_address();

  return zcl::ZclStatus::success;
}

zcl::ZclStatus leaveCommand(device::Device& device)
{
  device.leave_pan();

  return zcl::ZclStatus::success;
}

}  // namespace nwk
