#ifndef ZCL_CLUSTERS_ON_OFF_CLUSTER_HPP
#define ZCL_CLUSTERS_ON_OFF_CLUSTER_HPP

#include <zcl/common/cluster.hpp>

namespace zcl::on_off_cluster
{
// Attribute descriptors
const attribute_descriptor_t onOffAttributeDescriptor = {
    /*id=*/0,
    /*is_msp=*/false,
    /*is_reportable=*/false,
    /*is_readable=*/true,
    /*is_writable=*/true,
    /*is_mandatory=*/true,
    /*description=*/"onOff"};
const attribute_descriptor_t onTimeAttributeDescriptor = {
    /*id=*/16385,
    /*is_msp=*/false,
    /*is_reportable=*/false,
    /*is_readable=*/true,
    /*is_writable=*/true,
    /*is_mandatory=*/false,
    /*description=*/"onTime"};
const attribute_descriptor_t offWaitTimeAttributeDescriptor = {
    /*id=*/16386,
    /*is_msp=*/false,
    /*is_reportable=*/false,
    /*is_readable=*/true,
    /*is_writable=*/true,
    /*is_mandatory=*/false,
    /*description=*/"offWaitTime"};

//////////////////////////////
// Command descriptors
//////////////////////////////

// setOff command
// setOn command
const CommandDescriptor setOnCmdDescriptor{/*cmd_id=*/1,
                                           /*is_common=*/false,
                                           /*is_mandatory=*/true,
                                           /*description=*/"setOn"};

// toggle command
const CommandDescriptor toggleCmdDescriptor{/*cmd_id=*/2,
                                            /*is_common=*/false,
                                            /*is_mandatory=*/true,
                                            /*description=*/"toggle"};

// offWithEffect command
const CommandDescriptor offWithEffectCmdDescriptor{
    /*cmd_id=*/64,
    /*is_common=*/false,
    /*is_mandatory=*/false,
    /*description=*/"offWithEffect"};

// onWithRecallGlobalScene command
const CommandDescriptor onWithRecallGlobalSceneCmdDescriptor{
    /*cmd_id=*/65,
    /*is_common=*/false,
    /*is_mandatory=*/false,
    /*description=*/"onWithRecallGlobalScene"};

// onWithTimedOff command
const CommandDescriptor onWithTimedOffCmdDescriptor{
    /*cmd_id=*/66,
    /*is_common=*/false,
    /*is_mandatory=*/false,
    /*description=*/"onWithTimedOff"};

//////////////////////////////

// Cluster descriptor
const cluster_descriptor_t cluster_descriptor{/*id=*/6,
                                              /*is_msp=*/false,
                                              /*description=*/"onOff"};

// OnOffCluster class
class OnOffCluster : public Cluster
{
 public:
  OnOffCluster()
      : Cluster(
            /*descriptor=*/cluster_descriptor,
            /*attribute_descriptors=*/
            {onOffAttributeDescriptor, onTimeAttributeDescriptor,
             offWaitTimeAttributeDescriptor})
  {
  }

  /**
   * @brief Trigger OFF command
   *
   * @return ZclStatus
   */
  ZclStatus setOffCommand();

  /**
   * @brief Trigger ON command
   *
   * @return ZclStatus
   */
  ZclStatus setOnCommand();

  /**
   * @brief Trigger TOGGLE command
   *
   * @return ZclStatus
   */
  ZclStatus toggleCommand();

  /**
   * @brief Trigger OFF_WITH_EFFECT command
   *
   * @param effectIdentifier
   * @param effectVariant
   * @return ZclStatus
   */

  ZclStatus offWithEffectCommand(uint8_t  effectIdentifier,
                                 uint16_t effectVariant);

  /**
   * @brief Trigger ON_WITH_RECALL_GLOBAL_SCENE command
   *
   * @return ZclStatus
   */

  ZclStatus onWithRecallGlobalSceneCommand();

  /**
   * @brief Trigger ON_WITH_TIMED_OFF command
   *
   * @param onOffControl
   * @param onTime
   * @param offWaitTime
   * @return ZclStatus
   */
  ZclStatus onWithTimedOffCommand(uint8_t onOffControl, uint16_t onTime,
                                  uint16_t offWaitTime);
};
}  // namespace zcl::on_off_cluster

#endif  // ZCL_CLUSTERS_ON_OFF_CLUSTER_HPP
