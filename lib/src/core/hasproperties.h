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

  Property& property(const PropertyKey& key) const
  {
    return *m_properties.at(key);
  }

  PropertyKey make_property_key(const std::string& name) const;

protected:
  void add_property(const PropertyKey& key, std::unique_ptr<Property> property);

private:
  Properties m_properties;

};
