#pragma once
#include <zcl/clusters/on_off_cluster.hpp>
#include "zcl/common/cluster.hpp"
#include "zcl/common/commands.hpp"

#include <stdint.h>
#include <vector>

namespace zcl {

  using endpoint_id_t = uint8_t;
  using cluster_list_t = std::vector<Cluster>;

  class Endpoint {
    cluster_list_t clusters;

  public:

    Endpoint(endpoint_id_t id,
             cluster_list_t clusters) : id(id), clusters(clusters) {}
   
    endpoint_id_t id;

    Cluster& get_cluster(const cluster_id_t cluster_id) {
      for (auto& cluster : clusters) {
        if (cluster.descriptor.id == cluster_id) {
          return cluster;
        }
      }
      throw std::runtime_error("Cluster not found");
    }
  };

  using endpoint_list_t = std::vector<Endpoint>;

  class Device {
    endpoint_list_t endpoints;

  public:
    Device(endpoint_list_t endpoints) : endpoints(endpoints) {}

    Endpoint& get_endpoint(const endpoint_id_t ep_id) {
      for (auto& endpoint : endpoints) {
        if (endpoint.id == ep_id) {
          return endpoint;
        }
      }
      throw std::runtime_error("Endpoint not found");
    }

    template <typename... Args>
    ZclStatus execute_cluster_command(const endpoint_id_t ep_id,
                                      const cluster_id_t cluster_id,
                                      const command_id_t command_id,
                                      bool is_common,
                                      Args... args)
    {
      Endpoint ep = get_endpoint(ep_id);
      Cluster cluster = ep.get_cluster(cluster_id);

      return cluster.execute_cluster_command<Args...>(command_id, is_common, args...);
    }
  };

  class OnOffDevice : public Device {
  public:
    OnOffDevice() : Device(
      {
        Endpoint{
          1,
          {zcl::on_off_cluster::OnOffCluster()}
        }
      }
    )
    {};
  };
}

