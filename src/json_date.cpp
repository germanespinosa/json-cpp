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
        ss >> date::parse("%Y-%m-%d %T", date_time);
    }

    void Json_date::json_write(std::ostream &o) const {
        o << '"' << date::format(time_format, date_time) << '"';
    }

    Json_date Json_date::now() {
        Json_date jd;
        jd.date_time = round<milliseconds>(system_clock::now());
        return jd;
    }

    void Json_date::set_format(const string &new_format) {
        Json_date::time_format = new_format;
    }

    const std::string &Json_date::get_format() {
        return Json_date::time_format;
    }
}