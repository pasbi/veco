#pragma once

#include <memory>
#include "core/hasproperties.h"

class Object;
class Scene;

class Tag : public HasProperties
{
public:
  explicit Tag(Object& owner);
  virtual ~Tag();
  Object& owner() const;

  virtual bool run();

  static const std::string NAME_PROPERTY_KEY;
  Scene& scene() const;

private:
  Object& m_owner;
};
