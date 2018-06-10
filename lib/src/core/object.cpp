#include "core/object.h"

#include <assert.h>
#include <algorithm>

#include "core/tag.h"
#include "core/scene.h"
#include "core/property.h"

const std::string Object::TRANSFORMATION_PROPERTY_KEY = "transformation";
const std::string Object::NAME_PROPERTY_KEY = "name";

Object::Object(Scene& scene)
  : m_parent(nullptr)
  , m_scene(scene)
{
  addProperty( TRANSFORMATION_PROPERTY_KEY,
               std::make_unique<TransformationProperty>(Object::identity()) );
  addProperty( NAME_PROPERTY_KEY,
               std::make_unique<StringProperty>("<Unnamed Object>") );
}

Object::~Object()
{
  LOG(INFO) << "DELETE Object(" << (void*) this << ")";
}

ObjectTransformation Object::transformation() const
{
  return propertyValue<ObjectTransformation>(TRANSFORMATION_PROPERTY_KEY);
}

ObjectTransformation Object::globalTransformation() const
{
  assert(this != nullptr);

  if (isRoot()) {
    return transformation();
  } else {
    return parent().globalTransformation() * transformation();
  }
}

void Object::setTransformation(const ObjectTransformation& transformation)
{
  setPropertyValue(TRANSFORMATION_PROPERTY_KEY, transformation);
}

void Object::setGlobalTransformation(const ObjectTransformation& globalTransformation)
{
  ObjectTransformation localTransformation;
  if (isRoot()) {
    localTransformation = globalTransformation;
  } else {
    try {
      localTransformation = parent().globalTransformation().i() * globalTransformation;
    } catch (const std::runtime_error& e) {
      assert(false);
    }
  }
  setTransformation(localTransformation);
}

bool Object::isRoot() const
{
  return m_parent == nullptr;
}

Object& Object::parent() const
{
  assert(!isRoot());
  return *m_parent;
}

std::vector<std::reference_wrapper<Object>> Object::children() const
{
  return m_children;
}

void Object::addChild(Object& child)
{
  m_children.push_back(child);
}

void Object::removeChild(Object& child)
{
  m_children.erase(
    std::remove_if( m_children.begin(), 
                    m_children.end(),
                    [&](const std::reference_wrapper<Object>& i) {
    return &i.get() == &child;
  }));
}

void Object::setParent(Object& parent)
{
  assert(&parent != this);
  const ObjectTransformation globalTransformation = this->globalTransformation();
  if (m_parent != nullptr) {
    m_parent->removeChild(*this);
  }
  m_parent = &parent;
  m_parent->addChild(*this);
  setGlobalTransformation(globalTransformation);
}

void Object::transform(const ObjectTransformation& transformation)
{
  setTransformation(transformation * this->transformation());
}

std::vector<std::reference_wrapper<Tag>> Object::tags() const
{
  std::vector<std::reference_wrapper<Tag>> tags;
  tags.reserve(m_tags.size());
  for (const std::unique_ptr<Tag>& tag : m_tags) {
    tags.push_back(std::ref(*tag));
  }
  return tags;
}

Scene& Object::scene() const
{
  return m_scene;
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
