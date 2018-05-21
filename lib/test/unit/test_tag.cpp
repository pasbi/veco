/* Copyright 2018 K|Lens */

#include "gtest/gtest.h"
#include "core/tag.h"
#include "core/object.h"
#include "core/scene.h"

TEST(Tag_Test, Default)
{
  Object* o = new Object(Scene::instance()->root());
  Tag* tag = new Tag(o);
  const std::string name = "tag name";
  tag->setPropertyValue(Tag::NAME_PROPERTY_KEY, name);
  ASSERT_EQ(tag->propertyValue<std::string>(Tag::NAME_PROPERTY_KEY), name);
}