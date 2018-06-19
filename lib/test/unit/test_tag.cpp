/* Copyright 2018 K|Lens */

#include "gtest/gtest.h"
#include "core/tag.h"
#include "core/object.h"
#include "core/scene.h"

TEST(Tag_Test, Default)
{
  Scene scene;

  Tag& tag = scene.root().create_tag<Tag>();

  const std::string name = "tag name";
  tag.property(Tag::NAME_PROPERTY_KEY).cast<std::string>().set_value(name);
  ASSERT_EQ(tag.property(Tag::NAME_PROPERTY_KEY).cast<std::string>().value(), name);
}