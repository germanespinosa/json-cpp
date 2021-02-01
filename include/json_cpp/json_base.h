#pragma once
#include <vector>
#include <iostream>

namespace json_cpp {
    struct Json_base {
        virtual void json_parse(std::istream &);
        virtual void json_write(std::ostream &) const;
        bool load(const std::string &);
        bool save(const std::string &) const;
        friend std::istream & operator >> (std::istream &, Json_base &);
        friend std::ostream & operator << (std::ostream & , const Json_base &);
        friend std::string & operator >> (std::string &, Json_base &);
        friend const std::string & operator >> (const std::string &, Json_base &);
        friend std::string & operator << (std::string & , const Json_base &);
        friend char * operator >> (char *, Json_base &);
        friend const char * operator >> (const char *, Json_base &);
    };
    template <class T>
    T Json_create(std::istream &i) {
        T o;
        i >> o;
        return o;
    }
    template <class T>
    T Json_create(std::string &s) {
        T o;
        s >> o;
        return o;
    }
    template <class T>
    T Json_from_file(const std::string &file_path) {
        T o;
        o.load(file_path);
        return o;
    }
}