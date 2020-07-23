#pragma once
#include <iostream>
#include <memory>
#include <json_cpp/json_util.h>
#include <json_cpp/json_base.h>
#include <json_cpp/json_wrapper.h>

namespace json_cpp {
    struct Json_builder : Json_base{
        void json_add_member(std::string, bool, std::unique_ptr<Json_wrapped>);
        void json_parse(std::istream &) override;
        void json_write(std::ostream &) const override;
    private:
        struct Json_member {
            Json_member (std::string, bool, std::unique_ptr<Json_wrapped> );
            std::string name;
            bool mandatory;
            std::unique_ptr<Json_wrapped> ref;
        };
        std::vector<Json_member> _members;
        Json_member &_member(const std::string &);
        void _check_mandatory_members(const std::vector<std::string> &);
    };
}