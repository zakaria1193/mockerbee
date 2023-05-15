#ifndef ZCL_STATUS_HPP
#define ZCL_STATUS_HPP

namespace zcl
{
enum class ZclStatus
{
  success         = 0,
  timeout         = -1,
  null_pointer    = -2,
  not_implemented = -3,
  route_error     = -4,
};
}  // namespace zcl

#endif  // ZCL_STATUS_HPP
