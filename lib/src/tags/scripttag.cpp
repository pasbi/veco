#include "core/python.h"
#include "tags/scripttag.h"
#include <glog/logging.h>

const std::string ScriptTag::CODE_PROPERTY_KEY = "code";

ScriptTag::ScriptTag(Object& owner)
  : Tag(owner)
{
  addProperty( CODE_PROPERTY_KEY,
               std::make_unique<StringProperty>("") );
}

ScriptTag::~ScriptTag()
{  
}


bool ScriptTag::run()
{
  const std::string code = propertyValue<std::string>(CODE_PROPERTY_KEY);
  return Python::instance().run(scene(), code);
}

