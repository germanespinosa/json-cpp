#pragma once
#include <vector>
#include <sstream>

namespace json_cpp {
    struct Json_web_response{
        explicit Json_web_response(size_t s);
        void push_data(char *buffer, size_t l);
        const std::string &get_string() const;
        std::istream &get_stream();
        size_t size () const;
    private:
        std::string _content;
        size_t _byte_count;
        std::stringstream _content_stream;
    };
}