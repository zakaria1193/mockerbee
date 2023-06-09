#include <nwk_mgt_commands.hpp>

zcl::ZclStatus requestNwkAddressExecuter(
    device::Pool& pool, const device::mac_address_t& input_mac_address,
    device::short_address_t& output_nwk_address)
{
  auto device = pool.get_device_by_mac(input_mac_address);

  output_nwk_address = device.get_short_address();

  return zcl::ZclStatus::success;
}

zcl::ZclStatus requestMacAddressExecuter(
    device::Pool& pool, const device::short_address_t& input_nwk_address,
    device::mac_address_t& output_mac_address)
{
  auto device = pool.get_device_by_short(input_nwk_address);

  output_mac_address = device.get_mac_address();

  return zcl::ZclStatus::success;
}

zcl::ZclStatus leaveExecuter(device::Device& device)
{
  device.set_in_network(false);

  return zcl::ZclStatus::success;
}
