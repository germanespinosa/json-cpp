#include <json_cpp/python/json_python.h>
#include "json_cpp/python/json_python_list.h"


namespace json_cpp {

    Python_value::Python_value(){
        init(Python_type::Bool);
    }

    Python_value::Python_value(const Python_value &m) : Python_value() {
        *this = m;
    }

    Python_value::Python_value(Python_type type) {
        init(type);
    }

    Python_value &Python_value::operator = ( const Python_value &o ) {
        list_value.clear();
        object_value.clear();
        string_value.clear();
        type = o.type;
        switch(type) {
            case Python_type::Null:
                break;
            case Python_type::Bool:
                bool_value = o.bool_value;
                break;
            case Python_type::Int:
                int_value = o.int_value;
                break;
            case Python_type::Float:
                float_value = o.float_value;
                break;
            case Python_type::String:
                string_value = o.string_value;
                break;
            case Python_type::Object:
                object_value = o.object_value;
                break;
            case Python_type::List:
                list_value = o.list_value;
                break;
        }
        return *this;
    }

    bool Python_value::operator==(const Python_value &o) const {
        if (type == o.type) {
            switch (type) {
                case Python_type::Null:
                    return true;
                case Python_type::Bool:
                    return bool_value == o.bool_value;
                case Python_type::Int:
                    return int_value == o.int_value;
                case Python_type::List:
                    if (list_value->size() == o.list_value->size()) {
                        for (unsigned int i=0; i < list_value->size(); i++){
                            if ((*list_value)[i] != (*o.list_value)[i]) return false;
                        }
                        return true;
                    }
                    return false;
                case Python_type::Float:
                    return float_value == o.float_value;
                case Python_type::Object:
                    return object_value == o.object_value;
                case Python_type::String:
                    return string_value == o.string_value;
            }
        }
        return false;
    }

    void Python_value::json_parse(std::istream &i) {
        switch (type) {
            case Python_type::Null:
                break;
            case Python_type::Bool:
                Json_wrap_object(bool_value).json_parse(i);
                break;
            case Python_type::Int:
                Json_wrap_object(int_value).json_parse(i);
                break;
            case Python_type::Float:
                Json_wrap_object(float_value).json_parse(i);
                break;
            case Python_type::List:
                Json_wrap_object(*list_value.ptr).json_parse(i);
                break;
            case Python_type::Object:
                Json_wrap_object(*object_value.ptr).json_parse(i);
                break;
            case Python_type::String:
                Json_wrap_object(*string_value.ptr).json_parse(i);
                break;
        }
    }

    void Python_value::json_write(std::ostream &o) const {
        switch (type) {
            case Python_type::Null:
                break;
            case Python_type::Bool:
                Json_wrap_object(bool_value).json_write(o);
                break;
            case Python_type::Int:
                Json_wrap_object(int_value).json_write(o);
                break;
            case Python_type::Float:
                Json_wrap_object(float_value).json_write(o);
                break;
            case Python_type::List:
                Json_wrap_object(*list_value.ptr).json_write(o);
                break;
            case Python_type::Object:
                Json_wrap_object(*object_value.ptr).json_write(o);
                break;
            case Python_type::String:
                Json_wrap_object(*string_value.ptr).json_write(o);
                break;
        }
    }

    Python_value &Python_value::operator=(bool v) {
        if (type!=Python_type::Bool) {
            clear();
            type=Python_type::Bool;
        }
        bool_value = v;
        return *this;
    }

    Python_value &Python_value::operator=(int v) {
        if (type!=Python_type::Int) {
            clear();
            type=Python_type::Int;
        }
        int_value = v;
        return *this;
    }

    Python_value &Python_value::operator=(float v) {
        if (type!=Python_type::Float) {
            clear();
            type=Python_type::Float;
        }
        float_value = v;
        return *this;
    }

    Python_value &Python_value::operator=(const std::string &v) {
        if (type!=Python_type::String) {
            clear();
            type=Python_type::String;
        }
        string_value = v;
        return *this;
    }

    Python_value &Python_value::operator=(const Python_object &v) {
        if (type!=Python_type::Object) {
            clear();
            type=Python_type::Object;
        }
        object_value = v;
        return *this;
    }

    Python_value &Python_value::operator=(const Python_list &v) {
        if (type!=Python_type::List) {
            clear();
            type=Python_type::List;
        }
        list_value = v;
        return *this;
    }

    void Python_value::clear() {
        switch (type) {
            case Python_type::Null:
                break;
            case Python_type::Bool:
                bool_value = false;
                break;
            case Python_type::Int:
                int_value = 0;
                break;
            case Python_type::List:
                list_value.clear();
                break;
            case Python_type::Float:
                float_value = 0;
                break;
            case Python_type::Object:
                object_value.clear();
                break;
            case Python_type::String:
                string_value.clear();
                break;
        }
    }

    std::string Python_value::get_python_type() const {
        return Python_value::python_type_to_string(type);
    }

    Python_value::Python_value(const std::string &python_type) {
        if (python_type == "bool") {
            init(Python_type::Bool);
        } else if (python_type == "int") {
            init(Python_type::Int);
        } else if (python_type == "float") {
            init(Python_type::Float);
        } else if (python_type == "string") {
            init(Python_type::String);
        } else if (python_type == "object") {
            init(Python_type::Object);
        } else if (python_type == "array") {
            init(Python_type::List);
        }
    }

    void Python_value::init(Python_type python_type) {
        type = python_type;
        switch (type) {
            case Python_type::Null:
                break;
            case Python_type::Bool:
                bool_value = false;
                break;
            case Python_type::Int:
                int_value = 0;
                break;
            case Python_type::List:
                list_value.populate();
                break;
            case Python_type::Float:
                float_value = 0;
                break;
            case Python_type::Object:
                object_value.populate();
                break;
            case Python_type::String:
                string_value.populate();
                break;
        }
    }

    std::string Python_value::python_type_to_string(Python_type python_type) {
        switch (python_type) {
            case Python_type::Null:
                return "none";
            case Python_type::Bool:
                return "bool";
            case Python_type::Int:
                return "int";
            case Python_type::Float:
                return "float";
            case Python_type::String:
                return "str";
            case Python_type::Object:
                return "object";
            case Python_type::List:
                return "list";
        }
        return "";
    }

    Python_type Python_value::str_to_python_type(const std::string &python_type_str) {
        if (python_type_str == "bool") {
            return Python_type::Bool;
        } else if (python_type_str == "int") {
            return Python_type::Int;
        } else if (python_type_str == "float") {
            return Python_type::Float;
        } else if (python_type_str == "string") {
            return Python_type::String;
        } else if (python_type_str == "object") {
            return Python_type::Object;
        } else if (python_type_str == "array") {
            return Python_type::List;
        }
        return Python_type::Bool;
    }

    bool Python_list::operator==(const Python_list &o) const {
        if (size()!=o.size()) return false;
        for (size_t i=0; i<size(); i++) if ((*this)[i] != o[i]) return false;
        return true;
    }

    Python_list &Python_list::operator=(const Python_list &o) {
        clear();
        for (auto &i: o) push_back(i);
        return *this;
    }
}