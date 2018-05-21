#include "core/scene.h"
#include <random>
#include <glog/logging.h>
#include <assert.h>
#include "core/object.h"

namespace {
  Scene::ObjectId generateId()
  {
#ifdef DETERMINISTIC_OBJECT_IDS
    static ObjectId nextId = 0;
    return nextId++;
#else  // random
    static std::random_device rd;
    static std::mt19937_64 rng(rd());
    static std::uniform_int_distribution<Scene::ObjectId> dis;
    return dis(rng);
#endif
  }
}

Scene::Scene()
  : m_root(Object::createRootInstance(this))
{
  add(m_root);
}

Scene::~Scene()
{
  LOG(INFO) << "DELETE scene " << (void*) this;
  remove(m_root);
  delete m_root;
}

Scene::ObjectId Scene::add(Object* object)
{
  ObjectId id = generateId();
  const bool oNewlyInserted = m_objects.insert(std::make_pair(id, object)).second;
  const bool iNewlyInserted = m_ids.insert(std::make_pair(object, id)).second;
  assert(oNewlyInserted && iNewlyInserted);
  return id;
}

Scene* Scene::instance()
{
  static Scene* instance = nullptr;
  if (instance == nullptr) {
    instance = new Scene();
  }
  return instance;
}

Object* Scene::object(const ObjectId& id) const
{
  const ObjectMap::const_iterator it = m_objects.find(id);
  if (it == m_objects.end()) {
    return nullptr;
  } else {
    return it->second;
  }
}

Scene::ObjectId Scene::id(const Object* object) const
{
  const IdMap::const_iterator it = m_ids.find(object);
  assert(it != m_ids.end());
  return it->second;
}

void Scene::remove(const Object* object)
{
  for (Object* child : object->children()) {
    remove(child);
  }

  IdMap::iterator iit = m_ids.find(object);
  assert(iit != m_ids.end());
  const ObjectId id = iit->second;
  ObjectMap::iterator oit = m_objects.find(id);
  assert(oit != m_objects.end());

  m_objects.erase(oit);
  m_ids.erase(iit);
}

Object* Scene::root() const
{
  return m_root;
}