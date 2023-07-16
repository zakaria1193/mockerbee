#include <device/device.hpp>
#include <iostream>
#include <nwk/nwk_mgt_commands.hpp>
#include <nwk/pan.hpp>
#include <zcl/clusters/global_commands.hpp>
#include <zcl/clusters/on_off_cluster.hpp>


const device::MacAddress mac_address{0x11, 0x22, 0x33, 0x44,
                                     0x55, 0x66, 0x77, 0x88};
const nwk::pan_id_t pan_id             = 0x1234;

// Do not optimize
int main(int argc, char* argv[])
{
  device::OnOffDevice device(mac_address);

  std::cout << "Running..." << '\n';

  device.execute_cluster_command(
      1, zcl::on_off_cluster::cluster_descriptor.id,
      zcl::on_off_cluster::setOffCmdDescriptor.get_id(), false);

  const zcl::attr_id_t attr_id =
      zcl::on_off_cluster::onOffAttributeDescriptor.id;
  zcl::attr_value_t read_attr;

  device.execute_cluster_command<const zcl::attr_id_t&, zcl::attr_value_t&>(
      1, zcl::on_off_cluster::cluster_descriptor.id,
      zcl::read_attribute_command_descriptor.get_id(), true, attr_id,
      read_attr);

  // Pool

  device::Pool pool(pan_id);

  pool.add_device(device);

  device::short_address_t nwk_address = 0;

  device.join_pan(pool.get_pan());

  nwk::requestNwkAddressExecuter(pool, mac_address, nwk_address);

  std::cout << " --- Exiting --- " << '\n';

  return 0;
}
