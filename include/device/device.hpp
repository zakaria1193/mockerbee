#ifndef ZCL_DEVICE_HPP
#define ZCL_DEVICE_HPP

#include <cstdint>
#include <iomanip>
#include <memory>
#include <utility>
#include <vector>
#include <zcl/clusters/on_off_cluster.hpp>

#include "device/endpoint.hpp"
#include "device/mac_address.hpp"
#include "nwk/pan.hpp"
#include "zcl/common/cluster.hpp"

namespace device
{

using short_address_t = uint16_t;

class Device
{
  MacAddress      mac_address;
  endpoint_list_t endpoints;

  // Attributes depending on the network
  std::weak_ptr<nwk::Pan> pan{};
  short_address_t         short_address{};
  bool                    reacheable{true};

 public:
  Device() = delete;
  Device(const MacAddress& mac_address, std::initializer_list<Endpoint> endpoints);

  [[nodiscard]] MacAddress get_mac_address() const;

  [[nodiscard]] short_address_t get_short_address() const;

  [[nodiscard]] bool is_reacheable() const;

  [[nodiscard]] bool is_in_network() const;

  [[nodiscard]] const endpoint_list_t& get_endpoints() const;

  Endpoint& get_endpoint(endpoint_id_t ep_id);

  bool join_pan(const std::shared_ptr<nwk::Pan>& pan);

  void leave_pan();
};

class OnOffDevice : public Device
{
 public:
  explicit OnOffDevice(const MacAddress& mac_address);
};

}  // namespace device

#endif  // ZCL_DEVICE_HPP__
