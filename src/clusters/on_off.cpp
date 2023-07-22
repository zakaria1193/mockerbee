#include <iostream>
#include <zcl/clusters/on_off_cluster.hpp>

namespace zcl::on_off_cluster
{
ZclStatus OnOffCluster::setOffCommand()
{
  std::cout << "setOffCommand" << '\n';
  this->set_attribute_value(onOffAttributeDescriptor.id, true);

  return ZclStatus::success;
}

ZclStatus OnOffCluster::setOnCommand()
{
  std::cout << "setOnCommand" << '\n';
  this->set_attribute_value(onOffAttributeDescriptor.id, true);

  return ZclStatus::success;
}

ZclStatus OnOffCluster::toggleCommand()
{
  std::cout << "toggleCommand" << '\n';

  return ZclStatus::not_implemented;
}

ZclStatus OnOffCluster::offWithEffectCommand(uint8_t  effectIdentifier,
                                             uint16_t effectVariant)
{
  std::cout << "offWithEffectCommand" << '\n';

  return ZclStatus::not_implemented;
}

ZclStatus OnOffCluster::onWithRecallGlobalSceneCommand()
{
  std::cout << "onWithRecallGlobalSceneCommand" << '\n';

  return ZclStatus::not_implemented;
}

ZclStatus OnOffCluster::onWithTimedOffCommand(uint8_t  onOffControl,
                                              uint16_t onTime,
                                              uint16_t offWaitTime)
{
  std::cout << "onWithTimedOffCommand" << '\n';

  return ZclStatus::not_implemented;
}

}  // namespace zcl::on_off_cluster
