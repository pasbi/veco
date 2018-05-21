#pragma once

#include <vector>
#include "core/types.h"
#include "core/hasproperties.h"

class Property;
class Tag;
class Scene;

class Object : public HasProperties
{
private:
  /**
   * @brief The only purpose of this constructor is to create a root object.
   *  Use `Object::createRootInstance()`.
   */
  Object(Scene* scene);
public:
  explicit Object(Object* parent);
  virtual ~Object();

  Object* parent() const;
  std::vector<Object*> children() const;
  void setParent(Object* parent);

  void transform(const ObjectTransformation& transformation);
  ObjectTransformation transformation() const;
  ObjectTransformation globalTransformation() const;
  void setTransformation(const ObjectTransformation& transformation);
  void setGlobalTransformation(const ObjectTransformation& globalTransformation);

  std::string name() const { return propertyValue<std::string>(NAME_PROPERTY_KEY); }
  void setName(const std::string& name) { setPropertyValue(NAME_PROPERTY_KEY, name); }

  void addTag(Tag* tag);
  std::vector<Tag*> tags() const;

  Scene* scene() const;

  static ObjectTransformation translation(const Float& dx, const Float dy);
  static ObjectTransformation rotation(const Float& r);
  static ObjectTransformation scalation(const Float& sx, const Float sy);
  static ObjectTransformation identity();

  static const std::string TRANSFORMATION_PROPERTY_KEY;
  static const std::string NAME_PROPERTY_KEY;

  static Object* createRootInstance(Scene* scene);

private:
  Properties m_properties;
  std::vector<Tag*> m_tags;
  std::vector<Object*> m_children;
  Object* m_parent;
  Scene* const m_scene;
};
