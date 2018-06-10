/* Copyright 2018 K|Lens */

#include "gtest/gtest.h"
#include "tags/scripttag.h"
#include "core/object.h"
#include "core/scene.h"

TEST(ScriptTag_Test, Default)
{
  Scene scene;
  ScriptTag& tag = scene.new_object<Object>().new_tag<ScriptTag>();

  const std::string code = "print(o.scene())";
  tag.setPropertyValue(ScriptTag::CODE_PROPERTY_KEY, code);

  tag.run();
}

TEST(ScriptTag_umlaut_Test, Default)
{
  Scene scene;
  ScriptTag& tag = scene.new_object<Object>().new_tag<ScriptTag>();

  const std::string code = "print('ä')";
  tag.setPropertyValue(ScriptTag::CODE_PROPERTY_KEY, code);
  tag.run();
}

