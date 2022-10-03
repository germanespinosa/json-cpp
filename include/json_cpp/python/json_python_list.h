#pragma once
#include <json_cpp/python/json_python_value.h>
#include <json_cpp/python/json_python_object.h>

namespace json_cpp{
    struct Python_list : Json_vector<Python_value>{
        Python_list(const std::string &python_type_str): Python_list(Python_value::str_to_python_type(python_type_str)) {};
        Python_list(const Python_type &python_type): list_type(python_type) {};
        Python_list(): Json_vector<Python_value>(){};
        Python_list(const Python_list &o): Json_vector<Python_value>(o){};
        explicit Python_list(size_t s): Json_vector<Python_value>(s){};
        inline Python_value &new_item() override {
            auto &new_item = this->template emplace_back(list_type);
            if (list_type==Python_type::Object){
                new_item.object_value = item_descriptor;
            }
            return new_item;
        }
        bool operator == ( const Python_list &) const;
        Python_list & operator = ( const Python_list & );
        Python_object item_descriptor;
        Python_list *l;
        Python_type list_type;
        virtual ~Python_list()=default;
    };
}