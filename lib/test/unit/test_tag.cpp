/* Copyright 2018 K|Lens */

#include "gtest/gtest.h"
#include "core/tag.h"
#include "core/object.h"
#include "core/scene.h"

TEST(Tag_Test, Default)
{
  Scene scene;
  Tag& tag = scene.new_object<Object>().new_tag<Tag>();
  const std::string name = "tag name";
  tag.setPropertyValue(Tag::NAME_PROPERTY_KEY, name);
  ASSERT_EQ(tag.propertyValue<std::string>(Tag::NAME_PROPERTY_KEY), name);
}