#include "core/hasproperties.h"

HasProperties::~HasProperties()
{
}

HasProperties::PropertyKey HasProperties::make_property_key(const std::string& name) const
{
  //TODO append name of current class, exploit that class name in super constructor is `super`.
  return name;
}

void HasProperties::add_property(const PropertyKey& key, std::unique_ptr<Property> property)
{
  assert(m_properties.count(key) == 0);
  m_properties[key] = std::move(property);
}

