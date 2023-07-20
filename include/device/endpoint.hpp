#ifndef DEVICE_ENDPOINT_HPP
#define DEVICE_ENDPOINT_HPP

#include <zcl/common/cluster.hpp>

namespace device
{

using endpoint_id_t  = uint8_t;
using cluster_list_t = std::vector<zcl::Cluster>;

class Endpoint
{
  endpoint_id_t  ep_id;
  cluster_list_t clusters;

 public:
  Endpoint(endpoint_id_t ep_id, cluster_list_t clusters);

  [[nodiscard]] endpoint_id_t get_endpoint_id() const;

  zcl::Cluster& get_cluster(zcl::cluster_id_t cluster_id);
};

using endpoint_list_t = std::vector<Endpoint>;

}  // namespace device

#endif  // DEVICE_ENDPOINT_HPP
