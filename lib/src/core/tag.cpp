#include "core/tag.h"
#include "core/object.h"

const std::string Tag::NAME_PROPERTY_KEY = "name";

Tag::Tag(Object* owner)
  : m_owner(owner)
{
  m_owner->addTag(this);
  addProperty( NAME_PROPERTY_KEY,
               new StringProperty("<Unnamed Tag>") );
}

Tag::~Tag()
{
  
}

Object* Tag::owner() const
{
  return m_owner;
}

Scene* Tag::scene() const
{
  return m_owner->scene();
}

bool Tag::run()
{
  return false;
}