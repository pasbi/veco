#pragma once


#include "core/view.h"
#include <string>
#include "core/tag.h"

class TagView : public View<Tag>
{
public:
  TagView(Tag& tag);
  py::object owner();

  void remove();
};
