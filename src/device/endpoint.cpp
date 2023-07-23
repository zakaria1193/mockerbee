#include <device/endpoint.hpp>

namespace device
{
// Constructor from initializer list
Endpoint::Endpoint(endpoint_id_t ep_id, std::initializer_list<zcl::Cluster> clusters)
    : ep_id(ep_id)
{
  for (const auto& cluster : clusters)
  {
    this->clusters.emplace_back(std::make_unique<zcl::Cluster>(cluster));
  }
}

[[nodiscard]] endpoint_id_t Endpoint::get_endpoint_id() const { return ep_id; }

zcl::Cluster& Endpoint::get_cluster(const zcl::cluster_id_t cluster_id)
{
  for (auto& cluster : clusters)
  {
    if (cluster->get_descriptor().id == cluster_id)
    {
      return *cluster;
    }
  }
  throw std::runtime_error("Cluster not found");
}

}  // namespace device
