#pragma once
#include <json_cpp/json_base.h>
#include <vector>
#include <iostream>
#include <chrono>
#include <date/date.h>

namespace json_cpp {
    struct Json_date : Json_base, date::sys_time<std::chrono::milliseconds> {
        static Json_date now();
        static void set_format(const std::string &);
        static const std::string &get_format();
        virtual void json_parse(std::istream &) override;
        virtual void json_write(std::ostream &) const override;
        std::string to_string();
    private:
        static std::string time_format;
    };
}