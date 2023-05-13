#ifndef DEVICE_POOL_POOL_HPP
#define DEVICE_POOL_POOL_HPP

#include <device/device.hpp>

class Pool
{
  using device_list = std::vector<zcl::Device>;
  device_list devices;

 public:
  Pool() = default;
  explicit Pool(device_list devices) : devices(std::move(devices)) {}

  void add_device(zcl::Device& device) { devices.push_back(device); }

  zcl::Device& get_device_by_mac(zcl::mac_address_t mac)
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
};

#endif  // DEVICE_POOL_POOL_HPP
