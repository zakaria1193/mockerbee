#pragma once
#include <zcl/common/attributes.hpp>
#include <zcl/common/cluster.hpp>
#include <zcl/common/commands.hpp>
#include <zcl/common/zcl_status.hpp>

namespace zcl::on_off_cluster
{
using namespace zcl;

// Attribute descriptors
const AttributeDescriptor onOffAttributeDescriptor(
    /*id=*/0,
    /*is_msp=*/false,
    /*is_reportable=*/false,
    /*is_readable=*/true,
    /*is_writable=*/true,
    /*is_mandatory=*/true,
    /*description=*/"onOff");
const AttributeDescriptor onTimeAttributeDescriptor(
    /*id=*/16385,
    /*is_msp=*/false,
    /*is_reportable=*/false,
    /*is_readable=*/true,
    /*is_writable=*/true,
    /*is_mandatory=*/false,
    /*description=*/"onTime");
const AttributeDescriptor offWaitTimeAttributeDescriptor(
    /*id=*/16386,
    /*is_msp=*/false,
    /*is_reportable=*/false,
    /*is_readable=*/true,
    /*is_writable=*/true,
    /*is_mandatory=*/false,
    /*description=*/"offWaitTime");

//////////////////////////////
// Command descriptors
//////////////////////////////
const command_descriptor_t setOffCmdDescriptor{/*id=*/0,
                                               /*is_common=*/false,
                                               /*is_mandatory=*/true,
                                               /*description=*/"setOff"};
ZclStatus                  setOffExecuter(Cluster &cluster);
const Command              setOffCommand{/*executer=*/setOffExecuter};

const command_descriptor_t setOnCmdDescriptor{/*id=*/1,
                                              /*is_common=*/false,
                                              /*is_mandatory=*/true,
                                              /*description=*/"setOn"};
ZclStatus                  setOnExecuter(Cluster &cluster);
const Command              setOnCommand{/*executer=*/setOnExecuter};

const command_descriptor_t toggleCmdDescriptor{/*id=*/2,
                                               /*is_common=*/false,
                                               /*is_mandatory=*/true,
                                               /*description=*/"toggle"};
ZclStatus                  toggleExecuter(Cluster &cluster);
const Command              toggleCommand{/*executer=*/toggleExecuter};

const command_descriptor_t offWithEffectCmdDescriptor{
    /*id=*/64,
    /*is_common=*/false,
    /*is_mandatory=*/false,
    /*description=*/"offWithEffect"};
ZclStatus     offWithEffectExecuter(Cluster &cluster, uint8_t effectIdentifier,
                                    uint16_t effectVariant);
const Command offWithEffectCommand{/*executer=*/offWithEffectExecuter};

const command_descriptor_t onWithRecallGlobalSceneCmdDescriptor{
    /*id=*/65,
    /*is_common=*/false,
    /*is_mandatory=*/false,
    /*description=*/"onWithRecallGlobalScene"};
ZclStatus     onWithRecallGlobalSceneExecuter(Cluster &cluster);
const Command onWithRecallGlobalSceneCommand{
    /*executer=*/onWithRecallGlobalSceneExecuter};

const command_descriptor_t onWithTimedOffCmdDescriptor{
    /*id=*/66,
    /*is_common=*/false,
    /*is_mandatory=*/false,
    /*description=*/"onWithTimedOff"};
ZclStatus     onWithTimedOffExecuter(Cluster &cluster, uint8_t onOffControl,
                                     uint16_t onTime, uint16_t offWaitTime);
const Command onWithTimedOffCommand{/*executer=*/onWithTimedOffExecuter};

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
             offWaitTimeAttributeDescriptor},
            /*commands_map=*/
            {
                {setOffCmdDescriptor,
                 static_cast<const CommandBase *const>(&setOffCommand)},
            })
  {
  }
};
}  // namespace zcl::on_off_cluster
