#include <json_cpp/json_web_response.h>
#include <unistd.h>

using namespace std;

namespace json_cpp {

    std::string Json_web_response::get_string() const {
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        return buffer.str();
    }

    std::ostream &operator<<(ostream &o, Json_web_response &r) {
        o << r.get_stream().rdbuf();
        return o;
    }

    Json_web_response &operator>>(Json_web_response &r, Json_base &j) {
        r.get_stream() >> j;
        return r;
    }

    std::istream &Json_web_response::get_stream() {
        return ifs;
    }

    Json_web_response::Json_web_response(const string &file_path, const string &url) :
        _file_path(file_path),
        url(url){
        ifs.open (_file_path.c_str(), std::ifstream::in);
    }

    Json_web_response::~Json_web_response() {
        unlink(_file_path.c_str());

    }

    void Json_web_response::save(const string &file_name) {
        ofstream dest(file_name.c_str());
        dest << ifs.rdbuf();
        dest.close();
    }
}


