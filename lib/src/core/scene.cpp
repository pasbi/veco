#include "core/scene.h"
#include <random>
#include <glog/logging.h>
#include <assert.h>
#include "core/object.h"

Scene* Scene::current = nullptr;

Scene::Scene()
  : m_root(std::make_unique<RootObject>(*this))
  , m_dummy(std::make_unique<DummyClass>())
{
}

Scene::~Scene()
{
  LOG(INFO) << "DELETE scene " << (void*) this;
}

void Scene::remove(const Object& object)
{
  for (Object& child : object.children()) {
    remove(child);
  }

  m_objects.erase(std::find_if(m_objects.begin(), m_objects.end(), [&](const std::unique_ptr<Object>& i) {
    return i.get() == &object;
  }));
}

Scene::RootObject& Scene::root()
{
  return *m_root;
}

DummyClass& Scene::dummy()
{
  return *m_dummy;
}

Scene& Scene::currentInstance()
{
  assert(current != nullptr);
  return *current;
}