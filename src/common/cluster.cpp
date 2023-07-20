#include <zcl/common/cluster.hpp>

namespace zcl
{

// Method to get the list of attributes
const attributes_list_t& Cluster::get_attributes() const { return attributes; }

// Method to get the cluster descriptor
const cluster_descriptor_t& Cluster::get_descriptor() const
{
  return descriptor;
}

// Method to get a constant reference to the attribute with the given attribute
// ID
const Attribute& Cluster::get_attribute_const(attr_id_t attr_id) const
{
  for (const auto& attr : attributes)
  {
    if (attr.get_id() == attr_id)
    {
      return attr;
    }
  }
  throw std::runtime_error("Attribute not found");
}

// Method to get a non-constant reference to the attribute with the given
// attribute ID
Attribute& Cluster::get_attribute_not_const(attr_id_t attr_id)
{
  for (auto& attr : attributes)
  {
    if (attr.get_id() == attr_id)
    {
      return attr;
    }
  }
  throw std::runtime_error("Attribute not found");
}

// Method to get the value of the attribute with the given attribute ID
attr_value_t Cluster::get_attribute_value(attr_id_t attr_id) const
{
  const Attribute& attr = get_attribute_const(attr_id);
  return attr.get_value();
}

// Method to set the value of the attribute with the given attribute ID
void Cluster::set_attribute_value(attr_id_t attr_id, const attr_value_t& value)
{
  Attribute& attr = get_attribute_not_const(attr_id);
  attr.set_value(value);
}

}  // namespace zcl
