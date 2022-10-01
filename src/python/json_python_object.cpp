#include <json_cpp/python/json_python_object.h>

namespace json_cpp {

    bool Python_object::operator == ( const Python_object &o ) const {
        if (members.size() != o.members.size() ) return false;
        for (auto &m: members){
            if (!o.members.contains(m.first)) return false;
            if ( o.members.find(m.first)->second != m.second) return false;
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
            switch (v.type) {
                case Python_type::Bool:
                    Add_member_with_name(v.bool_value, v.mandatory, name);
                    break;
                case Python_type::Int:
                    Add_member_with_name(v.int_value, v.mandatory, name);
                    break;
                case Python_type::Float:
                    Add_member_with_name(v.float_value, v.mandatory, name);
                    break;
                case Python_type::String:
                    Add_member_with_name(*(v.string_value.ptr), v.mandatory, name);
                    break;
                case Python_type::Object:
                    Add_member_with_name(*(v.object_value.ptr), v.mandatory, name);
                    break;
                case Python_type::Array:
                    Add_member_with_name(*(v.array_value.ptr), v.mandatory, name);
                    break;
            }
        }
    }

    void Python_object::json_set_builder(Json_builder &jb) const {
        for (auto &m:members) {
            auto &name = m.first;
            auto &v = m.second;
            switch (v.type) {
                case Python_type::Bool:
                    Add_member_with_name(v.bool_value, v.mandatory, name);
                    break;
                case Python_type::Int:
                    Add_member_with_name(v.int_value, v.mandatory, name);
                    break;
                case Python_type::Float:
                    Add_member_with_name(v.float_value, v.mandatory, name);
                    break;
                case Python_type::String:
                    Add_member_with_name(*(v.string_value.ptr), v.mandatory, name);
                    break;
                case Python_type::Object:
                    Add_member_with_name(*(v.object_value.ptr), v.mandatory, name);
                    break;
                case Python_type::Array:
                    Add_member_with_name(*(v.array_value.ptr), v.mandatory, name);
                    break;
            }
        }
    }

    bool Python_object::add_bool_member(const std::string &name, bool mandatory) {
        if (members.contains(name)) return false;
        members[name] = Python_value(Python_type::Bool, mandatory);
        return true;
    }

    bool Python_object::add_int_member(const std::string &name, bool mandatory) {
        if (members.contains(name)) return false;
        members[name] = Python_value(Python_type::Int, mandatory);
        return true;
    }

    bool Python_object::add_float_member(const std::string &name, bool mandatory) {
        if (members.contains(name)) return false;
        members[name] = Python_value(Python_type::Float, mandatory);
        return true;
    }

    bool Python_object::add_string_member(const std::string &name, bool mandatory) {
        if (members.contains(name)) return false;
        members[name] = Python_value(Python_type::String, mandatory);
        return true;
    }

    bool Python_object::add_object_member(const std::string &name, bool mandatory) {
        if (members.contains(name)) return false;
        members[name] = Python_value(Python_type::Object, mandatory);
        return true;
    }

    bool Python_object::add_array_member(const std::string &name, bool mandatory) {
        if (members.contains(name)) return false;
        members[name] = Python_value(Python_type::Array, mandatory);
        return true;
    }
}
