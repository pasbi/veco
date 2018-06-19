#pragma once

#include <map>
#include <memory>
#include <vector>
#include <stdint.h>
#include "core/objectview.h"

class Object;

class Scene
{

public:
  using RootObject = Object;
  Scene();
  ~Scene();

  RootObject& root();
  ObjectView root_view();
  
  static Scene* currentInstance();
  
private:
  std::unique_ptr<RootObject> m_root;
  static Scene* m_current;
};
