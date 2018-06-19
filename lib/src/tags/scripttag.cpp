#include "core/python.h"
#include "tags/scripttag.h"
#include <glog/logging.h>

const std::string ScriptTag::CODE_PROPERTY_KEY = "code";

ScriptTag::ScriptTag(Object& owner)
  : Tag(owner)
{
  add_property( CODE_PROPERTY_KEY,
               std::make_unique<StringProperty>("") );
}

ScriptTag::~ScriptTag()
{  
}


bool ScriptTag::run()
{
  const std::string code = property(CODE_PROPERTY_KEY).cast<std::string>().value();
  return Python::instance().run(scene(), code);
}

