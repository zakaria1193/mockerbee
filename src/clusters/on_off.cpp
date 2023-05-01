#include <iostream>
#include <zcl/clusters/on_off_cluster.hpp>

namespace zcl::on_off_cluster
{
ZclStatus setOffExecuter(Cluster& cluster)
{
  std::cout << "setOffExecuter" << std::endl;
  cluster.set_attribute_value(onOffAttributeDescriptor.id, true);

  return ZclStatus::success;
}

ZclStatus setOnExecuter(Cluster& cluster)
{
  cluster.set_attribute_value(onOffAttributeDescriptor.id, true);

  return ZclStatus::success;
}

ZclStatus toggleExecuter(Cluster& cluster)
{
  std::cout << "toggleExecuter" << std::endl;

  return ZclStatus::not_implemented;
}

ZclStatus onWithRecallGlobalSceneExecuter(Cluster& cluster)
{
  std::cout << "onWithRecallGlobalSceneExecuter" << std::endl;

  return ZclStatus::not_implemented;
}

ZclStatus offWithEffectExecuter(Cluster& cluster, uint8_t effectIdentifier,
                                uint16_t effectVariant)
{
  std::cout << "offWithEffectExecuter" << std::endl;

  return ZclStatus::not_implemented;
}

ZclStatus onWithTimedOffExecuter(Cluster& cluster, uint8_t onOffControl,
                                 uint16_t onTime, uint16_t offWaitTime)
{
  std::cout << "onWithTimedOffExecuter" << std::endl;

  return ZclStatus::not_implemented;
}
}  // namespace zcl::on_off_cluster
