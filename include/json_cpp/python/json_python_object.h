#pragma once
#include <json_cpp/python/json_python_value.h>
#include <json_cpp/json_object.h>

namespace json_cpp {

    struct Python_member{
        Python_member () = default;
        Python_member (Python_type , bool );
        Python_value value;
        bool mandatory;
        Python_member& operator = (const Python_member&);
        bool operator == (const Python_member &) const;
        bool operator != (const Python_member &o) const { return !(*this==o); };
    };

    struct Python_member_descriptor : Json_object {
        Json_object_members(
                Add_member(name);
                Add_member(python_type);
                Add_member(mandatory);
                )
        std::string name;
        std::string python_type;
        bool mandatory;
        bool operator == (const Python_member_descriptor &) const;
        bool operator != (const Python_member_descriptor &o) const { return !(*this==o); };
    };

    using Python_member_list = Json_vector<Python_member_descriptor>;

    struct Python_object : Json_object {
        Python_object() = default;
        Python_object(const Python_object &) = default;
        void json_set_builder(Json_builder &) override;
        void json_set_builder(Json_builder &) const override;
        Python_member_list get_members_list();
        std::unordered_map<std::string, Python_member> members;
        Python_object & operator = ( const Python_object &);
        bool operator == ( const Python_object &) const;
        bool operator != ( const Python_object &o) const { return !(*this == o); };
        virtual ~Python_object()=default;
    };
}