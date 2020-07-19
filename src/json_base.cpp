#include <iostream>
#include <utility>
#include <fstream>
#include <json_cpp/json_base.h>


using namespace std;
namespace json_cpp {

    std::istream &operator>>(istream &i, Json_base &o) {
        o.json_parse(i);
        return i;
    }

    std::ostream &operator<<(ostream &o, const Json_base &j) {
        j.json_write(o);
        return o;
    }

    bool Json_base::load(const string &file_name) {
        std::ifstream file;
        file.open(file_name.c_str());
        if (!file.good()) return false;
        json_parse(file);
        return true;
    }

    bool Json_base::save(const string &file_name) const {
        std::ofstream file;
        file.open(file_name.c_str());
        if (!file.good()) return false;
        json_write(file);
        return true;
    }
}