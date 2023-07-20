#include <nwk/pan.hpp>

namespace nwk
{
Pan::Pan(pan_id_t pan_id) : pan_id(pan_id) {}

pan_id_t Pan::get_pan_id() const { return pan_id; }
bool     Pan::is_permit_joining() const { return permit_joining; }

void Pan::set_permit_joining(bool permit_joining)
{
  this->permit_joining = permit_joining;
}
}  // namespace nwk
