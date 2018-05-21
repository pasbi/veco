/* Copyright 2018 K|Lens */

#include <glog/logging.h>

#include "gtest/gtest.h"
#include "core/object.h"
#include "core/scene.h"

namespace arma {
bool operator==(const ObjectTransformation& a, const ObjectTransformation& b)
{
  return approx_equal(a, b, "absdiff", 1e-15);
}
}

TEST(Object_Tree_Test, Default)
{
  Scene* scene = Scene::instance();
  Object* child1 = new Object(scene->root());
  Object* child2 = new Object(scene->root());

  const ObjectTransformation gtC1 = Object::rotation(M_PI/4) 
                                  * Object::translation(1, 2)
                                  * Object::scalation(3, 4);

  child1->setGlobalTransformation(gtC1);
  child2->setTransformation(gtC1);
  EXPECT_EQ(child1->globalTransformation(), child2->globalTransformation());
  EXPECT_EQ(child1->transformation(), child2->transformation());

  child1->setParent(scene->root());
  EXPECT_EQ(child1->globalTransformation(), child2->globalTransformation());

  child2->setParent(child1);
  EXPECT_EQ(child2->transformation(), Object::identity());

  child2->setGlobalTransformation(Object::identity());
  const ObjectTransformation gtC2inv = child1->globalTransformation().i();
  EXPECT_EQ(child2->transformation(), gtC2inv);
}

TEST(Object_Property_Test, Default)
{
  const std::string name = "testname";
  Scene* scene = Scene::instance();
  scene->root()->setPropertyValue(Object::NAME_PROPERTY_KEY, name);
  ASSERT_EQ(scene->root()->propertyValue<std::string>(Object::NAME_PROPERTY_KEY), name);
}
