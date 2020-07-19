#include <json_cpp/json_builder.h>
#include <json_cpp/json_util.h>

using namespace  std;

namespace json_cpp{

    Json_builder::Json_member::Json_member(std::string name, bool mandatory, std::unique_ptr<Json_wrapped>  ref):
        name(name), mandatory(mandatory), ref(std::move(ref)){ }

    void Json_builder::json_add_member(std::string name, bool mandatory, std::unique_ptr<Json_wrapped> ref) {
        _members.emplace_back(name,mandatory,std::move(ref));
    }

    void Json_builder::json_parse(istream &i) {
        if (Json_util::skip_blanks(i) == '{') {
            Json_util::discard(i);
            string name;
            while (Json_util::skip_blanks(i) != '}') {
                if (!Json_util::read_name(name, i)) throw logic_error("format error: field name");
                auto &member = _member(name);
                member.ref->json_parse(i);
                if (Json_util::skip_blanks(i) != ',') break;
                Json_util::discard(i);
            }
            if (Json_util::skip_blanks(i) != '}') {
                throw logic_error("format error: expecting '}'");
            }
            Json_util::discard(i);
        } else {
            throw logic_error("format error: expecting '{'");
        }
    }

    void Json_builder::json_write(ostream &o) const {
        bool first = true;
        o << '{';
        for (auto &m:_members){
            if (!first) o<< ',';
            first = false;
            o<< '"' << m.name << '"' << ':';
            m.ref->json_write(o);
        }
        o << '}';
    }

    Json_builder::Json_member &Json_builder::_member(const std::string &name) {
        for (auto &m: _members){
            if (m.name == name) return m;
        }
        throw logic_error("member not found '" + name + "'");;
    }
}