#pragma once
#include <vector>
#include <iostream>

namespace json_cpp {

    struct Json_URI {
        Json_URI();
        explicit Json_URI(const std::string &);
        enum Protocol{
            http,
            https
        };
        Protocol protocol;
        std::string domain;
        unsigned int port;
        std::string query_string;
        std::string str() const;
        operator std::string() const;
        friend std::ostream & operator << (std::ostream & , const Json_URI &);
    };

    struct Json_base {
        virtual void json_parse(std::istream &);
        virtual void json_write(std::ostream &) const;
        bool load(const std::string &);
        bool save(const std::string &) const;
        bool load(const Json_URI &);
        friend std::istream & operator >> (std::istream &, Json_base &);
        friend std::ostream & operator << (std::ostream & , const Json_base &);
        friend std::string & operator >> (std::string &, Json_base &);
        friend std::string & operator << (std::string & , const Json_base &);
        friend char * operator >> (char *, Json_base &);
        friend const char * operator >> (const char *, Json_base &);
        friend const Json_URI & operator >> (const Json_URI &, Json_base &);
    private:
        bool _json_callback_ready;
        static size_t _json_callback(char*, size_t, size_t, void *);
    };
}