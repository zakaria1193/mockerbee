#ifndef DEVICE_POOL_POOL_HPP
#define DEVICE_POOL_POOL_HPP

#include <device/device.hpp>

namespace device
{
class Pool
{
  using device_list   = std::vector<device::Device>;
  device_list devices = {};

 public:
  Pool() = default;
  explicit Pool(device_list devices) : devices(std::move(devices)) {}

  void add_device(Device& device) { devices.push_back(device); }

  device::Device& get_device_by_mac(const device::mac_address_t& mac)
  {
    for (auto& device : devices)
    {
      if (device.get_mac_address() == mac)
      {
        return device;
      }
    }

    throw std::runtime_error("Device not found");
  }

  device::Device& get_device_by_short(
      const device::short_address_t& short_address)
  {
    for (auto& device : devices)
    {
      if (device.get_short_address() == short_address)
      {
        return device;
      }
    }

    throw std::runtime_error("Device not found");
  }
};
}  // namespace device

#endif  // DEVICE_POOL_POOL_HPP
