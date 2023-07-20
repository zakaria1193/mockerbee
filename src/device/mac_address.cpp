#include <device/mac_address.hpp>
#include <iomanip>
#include <iostream>

namespace device
{
[[nodiscard]] std::string MacAddress::get_string() const
{
  std::stringstream char_stream;
  // Format 00:AA:BB:CC:DD:EE:FF:00
  for (size_t i = 0; i < size; i++)
  {
    bool is_last = i == size - 1;
    char_stream << std::setfill('0') << std::setw(2) << std::hex
                << static_cast<int>(address[i]) << (is_last ? "" : ":");
  }

  return char_stream.str();
}

// Comparison operators
bool MacAddress::operator==(const MacAddress& rhs) const
{
  return address == rhs.address;
}

bool MacAddress::operator!=(const MacAddress& rhs) const
{
  return !(rhs == *this);
}

}  // namespace device
