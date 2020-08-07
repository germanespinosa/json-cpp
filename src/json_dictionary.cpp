#include <json_cpp/json_dictionary.h>
#include <sstream>

using namespace json_cpp;
using namespace std;

void Json_dictionary::json_parse(istream &i) {
    if (Json_util::skip_blanks(i) == '{') {
        Json_util::discard(i);
        string name;
        while (Json_util::skip_blanks(i) != '}'){
            Item new_item;
            if (!Json_util::read_name(new_item._key, i)) throw logic_error("format error: field name");
            i >> new_item;
            items.push_back(new_item);
            if (Json_util::skip_blanks(i) != ',') break;
            Json_util::discard(i);
        }
    } else {
        throw logic_error("format error: expecting '{'");
    }
}

void Json_dictionary::json_write(ostream &o) const {
    bool first = true;
    o << '{';
    for (auto &i:items){
        if (!first) o << ',';
        first = false;
        o << '"' << i._key << "\":";
        o << i;
    }
    o << '}';
}

size_t Json_dictionary::size() {
    return items.size();
}

Json_dictionary::Item Json_dictionary::operator[](const string &key) {
    for (auto &i:items) if (i._key==key) return i;
    throw logic_error("key not found");
}

Json_dictionary Json_dictionary::Item::to_dict() {
    Json_dictionary d;
    stringstream ss(value);
    ss >> d;
    return d;
}

void Json_dictionary::Item::json_parse(istream &i) {
    int bc = 0;
    char nc = Json_util::skip_blanks(i);
    switch (nc) {
        case '"':
            require_quotes = true;
            value = Json_util::read_string(i);
            break;
        case '{':
            require_quotes = false;
            while (nc == '{' || bc){
                if (nc == '{') bc ++;
                if (nc == '}') bc --;
                value += nc;
                Json_util::discard(i);
                nc = Json_util::skip_blanks(i);
            }
            break;
        default:
            require_quotes = false;
            while (nc != ','){
                value += nc;
                Json_util::discard(i);
                nc = Json_util::skip_blanks(i);
            }
    }
}

void Json_dictionary::Item::json_write(ostream &o) const {
    if (require_quotes) o << '"';
    o << value;
    if (require_quotes) o << '"';
}
