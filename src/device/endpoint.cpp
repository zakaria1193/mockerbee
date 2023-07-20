#include <device/endpoint.hpp>

namespace device
{

using endpoint_id_t  = uint8_t;
using cluster_list_t = std::vector<zcl::Cluster>;

Endpoint::Endpoint(endpoint_id_t ep_id, cluster_list_t clusters)
    : ep_id(ep_id), clusters(std::move(clusters))
{
}

[[nodiscard]] endpoint_id_t Endpoint::get_endpoint_id() const { return ep_id; }

zcl::Cluster& Endpoint::get_cluster(const zcl::cluster_id_t cluster_id)
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

}  // namespace device
