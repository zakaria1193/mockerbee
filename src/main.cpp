#include <iostream>
#include <zcl/clusters/global_commands.hpp>
#include <zcl/clusters/on_off_cluster.hpp>
#include <device.hpp>

// Do not optimize
int main(int argc, char* argv[])
{
  zcl::OnOffDevice device;

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

  std::cout << " --- Exiting --- " << '\n';

  return 0;
}
