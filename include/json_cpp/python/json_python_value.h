#pragma once
#include <json_cpp/json_base.h>
#include <json_cpp/json_vector.h>
#include <unordered_map>

namespace json_cpp {

    template <typename T>
    struct Python_smart_ptr {
        void populate(){
            ptr = new T();
        }
        T *ptr{};
        T* operator->() { return ptr; }
        const T* operator->() const { return ptr; }
        T &operator *(){ return *ptr; }
        const T &operator *() const { return *ptr; }
        T &operator = (const T &o) {
            if (!ptr) {
                populate();
            }
            *ptr = o;
            return *ptr;
        }
        bool operator == ( const T &o ) const {
            if (!ptr) {
                return false;
            }
            return *ptr == o;
        }
        bool operator != ( const T &o ) const { return !(*this == o); };
        bool operator == ( const Python_smart_ptr<T> &o ) const {
            if (!ptr) {
                return false;
            }
            return *ptr == *o;
        }
        bool operator != ( const Python_smart_ptr<T> &o) const { return !(*this == o); };
        void clear(){
            if (ptr) {
                delete ptr;
                ptr = nullptr;
            }
        };
        ~Python_smart_ptr() {
            if (ptr) {
                delete ptr;
            }
        };
        T &get() {
            return *ptr;
        }
    };

    enum class Python_type {
        Null,
        Bool,
        Int,
        Float,
        String,
        Object,
        List
    };

    struct Python_value;
    struct Python_object;
    struct Python_list;

    struct Python_value : Json_base {
        static Python_type str_to_python_type(const std::string &);
        static std::string python_type_to_string(Python_type);
        Python_value();
        explicit Python_value(const std::string &);
        Python_value(Python_type);
        Python_value(const Python_value &);
        Python_type type;
        void init(Python_type);
        bool bool_value{};
        int int_value{};
        float float_value{};
        Python_smart_ptr<std::string> string_value;
        Python_smart_ptr<Python_object> object_value;
        Python_smart_ptr<Python_list> list_value;
        Python_value & operator = ( const Python_value & );
        Python_value & operator = ( bool );
        Python_value & operator = ( int );
        Python_value & operator = ( float );
        Python_value & operator = ( const std::string & );
        Python_value & operator = ( const Python_object &);
        Python_value & operator = ( const Python_list &);
        bool operator == ( const Python_value &) const;
        bool operator != ( const Python_value &o) const { return !(*this == o); };
        void json_parse(std::istream &) override;
        void json_write(std::ostream &) const override;
        [[nodiscard]] std::string get_python_type() const;
        void clear();
    };
}