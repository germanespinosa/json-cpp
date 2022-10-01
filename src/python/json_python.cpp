#include <json_cpp/python/json_python.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

using namespace json_cpp;
using namespace std;

PYBIND11_MODULE(core, m) {

    pybind11::class_<Python_object>(m, "JsonObject")
            .def(pybind11::init<>())
            .def("get_bool_member", +[](Python_object &o, const string &name){
                return o.members[name].bool_value;
            })
            .def("get_int_member", +[](Python_object &o, const string &name){
                return o.members[name].int_value;
            })
            .def("get_float_member", +[](Python_object &o, const string &name){
                return o.members[name].float_value;
            })
            .def("get_string_member", +[](Python_object &o, const string &name){
                return o.members[name].string_value;
            })
            .def("get_object_member", +[](Python_object &o, const string &name){
                return o.members[name].object_value;
            })
            .def("get_array_member", +[](Python_object &o, const string &name){
                return o.members[name].array_value;
            })
            .def("set_bool_member", +[](Python_object &o, const string &name, bool v){
                o.members[name] = v;
            })
            .def("set_int_member", +[](Python_object &o, const string &name, int v){
                o.members[name] = v;
            })
            .def("set_float_member", +[](Python_object &o, const string &name, float v){
                o.members[name] = v;
            })
            .def("set_string_member", +[](Python_object &o, const string &name, const string &v){
                o.members[name] = v;
            })
            .def("set_object_member", +[](Python_object &o, const string &name, Python_object &v){
                o.members[name] = v;
            })
            .def("set_array_member", +[](Python_object &o, const string &name, Python_array &v){
                o.members[name] = v;
            })
            .def("add_bool_member", &json_cpp::Python_object::add_bool_member)
            .def("add_int_member", &json_cpp::Python_object::add_int_member)
            .def("add_float_member", &json_cpp::Python_object::add_float_member)
            .def("add_string_member", &json_cpp::Python_object::add_string_member)
            .def("add_object_member", &json_cpp::Python_object::add_object_member)
            .def("add_array_member", &json_cpp::Python_object::add_array_member)
            .def("get_member_type", +[](Python_object &o, const string &name){
                return o.members[name].get_python_type();
            })
            .def("get_member_mandatory", +[](Python_object &o, const string &name){
                return o.members[name].mandatory;
            })
            .def("load", &json_cpp::Json_base::load)
            .def("save", &json_cpp::Json_base::save)
            .def("__str__", &json_cpp::Json_base::to_json)
            .def("__repr__", &json_cpp::Json_base::to_json)
            .def("to_json", &json_cpp::Json_base::to_json)
            .def("from_json", &json_cpp::Json_base::from_json)
            ;

    pybind11::class_<json_cpp::Python_array>(m,"JsonList")
            .def(pybind11::init<size_t>())
            .def(pybind11::init<size_t, json_cpp::Python_value>())
            .def("__getitem__", +[](const json_cpp::Json_vector<json_cpp::Python_value> &a, const int c){ return a[c]; })
            .def("__setitem__", +[](json_cpp::Json_vector<json_cpp::Python_value> &a, const int c, json_cpp::Python_value &v){ a[c] = v; })
            .def("__len__", &json_cpp::Json_vector<json_cpp::Python_value>::size)
            .def("__contains__", [](const json_cpp::Json_vector<json_cpp::Python_value> &a, json_cpp::Python_value &v) { return a.contains(v); })
            .def("__reversed__", [](const json_cpp::Json_vector<json_cpp::Python_value> &a) { return a.reversed(); })
            .def("__iter__", [](const json_cpp::Json_vector<json_cpp::Python_value> &a) {
                return pybind11::make_iterator(a.begin(), a.end());
                }, pybind11::keep_alive<0, 1>() /* Essential: keep object alive while iterator exists */)
            ;
}
