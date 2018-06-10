#pragma once

#include "core/tag.h"

class ScriptTag : public Tag
{
public:
  explicit ScriptTag(Object& owner);
  ~ScriptTag();
  bool run() override;

  static const std::string CODE_PROPERTY_KEY;
};