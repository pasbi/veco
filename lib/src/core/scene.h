#pragma once

#include <map>
#include <memory>
#include <vector>
#include <stdint.h>

class Object;
class Root;

#include "core/hasproperties.h"
class Scene;
class DummyClass
{
public:
  std::vector<std::unique_ptr<int>> m_properties;
};

class Scene
{

public:
  using RootObject = Object;
  Scene();
  ~Scene();
  typedef uint64_t ObjectId;

  template<typename ObjectT> ObjectT& new_object()
  {
    m_objects.push_back(std::make_unique<ObjectT>(*this));
    return static_cast<ObjectT&>(*m_objects.back());
  }

  void remove(const Object& object);
  RootObject& root();
  DummyClass& dummy();

  std::string getPyTestField() const
  {
    return pyTestField;
  }

  void setPyTestField(const std::string& m)
  {
    pyTestField = m; 
  }

  static Scene& currentInstance();
  static Scene* current;
  
private:
  std::unique_ptr<RootObject> m_root;
  std::unique_ptr<DummyClass> m_dummy;
  std::vector<std::unique_ptr<Object>> m_objects;
  std::string pyTestField;
};
