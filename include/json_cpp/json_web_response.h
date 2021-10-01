#pragma once
#include <vector>
#include <sstream>
#include <json_cpp/json_base.h>

namespace json_cpp {
    struct Json_web_response{
        explicit Json_web_response(size_t s);
        void push_data(char *buffer, size_t l);
        const std::string &get_string() const;
        std::istream &get_stream();
        size_t size () const;
        friend std::ostream & operator << (std::ostream & , Json_web_response &);
        friend Json_web_response & operator >> (Json_web_response &, Json_base &);
    private:
        std::string _content;
        size_t _byte_count;
        std::stringstream _content_stream;
    };
}