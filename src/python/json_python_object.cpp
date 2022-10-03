#include <json_cpp/python/json_python.h>
#include "json_cpp/python/json_python_object.h"


using namespace std;

namespace json_cpp {

    bool Python_object::operator == ( const Python_object &o ) const {
        if (members.size() != o.members.size() ) return false;
        for(auto &m:members) {
            if (!o.members.contains(m.first) || o.members.find(m.first)->second != m.second) return false;
        }
        return true;
    }

    Python_object &Python_object::operator = (const Python_object &o) {
        members.clear();
        for (auto &m:o.members) members.emplace(m);
        return *this;
    }

    void Python_object::json_set_builder(Json_builder &jb) {
        for (auto &m:members) {
            auto &name = m.first;
            auto &v = m.second;
            switch (v.value.type) {
                case Python_type::Null:
                    break;
                case Python_type::Bool:
                    Add_member_with_name(v.value.bool_value, v.mandatory, name);
                    break;
                case Python_type::Int:
                    Add_member_with_name(v.value.int_value, v.mandatory, name);
                    break;
                case Python_type::Float:
                    Add_member_with_name(v.value.float_value, v.mandatory, name);
                    break;
                case Python_type::String:
                    Add_member_with_name(*(v.value.string_value.ptr), v.mandatory, name);
                    break;
                case Python_type::Object:
                    Add_member_with_name(*(v.value.object_value.ptr), v.mandatory, name);
                    break;
                case Python_type::List:
                    Add_member_with_name(*(v.value.list_value.ptr), v.mandatory, name);
                    break;
            }
        }
    }

    void Python_object::json_set_builder(Json_builder &jb) const {
        for (auto &m:members) {
            auto &name = m.first;
            auto &v = m.second;
            switch (v.value.type) {
                case Python_type::Null:
                    break;
                case Python_type::Bool:
                    Add_member_with_name(v.value.bool_value, v.mandatory, name);
                    break;
                case Python_type::Int:
                    Add_member_with_name(v.value.int_value, v.mandatory, name);
                    break;
                case Python_type::Float:
                    Add_member_with_name(v.value.float_value, v.mandatory, name);
                    break;
                case Python_type::String:
                    Add_member_with_name(*(v.value.string_value.ptr), v.mandatory, name);
                    break;
                case Python_type::Object:
                    Add_member_with_name(*(v.value.object_value.ptr), v.mandatory, name);
                    break;
                case Python_type::List:
                    Add_member_with_name(*(v.value.list_value.ptr), v.mandatory, name);
                    break;
            }
        }
    }

    Python_member_list Python_object::get_members_list() {
        Python_member_list member_list;
        for (auto &m:members) {
            auto &md = member_list.emplace_back();
            md.name = m.first;
            md.mandatory = m.second.mandatory;
            md.python_type = Python_value::python_type_to_string(m.second.value.type);
        }
        return member_list;
    }

    Python_member &Python_member::operator = (const Python_member &o) = default;

    bool Python_member::operator == (const Python_member &o) const {
        return o.mandatory == mandatory && o.value == value;
    }

    Python_member::Python_member(Python_type python_type, bool mandatory) : value(python_type), mandatory(mandatory) {

    }

    bool Python_member_descriptor::operator==(const Python_member_descriptor &o) const {
        return o.mandatory == mandatory && o.name == name && o.python_type == o.python_type;
    }
}
