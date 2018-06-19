#include "core/scene.h"
#include <random>
#include <glog/logging.h>
#include <assert.h>
#include "core/object.h"

Scene* Scene::m_current = nullptr;

Scene::Scene()
  : m_root(std::make_unique<RootObject>(*this))
{
  m_current = this;
}

Scene::~Scene()
{
  if (m_current == this) {
    m_current = nullptr;
  }
}

Scene::RootObject& Scene::root()
{
  return *m_root;
}

ObjectView Scene::root_view()
{
  return ObjectView(*m_root);
}

Scene* Scene::currentInstance()
{
  return m_current;
}