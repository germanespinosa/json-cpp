#include <json_cpp/json_builder.h>
#include <json_cpp/json_util.h>

using namespace  std;

namespace json_cpp{

    Json_builder::Json_member::Json_member(std::string name, bool mandatory, std::unique_ptr<Json_wrapped>  ref):
        name(name), mandatory(mandatory), ref(std::move(ref)){ }

    void Json_builder::json_add_member(std::string name, bool mandatory, std::unique_ptr<Json_wrapped> ref) {
        members.emplace_back(name, mandatory, std::move(ref));
    }

    void Json_builder::json_parse(istream &i) {
        vector<string> members_name;
        if (Json_util::skip_blanks(i) == '{') {
            Json_util::discard(i);
            string name;
            while (Json_util::skip_blanks(i) != '}') {
                if (!Json_util::read_name(name, i)) throw logic_error("format error: field name");
                if (std::find(_ignored_members.begin(), _ignored_members.end(), name) != _ignored_members.end())
                {
                    if (Json_util::skip_blanks(i) == '"' ) {
                        Json_util::read_string(i);
                    } else {
                        while (Json_util::skip_blanks(i)!=',') {
                            Json_util::discard(i);
                        };
                    }
                } else {
                    members_name.push_back(name);
                    auto &member = _member(name);
                    member.ref->json_parse(i);
                }
                if (Json_util::skip_blanks(i) != ',') break;
                Json_util::discard(i);
            }
            if (Json_util::skip_blanks(i) != '}') {
                throw logic_error("format error: expecting '}'");
            }
            Json_util::discard(i);
            _check_mandatory_members(members_name);
        } else {
            throw logic_error("format error: expecting '{'");
        }
    }

    void Json_builder::json_write(ostream &o) const {
        bool first = true;
        o << '{';
        for (auto &m:members){
            if (!first) o<< ',';
            first = false;
            o<< '"' << m.name << '"' << ':';
            m.ref->json_write(o);
        }
        o << '}';
    }

    Json_builder::Json_member &Json_builder::_member(const std::string &name) {
        for (auto &m: members){
            if (m.name == name) return m;
        }
        throw logic_error("member not found '" + name + "'");
    }

    void Json_builder::_check_mandatory_members(const vector<std::string> &names) {
        for (auto &member:members){
            if (member.mandatory){
                bool found = false;
                for (auto &name:names){
                    if (name == member.name) {
                        found = true;
                        break;
                    }
                }
                if (!found) throw logic_error("member '" + member.name + "' missing and marked as mandatory");
            }
        }
    }

    void Json_builder::json_ignore_member(const std::string &member_name) {
        _ignored_members.push_back(member_name);
    }
}