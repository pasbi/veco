#pragma once

#include <string>

class Scene;

class Python
{
private:
  Python();
public:
  bool run(Scene* scene, const std::string code);
  static Python* instance();
};