#include <device/device.hpp>

namespace device
{
Device::Device(const MacAddress& mac_address, endpoint_list_t endpoints)
    : mac_address(mac_address), endpoints(std::move(endpoints))
{
  std::cout << "Device created with MAC: " << this->mac_address.get_string()
            << " and " << this->endpoints.size() << " endpoints" << std::endl;
}

[[nodiscard]] MacAddress Device::get_mac_address() const { return mac_address; }

[[nodiscard]] short_address_t Device::get_short_address() const
{
  return short_address;
}

[[nodiscard]] bool Device::is_reacheable() const { return reacheable; }

[[nodiscard]] bool Device::is_in_network() const
{
  return pan.lock() != nullptr;
}

[[nodiscard]] const endpoint_list_t& Device::get_endpoints() const
{
  return endpoints;
}

Endpoint& Device::get_endpoint(const endpoint_id_t ep_id)
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

bool Device::join_pan(const std::shared_ptr<nwk::Pan>& pan)
{
  if (!pan->is_permit_joining())
  {
    std::cout << "Joining not allowed" << std::endl;
    return false;
  }

  this->pan = pan;
  return true;
}

void Device::leave_pan() { pan.reset(); }

OnOffDevice::OnOffDevice(const MacAddress& mac_address)
    : Device(mac_address,
             {Endpoint{1, {zcl::on_off_cluster::OnOffCluster()}}}){};

}  // namespace device
