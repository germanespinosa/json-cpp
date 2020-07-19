#pragma once
#include <vector>
namespace json_cpp {
    struct Json_base {
        virtual void json_parse(std::istream &) = 0;
        virtual void json_write(std::ostream &) const = 0 ;
        bool load(const std::string &);
        bool save(const std::string &) const;
        friend std::istream & operator >> (std::istream &, Json_base &);
        friend std::ostream& operator << (std::ostream& , const Json_base &);
    };
}