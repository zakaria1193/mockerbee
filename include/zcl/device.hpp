#ifndef ZCL_DEVICE_HPP
#define ZCL_DEVICE_HPP

#include <cstdint>
#include <utility>
#include <vector>
#include <zcl/clusters/on_off_cluster.hpp>

#include "zcl/common/cluster.hpp"
#include "zcl/common/commands.hpp"

namespace zcl
{
using endpoint_id_t  = uint8_t;
using cluster_list_t = std::vector<Cluster>;

class Endpoint
{
  cluster_list_t clusters;
  endpoint_id_t  ep_id;

 public:
  Endpoint(endpoint_id_t ep_id, cluster_list_t clusters)
      : ep_id(ep_id), clusters(std::move(clusters))
  {
  }

  [[nodiscard]] endpoint_id_t get_endpoint_id() const { return ep_id; }

  Cluster& get_cluster(const cluster_id_t cluster_id)
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

class Device
{
  endpoint_list_t endpoints;

 public:
  explicit Device(endpoint_list_t endpoints) : endpoints(std::move(endpoints))
  {
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
  ZclStatus execute_cluster_command(const endpoint_id_t ep_id,
                                    const cluster_id_t  cluster_id,
                                    const command_id_t  command_id,
                                    bool                is_common, Args... args)
  {
    Endpoint ept     = get_endpoint(ep_id);
    Cluster  cluster = ept.get_cluster(cluster_id);

    return cluster.execute_cluster_command<Args...>(command_id, is_common,
                                                    args...);
  }
};

class OnOffDevice : public Device
{
 public:
  OnOffDevice()
      : Device({Endpoint{1, {zcl::on_off_cluster::OnOffCluster()}}}){};
};
}  // namespace zcl

#endif  // ZCL_DEVICE_HPP__
