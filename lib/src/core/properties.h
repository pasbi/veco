// #pragma once

// #include <assert.h>

// #include "core/types.h"
// #include "core/property.h"

// class Properties
// {
// public:
//   ~Properties();

//   void add(const PropertyKey& key, Property* property);

//   template<typename T> void setValue(const PropertyKey& key, T value)
//   {
//     getProperty<T>(key)->setValue(value);
//   }

//   template<typename T> T value(const PropertyKey& key) const
//   {
//     return getProperty<T>(key)->value();
//   }

//   template<typename T> T& value(const PropertyKey& key)
//   {
//     return getProperty<T>(key)->value();
//   }

//   template<typename T> TypedProperty<T>* getProperty(const PropertyKey& key) const
//   {
//     TypedProperty<T>* property = dynamic_cast<TypedProperty<T>*>(m_properties.at(key));
//     assert(property != nullptr);
//     return property;
//   }

// };