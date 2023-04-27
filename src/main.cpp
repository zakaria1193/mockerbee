#include <zcl/clusters/on_off_cluster.hpp>
#include <zcl/clusters/global_commands.hpp>
#include <iostream>
#include <zcl/device.hpp>

zcl::OnOffDevice device;

// Do not optimize
int main(int argc, char *argv[])
{

  std::cout << "Running..." << std::endl;

  device.execute_cluster_command<>(
    1,
    zcl::on_off_cluster::cluster_descriptor.id,
    zcl::on_off_cluster::setOffCmdDescriptor.id,
    false
  );

  std::cout << " --- Exiting --- " << std::endl;

  return 0;
}
