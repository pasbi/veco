#pragma once

#include <string>
#include <typeinfo>
#include <unordered_set>
#include "core/types.h"

template<typename ValueT> class TypedProperty;
class Object;

#define DISABLE_DANGEROUS_PROPERTY_TYPE(T) \
  static_assert(!std::is_same<ValueT, T>(), \
                "Forbidden Property Type '"#T"'.");

// Disable some T in TypedProperty<T>
// Without this guard, it was easy to accidentally use the 
// TypedProperty<const char*> acidentally when you actually want
// TypedProperty<std::string>. It's hard to notice and things will 
// break at strange places so debugging it becomes ugly.
#define DISABLE_DANGEROUS_PROPERTY_TYPES \
  DISABLE_DANGEROUS_PROPERTY_TYPE(const char*)


class Property
{
public:
  Property();
  virtual ~Property();

  template<typename ValueT> bool is_type() const
  {
    return cast<ValueT>() != nullptr;
  }

  template<typename ValueT> const TypedProperty<ValueT>* cast() const
  {
    DISABLE_DANGEROUS_PROPERTY_TYPES
    return dynamic_cast<const TypedProperty<ValueT>*>(this);
  }

  template<typename ValueT> TypedProperty<ValueT>* cast() 
  {
    DISABLE_DANGEROUS_PROPERTY_TYPES
    return dynamic_cast<TypedProperty<ValueT>*>(this);
  }
};

template<typename ValueT>
class TypedProperty : public Property

{
protected:
  TypedProperty(ValueT defaultValue)
    : Property()
    , m_value(defaultValue)
    , m_defaultValue(defaultValue)
  {
  }
  
public:
  virtual void setValue(ValueT value)
  {
    m_value = value;
  }

  virtual ValueT value() const
  {
    return m_value;
  }

  virtual ValueT& value()
  {
    return m_value;
  }

  virtual void reset()
  {
    m_value = m_defaultValue;
  }

  std::type_info type() const
  {
    return typeid(ValueT);
  }

private:
  ValueT m_value;
  const ValueT m_defaultValue;
};

class IntegerProperty : public TypedProperty<int>
{
public:
  explicit IntegerProperty(const int& defaultValue);
};

class FloatProperty : public TypedProperty<double>
{
public:
  explicit FloatProperty(const double& defaultValue);
};

class StringProperty : public TypedProperty<std::string>
{
public:
  explicit StringProperty(const std::string& defaultValue);
};

class TransformationProperty : public TypedProperty<ObjectTransformation>
{
public:
  explicit TransformationProperty(const ObjectTransformation& defaultValue);
};


class ReferenceProperty : public TypedProperty<Object*>
{
public:
  ReferenceProperty();
  static bool isReferenced(const Object* candidate);
  void setValue(Object* value) override;

private:
  static std::unordered_set<const Object*> m_references;
};