#include "core/object.h"

#include <assert.h>
#include <algorithm>

#include "core/tag.h"
#include "core/scene.h"
#include "core/property.h"

const std::string Object::TRANSFORMATION_PROPERTY_KEY = "transformation";
const std::string Object::NAME_PROPERTY_KEY = "name";

Object::Object(Scene* scene)
  : m_parent(nullptr)
  , m_scene(scene)
{
  addProperty( TRANSFORMATION_PROPERTY_KEY,
               new TransformationProperty(Object::identity()) );
  addProperty( NAME_PROPERTY_KEY,
               new StringProperty("<Unnamed Object>") );
}

Object::Object(Object* parent)
  : Object(parent->scene())
{
  setParent(parent);
  m_scene->add(this);
}

Object::~Object()
{
  LOG(INFO) << "DELETE Object(" << (void*) this << ")";
  for (const Tag* tag : m_tags) {
    delete tag;
  }

  for (const Object* child : m_children) {
    delete child;
  }
}

ObjectTransformation Object::transformation() const
{
  return propertyValue<ObjectTransformation>(TRANSFORMATION_PROPERTY_KEY);
}

ObjectTransformation Object::globalTransformation() const
{
  if (parent()) {
    return parent()->globalTransformation() * transformation();
  } else {
    return transformation();
  }
}

void Object::setTransformation(const ObjectTransformation& transformation)
{
  setPropertyValue(TRANSFORMATION_PROPERTY_KEY, transformation);
}

void Object::setGlobalTransformation(const ObjectTransformation& globalTransformation)
{
  ObjectTransformation localTransformation;
  if (parent()) {
    try {
      localTransformation = parent()->globalTransformation().i() * globalTransformation;
    } catch (const std::runtime_error& e) {
      assert(false);
    }
  } else {
    localTransformation = globalTransformation;
  }
  setTransformation(localTransformation);
}

Object* Object::parent() const
{
  return m_parent;
}

std::vector<Object*> Object::children() const
{
  return m_children;
}

void Object::setParent(Object* parent)
{
  const ObjectTransformation t = globalTransformation();
  if (m_parent) {
    std::vector<Object*>& pcs = m_parent->m_children;
    assert(std::count(pcs.begin(), pcs.end(), this) == 1);
    pcs.erase(std::remove(pcs.begin(), pcs.end(), this), pcs.end());
  }
  m_parent = parent;
  if (m_parent) {
    std::vector<Object*>& pcs = m_parent->m_children;
    assert(std::count(pcs.begin(), pcs.end(), this) == 0);
    m_parent->m_children.push_back(this);
  }
  setGlobalTransformation(t);
}

void Object::transform(const ObjectTransformation& transformation)
{
  setTransformation(transformation * this->transformation());
}

ObjectTransformation Object::translation(const Float& dx, const Float dy)
{
  ObjectTransformation t = identity();
  t.at(0, 2) = dx;
  t.at(1, 2) = dy;
  return t;
}

ObjectTransformation Object::rotation(const Float& alpha)
{
  ObjectTransformation t = identity();
  t.at(0, 0) = cos(alpha);
  t.at(1, 1) = t.at(0, 0);
  t.at(0, 1) = sin(alpha);
  t.at(1, 0) = -t.at(0, 1);
  return t;
}

ObjectTransformation Object::scalation(const Float& sx, const Float sy)
{
  ObjectTransformation t = identity();
  t.at(0, 0) = sx;
  t.at(1, 1) = sy;
  return t;
}

ObjectTransformation Object::identity()
{
  ObjectTransformation t;
  t.eye();
  return t;
}

void Object::addTag(Tag* tag)
{
  assert(tag->owner() == this);
  m_tags.push_back(tag);
}

std::vector<Tag*> Object::tags() const
{
  return m_tags;
}

Scene* Object::scene() const
{
  return m_scene;
}

Object* Object::createRootInstance(Scene* scene)
{
  Object* rootInstance = new Object(scene);
  rootInstance->setPropertyValue(NAME_PROPERTY_KEY, std::string("root"));
  return rootInstance;
}