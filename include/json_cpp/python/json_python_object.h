#pragma once
#include <json_cpp/python/json_python_value.h>
#include <json_cpp/json_object.h>

namespace json_cpp {
    struct Python_object : Json_object {
        void json_set_builder(Json_builder &) override;
        void json_set_builder(Json_builder &) const override;
        bool add_bool_member(const std::string &, bool mandatory = false);
        bool add_int_member(const std::string &, bool mandatory = false);
        bool add_float_member(const std::string &, bool mandatory = false);
        bool add_string_member(const std::string &, bool mandatory = false);
        bool add_object_member(const std::string &, bool mandatory = false);
        bool add_array_member(const std::string &, bool mandatory = false);
        std::unordered_map<std::string, Python_value> members;
        Python_object & operator = ( const Python_object &);
        bool operator == ( const Python_object &) const;
        bool operator != ( const Python_object &o) const { return !(*this == o); };
    };
}