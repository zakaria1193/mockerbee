#ifndef DEVICE_POOL_POOL_HPP
#define DEVICE_POOL_POOL_HPP

#include <device/device.hpp>
#include <memory>
#include <nwk/pan.hpp>

namespace device
{
class Pool
{
  using device_list   = std::vector<std::unique_ptr<Device>>;
  device_list devices = {};

  // Each pool has its own PAN
  std::shared_ptr<nwk::Pan> pan;

 public:
  Pool() = delete;

  explicit Pool(nwk::pan_id_t pan_id) : pan(std::make_shared<nwk::Pan>(pan_id))
  {
  }

  Pool(std::initializer_list<Device> devices, nwk::pan_id_t pan_id)
      : pan(std::make_shared<nwk::Pan>(pan_id))
  {
    for (const auto& device : devices)
    {
      add_device(device);
    }
  }

  [[nodiscard]] std::shared_ptr<nwk::Pan> get_pan() const { return pan; }

  [[nodiscard]] const device_list& get_devices() const { return devices; }

  void add_device(Device& device) { devices.push_back(std::make_unique<Device>(device)); }

  device::Device& get_device_by_mac(const device::MacAddress& mac)
  {
    for (auto& device : devices)
    {
      if (device->get_mac_address() == mac)
      {
        return *device;
      }
    }

    throw std::runtime_error("Device not found");
  }

  device::Device& get_device_by_short(
      const device::short_address_t& short_address)
  {
    for (auto& device : devices)
    {
      if (device->get_short_address() == short_address)
      {
        return *device;
      }
    }

    throw std::runtime_error("Device not found");
  }
};
}  // namespace device

#endif  // DEVICE_POOL_POOL_HPP
