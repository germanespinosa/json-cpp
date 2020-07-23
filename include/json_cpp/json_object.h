#pragma once
#include <json_cpp/json_builder.h>

#define Json_object_members(ADD_MEMBERS) void json_set_builder(json_cpp::Json_builder &jb) override{ADD_MEMBERS} void json_set_builder(json_cpp::Json_builder &jb) const override{ADD_MEMBERS}

#define Add_member(VARIABLE) jb.json_add_member(#VARIABLE,true,std::move(Json_wrap_object(VARIABLE).get_unique_ptr()))
#define Add_optional_member(VARIABLE) jb.json_add_member(#VARIABLE,false,std::move(Json_wrap_object(VARIABLE).get_unique_ptr()))
#define Add_member_with_name(VARIABLE, MANDATORY, NAME) jb.json_add_member(NAME,MANDATORY,std::move(Json_wrap_object(VARIABLE).get_unique_ptr()))

namespace json_cpp {
    struct Json_object : Json_base{
        Json_object();
        virtual void json_set_builder(Json_builder &);
        virtual void json_set_builder(Json_builder &) const;
        void json_parse(std::istream &) override;
        void json_write(std::ostream &) const override;
    };
}