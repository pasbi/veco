/* Copyright 2018 K|Lens */

#include "gtest/gtest.h"
#include "tags/scripttag.h"
#include "core/object.h"
#include "core/scene.h"

TEST(ScriptTag_Test, Default)
{
  Scene scene;

  Tag& tag = scene.root().create_tag<ScriptTag>();


  const std::string code = "print(o.scene())";
  tag.property(ScriptTag::CODE_PROPERTY_KEY).cast<std::string>().set_value(code);

  tag.run();
}

TEST(ScriptTag_umlaut_Test, Default)
{
  Scene scene;
  ScriptTag& tag = scene.root().create_tag<ScriptTag>();

  const std::string code = "print('ä')";
  tag.property(ScriptTag::CODE_PROPERTY_KEY).cast<std::string>().set_value(code);
  tag.run();
}

TEST(ScriptTag_scene_Test, Default)
{
  Scene scene;
  ScriptTag& tag = scene.root().create_tag<ScriptTag>();
  scene.root().create_child<Object>();

  ASSERT_TRUE(tag.run());
}

