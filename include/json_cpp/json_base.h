#pragma once
#include <vector>
#include <iostream>
#include <json_cpp/json_web_request.h>

namespace json_cpp {
    struct Json_base {
        virtual void json_parse(std::istream &);
        virtual void json_write(std::ostream &) const;
        bool load(const std::string &);
        bool save(const std::string &) const;
        friend std::istream & operator >> (std::istream &, Json_base &);
        friend std::ostream & operator << (std::ostream & , const Json_base &);
        friend std::string & operator >> (std::string &, Json_base &);
        friend std::string & operator << (std::string & , const Json_base &);
        friend char * operator >> (char *, Json_base &);
        friend const char * operator >> (const char *, Json_base &);
    private:
        bool _json_callback_ready;
        static size_t _json_callback(char*, size_t, size_t, void *);
    };
}