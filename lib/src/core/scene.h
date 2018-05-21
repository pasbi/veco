#pragma once

#include <map>
#include <stdint.h>

class Object;
class Root;

class Scene
{
private:
  Scene();
public:
  ~Scene();
  typedef uint64_t ObjectId;
  ObjectId add(Object* object);
  Object* object(const ObjectId& id) const;
  ObjectId id(const Object* object) const;

  /**
   * @brief ownership is returned to the caller.
   */
  void remove(const Object* object);

  Object* root() const;

  
  static Scene* instance();

private:
  Object* m_root;

  // don't expose Object* to the outside.
  typedef std::map<ObjectId, Object*, std::less<>> ObjectMap;
  typedef std::map<Object*, ObjectId, std::less<>> IdMap;
  ObjectMap m_objects;
  IdMap m_ids;

};