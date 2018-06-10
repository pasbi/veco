#pragma once

#include <vector>
#include <memory>
#include "core/types.h"
#include "core/hasproperties.h"

class Property;
class Tag;
class Scene;

class Object : public HasProperties
{
public:
  Object(Scene& scene);
  virtual ~Object();

  bool isRoot() const;
  Object& parent() const;  // will fail if isRoot() == true
  std::vector<std::reference_wrapper<Object>> children() const;
  void setParent(Object& parent);

  void transform(const ObjectTransformation& transformation);
  ObjectTransformation transformation() const;
  ObjectTransformation globalTransformation() const;
  void setTransformation(const ObjectTransformation& transformation);
  void setGlobalTransformation(const ObjectTransformation& globalTransformation);

  std::string name() const { return propertyValue<std::string>(NAME_PROPERTY_KEY); }
  void setName(const std::string& name) { setPropertyValue(NAME_PROPERTY_KEY, name); }

  std::vector<std::reference_wrapper<Tag>> tags() const;

  template<typename TagT> TagT& new_tag() 
  {
    m_tags.push_back(std::make_unique<TagT>(*this));
    return static_cast<TagT&>(*m_tags.back());
  }

  Scene& scene() const;

  static ObjectTransformation translation(const Float& dx, const Float dy);
  static ObjectTransformation rotation(const Float& r);
  static ObjectTransformation scalation(const Float& sx, const Float sy);
  static ObjectTransformation identity();

  static const std::string TRANSFORMATION_PROPERTY_KEY;
  static const std::string NAME_PROPERTY_KEY;

private:
  std::vector<std::unique_ptr<Tag>> m_tags;
  std::vector<std::reference_wrapper<Object>> m_children;
  Object* m_parent;
  Scene& m_scene;

  void addChild(Object& child);
  void removeChild(Object& child);
};
