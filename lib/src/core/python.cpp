#include <pybind11/embed.h>
#include <iostream>
#include "python.h"

#include "scene.h"
#include "object.h"
#include "tag.h"

// namespace py = pybind11;

// PYBIND11_EMBEDDED_MODULE(ommpfritt, m) {
//     py::class_<Scene>(m, "Scene")
//         .def("root", &Scene::root)
//         .def("instance", &Scene::instance);
//     py::class_<Object>(m, "Object")
//         .def(py::init<Object*>())
//         .def("name", &Object::name)
//         .def("setName", &Object::setName);
//     py::class_<Tag>(m, "Tag")
//         .def(py::init<Object*>());
// }

namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(ommpfritt, m) {
    py::class_<Scene, std::shared_ptr<Scene>>(m, "Scene")
        .def("root", &Scene::root)
        .def("instance", &Scene::instance);
    py::class_<Object, std::shared_ptr<Object>>(m, "Object")
        .def(py::init<Object*>())
        .def("name", &Object::name)
        .def("setName", &Object::setName);
    py::class_<Tag, std::shared_ptr<Tag>>(m, "Tag")
        .def(py::init<Object*>());
}


Python::Python()
{
}

bool Python::run(Scene* scene, const std::string code)
{
  // py::scoped_interpreter guard {};
  py::initialize_interpreter();

  try {
    py::exec(R"(
import ommpfritt as o
scene = o.Scene.instance()
print(scene)
root = scene.root().name();
print("end script.", root)
    )");

      LOG(INFO) << "Name: " << scene->root()->name();
    return true;
  } catch (const std::exception& e) {
    LOG(WARNING) << e.what();
    return false;
  }
}


Python* Python::instance()
{
  static Python* instance = nullptr;
  if (instance == nullptr) {
    instance = new Python();
  }
  return instance;
}