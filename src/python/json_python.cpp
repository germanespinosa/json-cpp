#include <json_cpp/python/json_python.h>
#include <json_cpp/python/json_descriptor.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

using namespace json_cpp;
using namespace std;

PYBIND11_MODULE(core, m) {

    pybind11::class_<Json_bool_descriptor>(m, "JsonBoolDescriptor")
            .def(pybind11::init<>())
            .def_readwrite("value", &Json_bool_descriptor::value)
            .def("load", &Json_bool_descriptor::load)
            .def("save", &Json_bool_descriptor::save)
            .def("__str__", &Json_bool_descriptor::to_json)
            .def("__repr__", &Json_bool_descriptor::to_json)
            .def("to_json", &Json_bool_descriptor::to_json)
            .def("from_json", &Json_bool_descriptor::from_json)
    ;

    pybind11::class_<Json_int_descriptor>(m, "JsonIntDescriptor")
            .def(pybind11::init<>())
            .def_readwrite("value", &Json_int_descriptor::value)
            .def("load", &Json_int_descriptor::load)
            .def("save", &Json_int_descriptor::save)
            .def("__str__", &Json_int_descriptor::to_json)
            .def("__repr__", &Json_int_descriptor::to_json)
            .def("to_json", &Json_int_descriptor::to_json)
            .def("from_json", &Json_int_descriptor::from_json)
    ;

    pybind11::class_<Json_float_descriptor>(m, "JsonFloatDescriptor")
            .def(pybind11::init<>())
            .def_readwrite("value", &Json_float_descriptor::value)
            .def("load", &Json_float_descriptor::load)
            .def("save", &Json_float_descriptor::save)
            .def("__str__", &Json_float_descriptor::to_json)
            .def("__repr__", &Json_float_descriptor::to_json)
            .def("to_json", &Json_float_descriptor::to_json)
            .def("from_json", &Json_float_descriptor::from_json)
    ;

    pybind11::class_<Json_string_descriptor>(m, "JsonStringDescriptor")
            .def(pybind11::init<>())
            .def_readwrite("value", &Json_string_descriptor::value)
            .def("load", &Json_string_descriptor::load)
            .def("save", &Json_string_descriptor::save)
            .def("__str__", &Json_string_descriptor::to_json)
            .def("__repr__", &Json_string_descriptor::to_json)
            .def("to_json", &Json_string_descriptor::to_json)
            .def("from_json", &Json_string_descriptor::from_json)
    ;

    pybind11::class_<Json_object_descriptor>(m, "JsonObjectDescriptor")
            .def(pybind11::init<>())
            .def("add_member",+[](Json_object_descriptor &o, const string &n, Json_bool_descriptor &d){
                o.add_member(n, d, true);
            })
            .def("add_member",+[](Json_object_descriptor &o, const string &n, Json_int_descriptor &d){
                o.add_member(n, d, true);
            })
            .def("add_member",+[](Json_object_descriptor &o, const string &n, Json_float_descriptor &d){
                o.add_member(n, d, true);
            })
            .def("add_member",+[](Json_object_descriptor &o, const string &n, Json_string_descriptor &d){
                o.add_member(n, d, true);
            })
            .def("add_member",+[](Json_object_descriptor &o, const string &n, Json_object_descriptor &d){
                o.add_member(n, d, true);
            })
            .def("add_member",+[](Json_object_descriptor &o, const string &n, Json_list_descriptor &d){
                o.add_member(n, d, true);
            })
            .def("load", &Json_object_descriptor::load)
            .def("save", &Json_object_descriptor::save)
            .def("__str__", &Json_object_descriptor::to_json)
            .def("__repr__", &Json_object_descriptor::to_json)
            .def("to_json", &Json_object_descriptor::to_json)
            .def("from_json", &Json_object_descriptor::from_json)
    ;

    pybind11::class_<Json_list_descriptor>(m, "JsonListDescriptor")
            .def(pybind11::init<>())
            .def("set_item_descriptor",+[](Json_list_descriptor &o, Json_bool_descriptor &d){
                o.set_item_descriptor(d);
            })
            .def("set_item_descriptor",+[](Json_list_descriptor &o, Json_int_descriptor &d){
                o.set_item_descriptor(d);
            })
            .def("set_item_descriptor",+[](Json_list_descriptor &o, Json_float_descriptor &d){
                o.set_item_descriptor(d);
            })
            .def("set_item_descriptor",+[](Json_list_descriptor &o, Json_string_descriptor &d){
                o.set_item_descriptor(d);
            })
            .def("set_item_descriptor",+[](Json_list_descriptor &o, Json_object_descriptor &d){
                o.set_item_descriptor(d);
            })
            .def("set_item_descriptor",+[](Json_list_descriptor &o, Json_list_descriptor &d){
                o.set_item_descriptor(d);
            })
            .def("load", &Json_list_descriptor::load)
            .def("save", &Json_list_descriptor::save)
            .def("__str__", &Json_list_descriptor::to_json)
            .def("__repr__", &Json_list_descriptor::to_json)
            .def("to_json", &Json_list_descriptor::to_json)
            .def("from_json", &Json_list_descriptor::from_json)
    ;


    pybind11::class_<Python_member_descriptor>(m, "ObjectMember")
            .def(pybind11::init<>())
            .def_readwrite("name", &Python_member_descriptor::name)
            .def_readwrite("python_type", &Python_member_descriptor::python_type)
            .def_readwrite("mandatory", &Python_member_descriptor::mandatory)
            .def("load", &json_cpp::Json_base::load)
            .def("save", &json_cpp::Json_base::save)
            .def("__str__", &json_cpp::Json_base::to_json)
            .def("__repr__", &json_cpp::Json_base::to_json)
            .def("to_json", &json_cpp::Json_base::to_json)
            .def("from_json", &json_cpp::Json_base::from_json)
    ;

    pybind11::class_<json_cpp::Python_member_list>(m,"JsonObjectMembers")
            .def(pybind11::init<size_t>())
            .def("__getitem__", +[](const json_cpp::Python_member_list &a, const string &v){
                for(auto &i : a) if (i.name==v) return i;
                return Python_member_descriptor();
            })
            .def("__setitem__", +[](json_cpp::Python_member_list &a, const int c, json_cpp::Python_member_descriptor &v){ a[c] = v; })
            .def("__len__", &json_cpp::Json_vector<json_cpp::Python_member_descriptor>::size)
            .def("__contains__", [](const json_cpp::Python_member_list &a, json_cpp::Python_member_descriptor &v) { return a.contains(v); })
            .def("__contains__", [](const json_cpp::Python_member_list &a, const string &v) {
                return any_of(a.begin(), a.end(), [v](auto i) { return i.name==v; });
            })
            .def("__reversed__", [](const json_cpp::Python_member_list &a) { return a.reversed(); })
            .def("__iter__", [](const json_cpp::Python_member_list &a) {
                return pybind11::make_iterator(a.begin(), a.end());
            }, pybind11::keep_alive<0, 1>() /* Essential: keep object alive while iterator exists */)
            .def("load", &json_cpp::Json_base::load)
            .def("save", &json_cpp::Json_base::save)
            .def("__str__", &json_cpp::Json_base::to_json)
            .def("__repr__", &json_cpp::Json_base::to_json)
            .def("to_json", &json_cpp::Json_base::to_json)
            .def("from_json", &json_cpp::Json_base::from_json)
            ;

    pybind11::class_<Python_object>(m, "JsonObject")
            .def(pybind11::init<>())
            .def("get_members_list", &Python_object::get_members_list)
            .def("get_bool_member", +[](Python_object &o, const string &name){
                return o.members[name].value.bool_value;
            })
            .def("get_int_member", +[](Python_object &o, const string &name){
                return o.members[name].value.int_value;
            })
            .def("get_float_member", +[](Python_object &o, const string &name){
                return o.members[name].value.float_value;
            })
            .def("get_string_member", +[](Python_object &o, const string &name){
                return o.members[name].value.string_value;
            })
            .def("get_object_member", +[](Python_object &o, const string &name){
                return (Python_object) o.members[name].value.object_value.get();
            })
            .def("get_array_member", +[](Python_object &o, const string &name){
                return o.members[name].value.list_value;
            })
            .def("set_bool_member", +[](Python_object &o, const string &name, bool v){
                o.members[name].value = v;
            })
            .def("set_int_member", +[](Python_object &o, const string &name, int v){
                o.members[name].value = v;
            })
            .def("set_float_member", +[](Python_object &o, const string &name, float v){
                o.members[name].value = v;
            })
            .def("set_string_member", +[](Python_object &o, const string &name, const string &v){
                o.members[name].value = v;
            })
            .def("set_object_member", +[](Python_object &o, const string &name, Python_object &v){
                o.members[name].value = v;
            })
            .def("set_array_member", +[](Python_object &o, const string &name, Python_list &v){
                o.members[name].value = v;
            })

//    members[name] = Python_value(Python_type::Bool, mandatory);
//    members[name] = Python_value(Python_type::Int, mandatory);
//    members[name] = Python_value(Python_type::Float, mandatory);
//    members[name] = Python_value(Python_type::String, mandatory);
//    members[name] = Python_value(Python_type::Object, mandatory);
//    members[name] = Python_value(Python_type::List, mandatory);


            .def("add_bool_member", +[](Python_object &o, const string &name, bool mandatory){
                if (o.members.contains(name)) return false;
                o.members[name] = Python_member(Python_type::Bool, mandatory);
                return true;
            })
            .def("add_int_member", +[](Python_object &o, const string &name, bool mandatory){
                if (o.members.contains(name)) return false;
                o.members[name] = Python_member(Python_type::Int, mandatory);
                return true;
            })
            .def("add_float_member", +[](Python_object &o, const string &name, bool mandatory){
                if (o.members.contains(name)) return false;
                o.members[name] = Python_member(Python_type::Float, mandatory);
                return true;
            })
            .def("add_string_member", +[](Python_object &o, const string &name, bool mandatory){
                if (o.members.contains(name)) return false;
                o.members[name] = Python_member(Python_type::String, mandatory);
                return true;
            })
            .def("add_object_member", +[](Python_object &o, const string &name, bool mandatory){
                if (o.members.contains(name)) return false;
                o.members[name] = Python_member(Python_type::Object, mandatory);
                return true;
            })
            .def("add_list_member", +[](Python_object &o, const string &name, bool mandatory){
                if (o.members.contains(name)) return false;
                o.members[name] = Python_member(Python_type::List, mandatory);
                return true;
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

    pybind11::class_<Python_value>(m, "JsonValue")
            .def(pybind11::init<const string &>())
    ;

    pybind11::class_<json_cpp::Python_list>(m,"JsonList")
            .def(pybind11::init<const string &>())
            .def(pybind11::init<size_t>())
            .def("__getitem__", +[](const json_cpp::Json_vector<json_cpp::Python_value> &a, const int c){ return a[c]; })
            .def("__setitem__", +[](json_cpp::Json_vector<json_cpp::Python_value> &a, const int c, json_cpp::Python_value &v){ a[c] = v; })
            .def("__len__", &json_cpp::Json_vector<json_cpp::Python_value>::size)
            .def("__contains__", [](const json_cpp::Json_vector<json_cpp::Python_value> &a, json_cpp::Python_value &v) { return a.contains(v); })
            .def("__reversed__", [](const json_cpp::Json_vector<json_cpp::Python_value> &a) { return a.reversed(); })
            .def("__iter__", [](const json_cpp::Json_vector<json_cpp::Python_value> &a) {
                return pybind11::make_iterator(a.begin(), a.end());
                }, pybind11::keep_alive<0, 1>() /* Essential: keep object alive while iterator exists */)
            .def("load", &json_cpp::Json_base::load)
            .def("save", &json_cpp::Json_base::save)
            .def("__str__", &json_cpp::Json_base::to_json)
            .def("__repr__", &json_cpp::Json_base::to_json)
            .def("to_json", &json_cpp::Json_base::to_json)
            .def("from_json", &json_cpp::Json_base::from_json)
            ;
}
