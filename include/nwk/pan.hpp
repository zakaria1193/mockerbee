#ifndef NWK_PAN_HPP
#define NWK_PAN_HPP

#include <cstdint>

namespace nwk
{

using pan_id_t = uint16_t;

class Pan
{
  pan_id_t pan_id{};
  bool     permit_joining{false};

 public:
  explicit Pan(pan_id_t pan_id) : pan_id(pan_id) {}

  [[nodiscard]] pan_id_t get_pan_id() const { return pan_id; }
  [[nodiscard]] bool     is_permit_joining() const { return permit_joining; }

  void set_permit_joining(bool permit_joining)
  {
    this->permit_joining = permit_joining;
  }
};

}  // namespace nwk

#endif  // NWK_PAN_HPP
