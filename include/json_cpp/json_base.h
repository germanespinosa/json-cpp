#pragma once
#include <vector>
#include <iostream>

namespace json_cpp {

    struct Json_URI {
        explicit Json_URI(const std::string &);
        enum Protocol{
            http,
            https
        };
        Protocol protocol;
        std::string domain;
        unsigned int port;
        std::string query_string;
        operator std::string () const;
    };

    struct Json_base {
        virtual void json_parse(std::istream &);
        virtual void json_write(std::ostream &) const;
        bool load(const std::string &);
        bool save(const std::string &) const;
        bool load(Json_URI &);
        friend std::istream & operator >> (std::istream &, Json_base &);
        friend std::ostream & operator << (std::ostream & , const Json_base &);
        friend std::string & operator >> (std::string &, Json_base &);
        friend std::string & operator << (std::string & , const Json_base &);
        friend char * operator >> (char *, Json_base &);
        friend const char * operator >> (const char *, Json_base &);
    private:
        size_t json_write_callback(char* buf, size_t size, size_t nmemb, void* up);
    };
}