#include <device/device.hpp>
#include <iostream>
#include <nwk/nwk_mgt_commands.hpp>
#include <nwk/pan.hpp>
#include <zcl/clusters/global_commands.hpp>
#include <zcl/clusters/on_off_cluster.hpp>

// const device::MacAddress mac_address{0x11, 0x22, 0x33, 0x44,
//                                      0x55, 0x66, 0x77, 0x88};
//
const device::MacAddress mac_address =
    device::MacAddress{0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
const nwk::pan_id_t pan_id = 0x1234;


// Do not optimize
int main(int argc, char* argv[])
{
  device::OnOffDevice device(mac_address);

  std::cout << "Running..." << '\n';

  const zcl::attr_id_t attr_id =
      zcl::on_off_cluster::onOffAttributeDescriptor.id;
  const zcl::cluster_id_t cluster_id =
      zcl::on_off_cluster::cluster_descriptor.id;

  zcl::attr_value_t read_attr;

  device.get_endpoint(1)
      .get_cluster(cluster_id)
      .readAttributeCommand(attr_id, read_attr);

  auto cls = device.get_endpoint(1).get_cluster(cluster_id);
  std::cout << "typeid(cls).name(): " << typeid(cls).name() << '\n';
  std::cout << "typeid(zcl::on_off_cluster::OnOffCluster).name(): "
            << typeid(zcl::on_off_cluster::OnOffCluster).name() << '\n';
  auto *cls_ = dynamic_cast<zcl::on_off_cluster::OnOffCluster*>(&cls);
  if (cls_ == nullptr)
  {
    std::cout << "cls_ is null" << '\n';
    exit(1);
  }
  cls_->setOffCommand();



  // Pool

  device::Pool pool(pan_id);

  pool.add_device(device);

  device::short_address_t nwk_address = 0;

  device.join_pan(pool.get_pan());

  nwk::requestNwkAddressCommand(pool, mac_address, nwk_address);

  std::cout << " --- Exiting --- " << '\n';

  return 0;
}
