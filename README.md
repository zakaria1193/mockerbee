👷 Project is still a draft ! roadmap is still not clearly defined. your comments are welcome


Device Mocker with ZCL API is a powerful library for simulating devices with different ZCL clusters, designed for developers working on IoT devices with Zigbee communication.

Built with modern C++ features, Device Mocker supports both C and C++ APIs and can be easily integrated into your existing project.

Device Mocker is designed to be easy to use, with a simple API that allows you to create a device with just a few lines of code.

### Prerequisites

- CMake 3.10 or later
- C++ compiler with C++23 support (Recommended clang-17)

### Code quality checks

- libsanitizer
- clang-tidy
- cppcheck
- clang-format

### CI Test

[![CMake](https://github.com/zakaria1193/mockerbee/actions/workflows/cmake.yml/badge.svg)](https://github.com/zakaria1193/mockerbee/actions/workflows/cmake.yml)

### Documentation

#### Concepts

##### Endpoint & Device & Device Pool

A pool of devices is a collection of devices. A device is a collection of endpoints. each endpoint is a collection of clusters.

A pool has an associated PAN (Personal Area Network) object. Each device in the pool can be in this PAN or not.

A device pool can be enhanced to hold multiple PANs. But it is not considered in the current implementation.

##### Cluster

ZCL cluster representation object. it mirror a ZCL cluster with all its attributes as if it running on a real device.

Each cluster command is defined by:

- A command descriptor.
- A command executer = a free function that takes a cluster object as a first argument.

The commands are not methods of the cluster object. this is needed because a command can be executed from runtime
id resolved from a command ID. using:

```C++
class Device
{
  ...

  template <typename... Args>
  zcl::ZclStatus execute_cluster_command(const endpoint_id_t     ep_id,
                                         const zcl::cluster_id_t cluster_id,
                                         const zcl::command_id_t command_id,
                                         bool is_common, Args... args);
}
```

##### Create a device pool and communicate with devices

```C++
  // Create a device pool with a PAN ID
  device::Pool pool(pan_id);

  // Instantiate a device using a device class
  device::OnOffDevice device(mac_address);

  // Open the pan
  pool.pan.set_permit_joining(true);

  // Make it join the PAN
  device.join_pan(pool.get_pan());

  // Communicate with the device
  device.execute_cluster_command(
      1, zcl::on_off_cluster::cluster_descriptor.id,
      zcl::on_off_cluster::setOffCmdDescriptor.get_id(), false);




```

#### Custom clusters and devices

##### Adding custom cluster

A custom cluster can be added by inheriting from the `Cluster` class and passing the required
attribute descriptors and commands.

```C++

namespace my_rocket_cluster_namespace
{
// Cluster descriptor
const cluster_descriptor_t cluster_descriptor{/*id=*/0xF001,
                                              /*is_msp=*/true,
                                              /*description=*/"My rocket cluster"};

const commands_map_t on_off_commands_map = {
    {liftOffCommandDescriptor,
     static_cast<const CommandBase* const>(&liftOffCommand)},
};

// OnOffCluster class
class MyRocketCluster : public Cluster
{
 public:
  RocketCluster()
      : Cluster(
            /*descriptor=*/cluster_descriptor,
            /*attribute_descriptors=*/
            {altitudeAttributeDescriptor, speedAttributeDescriptor,
             coordinatesAttributeDescriptor},
            /*commands_map=*/
  {
  }
};
```

##### Add custom device

A device class can be created by inheriting from the `Device` class and passing the required
endpoints with their clusters to the base class constructor.

```C++

class OnOffDevice : public Device
{
 public:
  explicit OnOffDevice(const MacAddress& mac_address)
      : Device(mac_address,
               {Endpoint{1, {zcl::on_off_cluster::OnOffCluster()}},
                Endpoint{2, {zcl::my_cluster_namespace::MyCluster()}}
               }){};
};
```
