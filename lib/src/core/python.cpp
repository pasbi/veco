#include <pybind11/embed.h>
#include <iostream>
#include "python.h"

#include "scene.h"
#include "object.h"
#include "tag.h"

namespace py = pybind11;
using namespace pybind11::literals;

Python::Python(ConstructorTag)
{
}

PYBIND11_EMBEDDED_MODULE(ommpfritt, m) {
    // py::class_<Scene>(m, "Scene")
    //   .def("current", &Scene::currentInstance, py::return_value_policy::reference)
    //   // .def("root", &Scene::root, py::return_value_policy::reference)
    //   .def("dummy", &Scene::dummy, py::return_value_policy::reference)
    //   .def("get", &Scene::getPyTestField)
    //   .def("set", &Scene::setPyTestField)
    //   ;
    py::class_<DummyClass>(m, "Dummy")
      ;

    // py::class_<Object>(m, "Object")
    //     // .def("name", &Object::name)
    //     ;
}

bool Python::run(Scene& scene, const std::string code)
{
  py::scoped_interpreter guard {};


  // try {
  //   auto py_scene = 42; //py::init<Scene>();
  //   auto locals = py::dict("scene"_a = scene);
  // } catch (const pybind11::error_already_set& e) {
  //   LOG(INFO) << "ERROR HANDLING <<";
  //   LOG(WARNING) << e.what();
  //   LOG(INFO) << "ERROR HANDLING >>";
  //   return false;
  // }

  // Scene::current = &scene;
  // py::object pyScene = py::cast(scene);
  auto locals = py::dict();

  Scene::current = &scene;

  try {
    py::exec(R"(print(2)
from ommpfritt import Scene
scene = Scene.current()
print(scene.dummy())
print(scene.dummy().name())
    )", py::globals(), locals);

      LOG(INFO) << "Name: " << scene.getPyTestField();
    return true;
  } catch (const pybind11::error_already_set& e) {
    LOG(INFO) << "ERROR HANDLING <<";
    LOG(WARNING) << e.what();
    LOG(INFO) << "ERROR HANDLING >>";
    return false;
  }
  return false;
}

Python& Python::instance()
{
  static std::unique_ptr<Python> instance(nullptr);
  if (instance == nullptr) {
    instance = std::make_unique<Python>(Python::ConstructorTag{});
  }
  return *instance;
}
