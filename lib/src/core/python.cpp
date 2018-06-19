#include <pybind11/embed.h>
#include <iostream>
#include "python.h"

#include "scene.h"
#include "objectview.h"
#include "tagview.h"

namespace py = pybind11;
using namespace pybind11::literals;

Python::Python(ConstructorTag)
{
}

PYBIND11_EMBEDDED_MODULE(ommpfritt, m) {
    py::class_<Scene>(m, "Scene")
      .def("current", &Scene::currentInstance, py::return_value_policy::reference)
      .def("root", &Scene::root_view)
      ;

    py::class_<ObjectView>(m, "Object")
      .def("property", &ObjectView::get_property)
      .def("set_property", &ObjectView::set_property)
      .def("children", &ObjectView::children)
      .def("parent", &ObjectView::parent)
      .def("tags", &ObjectView::tags)
      .def("remove", &ObjectView::remove)
      ;

    py::class_<TagView>(m, "Tag")
      .def("property", &TagView::get_property)
      .def("set_property", &TagView::set_property)
      .def("owner", &TagView::owner)
      .def("remove", &TagView::remove)
      ;
}

bool Python::run(Scene& scene, const std::string code)
{
  py::scoped_interpreter guard {};

  try {
    py::exec(R"(
from ommpfritt import Scene
scene = Scene.current()
root = scene.root()
print("name: ", root.property("name") + "abc")
root.set_property("ans", 22)
print("ans: ", root.property("ans") + 42)
print("children: ", root.children())
print(root.parent())
print(root.set_property("name", "ROOOT"))
c = root.children()[0]
print(c.parent().property("name"))
print(c.parent().parent())
c.remove()
print(c.parent().property("name"))
    )", py::globals(), locals);

      // LOG(INFO) << "Name: " << scene.getPyTestField();
    return true;
  } catch (const pybind11::error_already_set& e) {
    LOG(WARNING) << e.what();
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
