#include "core/property.h"
#include <algorithm>
#include <assert.h>

std::unordered_set<const Object*> ReferenceProperty::m_references;

Property::Property()
{
}

Property::~Property()
{

}

ReferenceProperty::ReferenceProperty()
  : TypedProperty<Object*>(nullptr)
{
}

bool ReferenceProperty::isReferenced(const Object* candidate)
{
  return std::find(m_references.begin(), m_references.end(), candidate) != m_references.end();
}

void ReferenceProperty::setValue(Object* reference)
{
  const Object* oldReference = value();
  if (oldReference != nullptr) {
    assert(isReferenced(oldReference
      ));
    m_references.erase(oldReference);
  }
  TypedProperty<Object*>::setValue(reference);
  if (reference != nullptr) {
    m_references.emplace(reference);
  }
}

IntegerProperty::IntegerProperty(const int& defaultValue)
  : TypedProperty<int>(defaultValue)
{
}

FloatProperty::FloatProperty(const double& defaultValue)
  : TypedProperty<double>(defaultValue)
{
}

StringProperty::StringProperty(const std::string& defaultValue)
  : TypedProperty<std::string>(defaultValue)
{
}

TransformationProperty::TransformationProperty(const ObjectTransformation& defaultValue)
  : TypedProperty<ObjectTransformation>(defaultValue)
{
}
