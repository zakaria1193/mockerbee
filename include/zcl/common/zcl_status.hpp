#pragma once

namespace zcl
{

  enum class ZclStatus
  {
    success = 0,
    timeout = -1,
    null_pointer = -2,
    not_implemented = -3,
  };
}
