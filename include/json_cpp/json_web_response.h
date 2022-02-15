#pragma once
#include <vector>
#include <sstream>
#include <json_cpp/json_base.h>
#include <fstream>
#include <iostream>

namespace json_cpp {
    struct Json_web_response{
        std::string get_string() const;
        friend std::ostream & operator << (std::ostream & , Json_web_response &);
        friend Json_web_response & operator >> (Json_web_response &, Json_base &);
        std::istream &get_stream();
        void save (const std::string &);
        template <class T>
        T get() {
            T o;
            get_stream() >> o;
            return o;
        }
        ~Json_web_response();
    private:
        explicit Json_web_response(const std::string &);
        const std::string _file_path;
        std::ifstream ifs;
        friend struct Json_web_request;
    };
}