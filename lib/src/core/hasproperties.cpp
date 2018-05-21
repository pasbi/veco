#include "core/hasproperties.h"

HasProperties::Properties HasProperties::properties() const
{
  return m_properties;
}

HasProperties::~HasProperties()
{
  for (const auto& key_property : m_properties) {
    delete key_property.second;
  }
}

void HasProperties::addProperty(const PropertyKey& key, Property* property)
{
  //TODO append name of current class, exploit that class name in super constructor is `super`.
  const bool notExistedBefore = m_properties.insert(std::make_pair(key, property)).second;
  assert(notExistedBefore);
}

