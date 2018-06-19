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

TEST(Object_Test, Default)
{
  Scene scene;
  Object& child1 = scene.root().create_child<Object>();
  Object& child2 = scene.root().create_child<Object>();
  scene.root().repudiate(child1);
  scene.root().repudiate(child2);
}

TEST(Object_Tree_Test, Default)
{ 
  Scene scene;
  Object& root = scene.root();
  auto child1 = std::make_unique<Object>(scene);
  auto child2 = std::make_unique<Object>(scene);

  const ObjectTransformation gtC1 = Object::rotation(M_PI/4) 
                                  * Object::translation(1, 2)
                                  * Object::scalation(3, 4);
  child1->set_global_transformation(gtC1);
  child2->set_transformation(gtC1);
  EXPECT_EQ(child1->global_transformation(), child2->global_transformation());
  EXPECT_EQ(child1->transformation(), child2->transformation());

  Object& c1ref = root.adopt(std::move(child1));
  EXPECT_EQ(c1ref.global_transformation(), child2->global_transformation());

  Object& c2ref = c1ref.adopt(std::move(child2));
  EXPECT_EQ(c2ref.transformation(), Object::identity());

  c2ref.set_global_transformation(Object::identity());
  const ObjectTransformation gtC2inv = c1ref.global_transformation().i();
  EXPECT_EQ(c2ref.transformation(), gtC2inv);
}

TEST(Object_Property_Test, Default)
{
  const std::string name = "testname";
  Scene scene;
  Object& root = scene.root();
  root.property(Object::NAME_PROPERTY_KEY).cast<std::string>().set_value(name);
  ASSERT_EQ(root.property(Object::NAME_PROPERTY_KEY).cast<std::string>().value(), name);
}
