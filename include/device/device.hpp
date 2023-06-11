#ifndef ZCL_DEVICE_HPP
#define ZCL_DEVICE_HPP

#include <cstdint>
#include <utility>
#include <vector>
#include <zcl/clusters/on_off_cluster.hpp>

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
using mac_address_t   = uint64_t;

class Device
{
  mac_address_t   mac_address;
  short_address_t short_address;
  bool            reacheable{true};
  bool            in_network{false};
  endpoint_list_t endpoints;

 public:
  Device(mac_address_t mac_address, endpoint_list_t endpoints)
      : mac_address(mac_address),
        short_address(random()),
        endpoints(std::move(endpoints))
  {
  }

  [[nodiscard]] mac_address_t get_mac_address() const { return mac_address; }

  [[nodiscard]] short_address_t get_short_address() const
  {
    return short_address;
  }

  [[nodiscard]] bool is_reacheable() const { return reacheable; }

  [[nodiscard]] bool is_in_network() const { return in_network; }

  void set_in_network(bool in_network) { this->in_network = in_network; }

  [[nodiscard]] const endpoint_list_t& get_endpoints() const
  {
    return endpoints;
  }

  Endpoint& get_endpoint(const endpoint_id_t ep_id)
  {
    for (auto& endpoint : endpoints)
    {
      if (endpoint.get_endpoint_id() == ep_id)
      {
        return endpoint;
      }
    }
    throw std::runtime_error("Endpoint not found");
  }

  template <typename... Args>
  zcl::ZclStatus execute_cluster_command(const endpoint_id_t     ep_id,
                                         const zcl::cluster_id_t cluster_id,
                                         const zcl::command_id_t command_id,
                                         bool is_common, Args... args)
  {
    Endpoint     ept     = get_endpoint(ep_id);
    zcl::Cluster cluster = ept.get_cluster(cluster_id);

    return cluster.execute_cluster_command<Args...>(command_id, is_common,
                                                    args...);
  }
};

class OnOffDevice : public Device
{
 public:
  explicit OnOffDevice(mac_address_t mac_address)
      : Device(mac_address,
               {Endpoint{1, {zcl::on_off_cluster::OnOffCluster()}}}){};
};

}  // namespace device

#endif  // ZCL_DEVICE_HPP__
