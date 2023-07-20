#ifndef MAC_ADDRESS_HPP
#define MAC_ADDRESS_HPP

#include <array>

namespace device
{
const size_t MAC_ADDRESS_SIZE = 8;

class MacAddress
{
  using mac_address_value_t = std::array<uint8_t, MAC_ADDRESS_SIZE>;
  mac_address_value_t address{};
  size_t              size{};

 public:
  MacAddress() = delete;

  // Constructer from byte arg list using initializer list
  template <typename... Args>
  explicit MacAddress(Args... args);

  [[nodiscard]] std::string get_string() const;

  // Comparison operators
  bool operator==(const MacAddress& rhs) const;
  bool operator!=(const MacAddress& rhs) const;
};

}  // namespace device

#include "mac_address.ipp"

#endif  // MAC_ADDRESS_HPP
