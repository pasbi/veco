#pragma once

#include <glog/logging.h>
#include <assert.h>
#include <map>
#include <typeinfo>
#include "core/property.h"

class HasProperties
{
public:
  typedef std::string PropertyKey;
  typedef std::map<PropertyKey, Property*> Properties;

  virtual ~HasProperties();

  Properties properties() const;

  template<typename T> void setPropertyValue(const PropertyKey& key, T value)
  {
    property<T>(key)->setValue(value);
  }

  template<typename T> T propertyValue(const PropertyKey& key) const
  {
    return property<T>(key)->value();
  }

  template<typename T> T& propertyValue(const PropertyKey& key)
  {
    return property<T>(key)->value();
  }

  template<typename T> TypedProperty<T>* property(const PropertyKey& key) const
  {
    TypedProperty<T>* property = nullptr;
    try {
      property = m_properties.at(key)->cast<T>();
    } catch (const std::out_of_range&) {
      LOG(FATAL) << "Tried to access non-existend propert: '" << key << "'.";
    }
    assert(property != nullptr);
    return property;
  }

protected:
  void addProperty(const PropertyKey& key, Property* property);

private:
  Properties m_properties;

};
