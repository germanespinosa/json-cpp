#include <json_cpp/json_date.h>
#include <json_cpp/json_util.h>
#include <string>

using namespace std::chrono;
using namespace std;

namespace json_cpp{

    string Json_date::time_format("%Y-%m-%d %T");

    void Json_date::json_parse(std::istream &i) {
        string d = Json_util::read_string(i);
        std::istringstream ss{d};
        ss >> date::parse("%Y-%m-%d %T", *this);
    }

    void Json_date::json_write(std::ostream &o) const {
        o << '"' << date::format(time_format, *this) << '"';
    }

    Json_date Json_date::now() {
        Json_date jd;
        date::sys_time<std::chrono::milliseconds> &d = jd;
        d = round<milliseconds>(system_clock::now());
        return jd;
    }

    void Json_date::set_format(const string &new_format) {
        Json_date::time_format = new_format;
    }

    const std::string &Json_date::get_format() {
        return Json_date::time_format;
    }

    std::string Json_date::to_string() {
        return date::format(time_format, *this);
    }

    std::string Json_date::to_string(const string &format) {
        return date::format(format, *this);
    }
}