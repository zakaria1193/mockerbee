// Template function implementation for MacAddress class
// Reminder : Template functions must be implemented in the header file
// otherwise the compiler will not be able to instantiate the template
// and the linker will not be able to find the implementation.

#include <iostream>

namespace device
{
// Constructer from byte arg list using initializer list
template <typename... Args>
MacAddress::MacAddress(Args... args) : size(sizeof...(args))
{
  size_t index = 0;

  if (size > MacAddress::address.size())
  {
    throw std::runtime_error("MacAddress constructor received too many bytes");
  }

  for (auto arg : {args...})
  {
    address[index++] = arg;
  }

  std::cout << "MacAddress created with " << size << " bytes" << std::endl;
}
}  // namespace device
