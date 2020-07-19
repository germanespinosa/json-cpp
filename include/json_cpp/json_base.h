#pragma once
#include <vector>
namespace json_cpp {
    struct Json_base {
        virtual void json_parse(std::istream &) = 0;
        virtual void json_write(std::ostream &) const = 0 ;
        bool load(const std::string &);
        bool save(const std::string &) const;
        friend std::istream & operator >> (std::istream &, Json_base &);
        friend std::ostream & operator << (std::ostream & , const Json_base &);
        friend std::string & operator >> (std::string &, Json_base &);
        friend std::string & operator << (std::string & , const Json_base &);
        friend char * operator >> (char *, Json_base &);
        friend const char * operator >> (const char *, Json_base &);
    };
}