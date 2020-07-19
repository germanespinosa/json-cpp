#pragma once
#include <json_cpp/json_builder.h>

#define Json_set_builder(X) void json_set_builder(Json_builder &jb) override{X} void json_set_builder(Json_builder &jb) const override{X}

#define Json_add_member(VARIABLE, MANDATORY) jb.json_add_member(#VARIABLE,MANDATORY,Json_wrap(VARIABLE))
#define Json_add_member_with_name(VARIABLE, MANDATORY, NAME) jb.json_add_member(NAME,MANDATORY,Json_wrap(VARIABLE))

namespace json_cpp {
    struct Json_object : Json_base{
        Json_object();
        virtual void json_set_builder(Json_builder &);
        virtual void json_set_builder(Json_builder &) const;
        void json_parse(std::istream &) override;
        void json_write(std::ostream &) const override;
    };
}