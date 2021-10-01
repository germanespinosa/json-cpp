#include <json_cpp/json_web_response.h>

using namespace std;

namespace json_cpp {

    Json_web_response::Json_web_response(size_t s) {
        _content.reserve(s);
        _byte_count = 0;
    }

    void Json_web_response::push_data(char *buffer, size_t l)  {
        for (size_t i=0;i<l;i++)
            _content += buffer[i];
        _byte_count += l;
    }

    const std::string &Json_web_response::get_string() const {
        return _content;
    }

    std::istream &Json_web_response::get_stream() {
        _content_stream = std::stringstream (_content);
        return _content_stream;
    }

    size_t Json_web_response::size() const {
        return _byte_count;
    }

    std::ostream &operator<<(ostream &o, Json_web_response &r) {
        o << r.get_string();
        return o;
    }

    Json_web_response &operator>>(Json_web_response &r, Json_base &j) {
        r.get_string() >> j;
        return r;
    }
}


