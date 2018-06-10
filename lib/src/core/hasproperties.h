#pragma once

#include <glog/logging.h>
#include <assert.h>
#include <map>
#include <memory>
#include <typeinfo>
#include "core/property.h"

class HasProperties
{
public:
  using PropertyKey = std::string;
  using Properties = std::map<PropertyKey, std::unique_ptr<Property>>;

  virtual ~HasProperties();

  template<typename T> void setPropertyValue(const PropertyKey& key, T value)
  {
    property<T>(key).setValue(value);
  }

  template<typename T> T propertyValue(const PropertyKey& key) const
  {
    return property<T>(key).value();
  }

  template<typename T> T& propertyValue(const PropertyKey& key)
  {
    return property<T>(key).value();
  }

  template<typename T> TypedProperty<T>& property(const PropertyKey& key) const
  {
    try {
      TypedProperty<T>& property = m_properties.at(key)->cast<T>();
      return property;
    } catch (const std::out_of_range&) {
      LOG(FATAL) << "Tried to access non-existend property: '" << key << "'.";
      exit(1);
    }
  }

  PropertyKey makePropertyKey(const std::string& name) const;

protected:
  void addProperty(const PropertyKey& key, std::unique_ptr<Property> property);

private:
  Properties m_properties;

};
