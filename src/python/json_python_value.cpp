#include <json_cpp/python/json_python_object.h>
#include <json_cpp/python/json_python_value.h>

namespace json_cpp {

    Python_value::Python_value() :  type(Python_type::Bool), mandatory(false){
    }

    Python_value::Python_value(const Python_value &m) : Python_value() {
        *this = m;
    }

    Python_value::Python_value(Python_type type, bool mandatory): type(type), mandatory(mandatory) {
        switch (type) {
            case Python_type::Bool:
                bool_value = false;
                break;
            case Python_type::Int:
                int_value = 0;
                break;
            case Python_type::Array:
                array_value.populate();
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

    Python_value &Python_value::operator = ( const Python_value &o ) {
        array_value.clear();
        object_value.clear();
        string_value.clear();
        type = o.type;
        switch(type) {
            case Python_type::Bool:
                bool_value = o.bool_value;
                break;
            case Python_type::Int:
                int_value = o.int_value;
                break;
            case Python_type::Array:
                array_value = o.array_value;
                break;
            case Python_type::Float:
                float_value = o.float_value;
                break;
            case Python_type::Object:
                object_value = o.object_value;
                break;
            case Python_type::String:
                string_value = o.string_value;
                break;
        }
        return *this;
    }

    bool Python_value::operator==(const Python_value &o) const {
        if (type == o.type) {
            switch (type) {
                case Python_type::Bool:
                    return bool_value == o.bool_value;
                case Python_type::Int:
                    return int_value == o.int_value;
                case Python_type::Array:
                    if (array_value->size() == o.array_value->size()) {
                        for (unsigned int i=0;i<array_value->size();i++){
                            if ((*array_value)[i] != (*o.array_value)[i]) return false;
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
            case Python_type::Bool:
                Json_wrap_object(bool_value).json_parse(i);
                break;
            case Python_type::Int:
                Json_wrap_object(int_value).json_parse(i);
                break;
            case Python_type::Float:
                Json_wrap_object(float_value).json_parse(i);
                break;
            case Python_type::Array:
                Json_wrap_object(*array_value.ptr).json_parse(i);
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
            case Python_type::Bool:
                Json_wrap_object(bool_value).json_write(o);
                break;
            case Python_type::Int:
                Json_wrap_object(int_value).json_write(o);
                break;
            case Python_type::Float:
                Json_wrap_object(float_value).json_write(o);
                break;
            case Python_type::Array:
                Json_wrap_object(*array_value.ptr).json_write(o);
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

    Python_value &Python_value::operator=(const Python_array &v) {
        if (type!=Python_type::Array) {
            clear();
            type=Python_type::Array;
        }
        array_value = v;
        return *this;
    }

    void Python_value::clear() {
        switch (type) {
            case Python_type::Bool:
                bool_value = false;
                break;
            case Python_type::Int:
                int_value = 0;
                break;
            case Python_type::Array:
                array_value.clear();
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

    const std::string Python_value::get_python_type() const {
        switch (type) {
            case Python_type::Bool:
                return "bool";
            case Python_type::Int:
                return "int";
            case Python_type::Array:
                return "array";
            case Python_type::Float:
                return "float";
            case Python_type::Object:
                return "object";
            case Python_type::String:
                return "string";
        }
        return "";
    }
}