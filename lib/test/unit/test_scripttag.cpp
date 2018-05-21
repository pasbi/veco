/* Copyright 2018 K|Lens */

#include "gtest/gtest.h"
#include "tags/scripttag.h"
#include "core/object.h"
#include "core/scene.h"

TEST(ScriptTag_Test, Default)
{
  Object* o = new Object(Scene::instance()->root());
  ScriptTag* tag = new ScriptTag(o);

  const std::string code = "print(o.scene())";
  tag->setPropertyValue(ScriptTag::CODE_PROPERTY_KEY, code);

  tag->run();
  // ASSERT_TRUE(true);
}



// TEST(ScriptTag_umlaut_Test, Default)
// {
//   ScriptTag* tag = new ScriptTag();
//   const std::string code = "print('ä')";
//   tag->setPropertyValue(ScriptTag::CODE_PROPERTY_KEY, code);
//   tag->run();
//   delete tag;
// }

