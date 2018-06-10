// /* Copyright 2018 K|Lens */

// #include <glog/logging.h>

// #include "gtest/gtest.h"
// #include "core/object.h"
// #include "core/scene.h"

// namespace arma {
// bool operator==(const ObjectTransformation& a, const ObjectTransformation& b)
// {
//   return approx_equal(a, b, "absdiff", 1e-15);
// }
// }

// TEST(Object_Test, Default)
// {
//   Scene scene;
//   Object& child1 = scene.new_object<Object>();
//   Object& child2 = scene.new_object<Object>();
//   scene.remove(child1);

//   Object& child3 = scene.new_object<Object>();
//   child2.setParent(child3);
//   scene.remove(child2);

//   LOG(INFO) << "Delete scene ...";
// }

// TEST(Object_Tree_Test, Default)
// { 
//   Scene scene;
//   Object& root = scene.new_object<Object>();
//   Object& child1 = scene.new_object<Object>();
//   Object& child2 = scene.new_object<Object>();
//   const ObjectTransformation gtC1 = Object::rotation(M_PI/4) 
//                                   * Object::translation(1, 2)
//                                   * Object::scalation(3, 4);
//   child1.setGlobalTransformation(gtC1);
//   child2.setTransformation(gtC1);
//   EXPECT_EQ(child1.globalTransformation(), child2.globalTransformation());
//   EXPECT_EQ(child1.transformation(), child2.transformation());

//   child1.setParent(root);
//   EXPECT_EQ(child1.globalTransformation(), child2.globalTransformation());

//   child2.setParent(child1);
//   EXPECT_EQ(child2.transformation(), Object::identity());

//   child2.setGlobalTransformation(Object::identity());
//   const ObjectTransformation gtC2inv = child1.globalTransformation().i();
//   EXPECT_EQ(child2.transformation(), gtC2inv);
// }

// TEST(Object_Property_Test, Default)
// {
//   const std::string name = "testname";
//   Scene scene;
//   Object& root = scene.new_object<Object>();
//   root.setPropertyValue(Object::NAME_PROPERTY_KEY, name);
//   ASSERT_EQ(root.propertyValue<std::string>(Object::NAME_PROPERTY_KEY), name);
// }
