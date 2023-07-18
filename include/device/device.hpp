#ifndef ZCL_DEVICE_HPP
#define ZCL_DEVICE_HPP

#include <cstdint>
#include <iomanip>
#include <memory>
#include <utility>
#include <vector>
#include <zcl/clusters/on_off_cluster.hpp>

#include "nwk/pan.hpp"
#include "zcl/common/cluster.hpp"
#include "zcl/common/commands.hpp"

namespace device
{

using endpoint_id_t  = uint8_t;
using cluster_list_t = std::vector<zcl::Cluster>;

class Endpoint
{
  endpoint_id_t  ep_id;
  cluster_list_t clusters;

 public:
  Endpoint(endpoint_id_t ep_id, cluster_list_t clusters)
      : ep_id(ep_id), clusters(std::move(clusters))
  {
  }

  [[nodiscard]] endpoint_id_t get_endpoint_id() const { return ep_id; }

  zcl::Cluster& get_cluster(const zcl::cluster_id_t cluster_id)
  {
    for (auto& cluster : clusters)
    {
      if (cluster.get_descriptor().id == cluster_id)
      {
        return cluster;
      }
    }
    throw std::runtime_error("Cluster not found");
  }
};

using endpoint_list_t = std::vector<Endpoint>;
using short_address_t = uint16_t;

class MacAddress
{
  using mac_address_value_t = std::array<uint8_t, 8>;
  mac_address_value_t address{};
  size_t              size{};

 public:
  MacAddress() = delete;

  // Constructer from byte arg list using initializer list
  template <typename... Args>
  explicit MacAddress(Args... args) : size(sizeof...(args))
  {
    size_t index = 0;

    if (size > address.size())
    {
      throw std::runtime_error(
          "MacAddress constructor received too many bytes");
    }

    for (auto arg : {args...})
    {
      address[index++] = arg;
    }

    std::cout << "MacAddress created with " << size << " bytes" << std::endl;
  }

  [[nodiscard]] std::string get_string() const
  {
    std::stringstream ss;
    // Format 00:AA:BB:CC:DD:EE:FF:00
    for (size_t i = 0; i < size; i++)
    {
      bool is_last = i == size - 1;
      ss << std::setfill('0') << std::setw(2) << std::hex
         << static_cast<int>(address[i]) << (is_last ? "" : ":");
    }

    return ss.str();
  }

  // Comparison operators
  bool operator==(const MacAddress& rhs) const
  {
    return address == rhs.address;
  }

  bool operator!=(const MacAddress& rhs) const { return !(rhs == *this); }
};

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
  Device(const MacAddress& mac_address, endpoint_list_t endpoints)
      : mac_address(mac_address), endpoints(std::move(endpoints))
  {
    std::cout << "Device created with MAC: " << mac_address.get_string()
              << " and " << endpoints.size() << " endpoints" << std::endl;
  }

  [[nodiscard]] MacAddress get_mac_address() const { return mac_address; }

  [[nodiscard]] short_address_t get_short_address() const
  {
    return short_address;
  }

  [[nodiscard]] bool is_reacheable() const { return reacheable; }

  [[nodiscard]] bool is_in_network() const { return pan.lock() != nullptr; }

  [[nodiscard]] const endpoint_list_t& get_endpoints() const
  {
    return endpoints;
  }

  Endpoint& get_endpoint(const endpoint_id_t ep_id)
  {
    auto ept = std::find_if(endpoints.begin(), endpoints.end(),
                            [ep_id](const Endpoint& ept)
                            { return ept.get_endpoint_id() == ep_id; });

    if (ept == endpoints.end())
    {
      throw std::runtime_error("Endpoint not found");
    }

    return *ept;
  }

  bool join_pan(const std::shared_ptr<nwk::Pan>& pan)
  {
    if (!pan->is_permit_joining())
    {
      std::cout << "Joining not allowed" << std::endl;
      return false;
    }

    this->pan = pan;
    return true;
  }

  void leave_pan() { pan.reset(); }
};

class OnOffDevice : public Device
{
 public:
  explicit OnOffDevice(const MacAddress& mac_address)
      : Device(mac_address,
               {Endpoint{1, {zcl::on_off_cluster::OnOffCluster()}}}){};
};

}  // namespace device

#endif  // ZCL_DEVICE_HPP__
