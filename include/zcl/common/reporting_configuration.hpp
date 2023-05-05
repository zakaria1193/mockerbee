#ifndef ZCL_COMMON_REPORTING_CONFIGURATION_HPP
#define ZCL_COMMON_REPORTING_CONFIGURATION_HPP

#include <cstdint>

const uint16_t MAX_REPORTING_INTERVAL = 10*60; // 10 minutes

namespace zcl
{
class ReportingConfiguration
{
   uint16_t min_interval{0};
   uint16_t max_interval{};
   uint16_t min_reportable_change{1};

  public:
   ReportingConfiguration() = default;
   ReportingConfiguration(uint16_t min_interval,
                          uint16_t max_interval,
                          uint16_t min_reportable_change)
       : min_interval(min_interval),
         max_interval(max_interval),
         min_reportable_change(min_reportable_change)
   {
   }
};
}  // namespace zcl

#endif  // ZCL_COMMON_REPORTING_CONFIGURATION_HPP
