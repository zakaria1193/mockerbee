#ifndef ZCL_CLUSTERS_ON_OFF_CLUSTER_HPP
#define ZCL_CLUSTERS_ON_OFF_CLUSTER_HPP

#include <zcl/common/attributes.hpp>
#include <zcl/common/cluster.hpp>
#include <zcl/common/commands.hpp>
#include <zcl/common/zcl_status.hpp>

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
const CommandDescriptor setOffCmdDescriptor{/*cmd_id=*/0,
                                            /*is_common=*/false,
                                            /*is_mandatory=*/true,
                                            /*description=*/"setOff"};
ZclStatus               setOffExecuter(Cluster &cluster);
const Command           setOffCommand{/*exec=*/setOffExecuter};

// setOn command
const CommandDescriptor setOnCmdDescriptor{/*cmd_id=*/1,
                                           /*is_common=*/false,
                                           /*is_mandatory=*/true,
                                           /*description=*/"setOn"};
ZclStatus               setOnExecuter(Cluster &cluster);
const Command           setOnCommand{/*exec=*/setOnExecuter};

// toggle command
const CommandDescriptor toggleCmdDescriptor{/*cmd_id=*/2,
                                            /*is_common=*/false,
                                            /*is_mandatory=*/true,
                                            /*description=*/"toggle"};
ZclStatus               toggleExecuter(Cluster &cluster);
const Command           toggleCommand{/*exec=*/toggleExecuter};

// offWithEffect command
const CommandDescriptor offWithEffectCmdDescriptor{
    /*cmd_id=*/64,
    /*is_common=*/false,
    /*is_mandatory=*/false,
    /*description=*/"offWithEffect"};
ZclStatus     offWithEffectExecuter(Cluster &cluster, uint8_t effectIdentifier,
                                    uint16_t effectVariant);
const Command offWithEffectCommand{/*exec=*/offWithEffectExecuter};

// onWithRecallGlobalScene command
const CommandDescriptor onWithRecallGlobalSceneCmdDescriptor{
    /*cmd_id=*/65,
    /*is_common=*/false,
    /*is_mandatory=*/false,
    /*description=*/"onWithRecallGlobalScene"};
ZclStatus     onWithRecallGlobalSceneExecuter(Cluster &cluster);
const Command onWithRecallGlobalSceneCommand{
    /*exec=*/onWithRecallGlobalSceneExecuter};

// onWithTimedOff command
const CommandDescriptor onWithTimedOffCmdDescriptor{
    /*cmd_id=*/66,
    /*is_common=*/false,
    /*is_mandatory=*/false,
    /*description=*/"onWithTimedOff"};
ZclStatus     onWithTimedOffExecuter(Cluster &cluster, uint8_t onOffControl,
                                     uint16_t onTime, uint16_t offWaitTime);
const Command onWithTimedOffCommand{/*exec=*/onWithTimedOffExecuter};

//////////////////////////////

// Cluster descriptor
const cluster_descriptor_t cluster_descriptor{/*id=*/6,
                                              /*is_msp=*/false,
                                              /*description=*/"onOff"};

const commands_map_t on_off_commands_map = {
    {setOffCmdDescriptor,
     static_cast<const CommandBase *const>(&setOffCommand)},
};

// OnOffCluster class
class OnOffCluster : public Cluster
{
 public:
  OnOffCluster()
      : Cluster(
            /*descriptor=*/cluster_descriptor,
            /*attribute_descriptors=*/
            {onOffAttributeDescriptor, onTimeAttributeDescriptor,
             offWaitTimeAttributeDescriptor},
            /*commands_map=*/on_off_commands_map)
  {
  }
};
}  // namespace zcl::on_off_cluster

#endif  // ZCL_CLUSTERS_ON_OFF_CLUSTER_HPP
