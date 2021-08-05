#include <iostream>
#include <json_cpp/json_base64.h>
#include <json_cpp/json_util.h>

#define STRING_PARSE_ERROR throw logic_error("error converting to string")
#define INT_PARSE_ERROR throw logic_error("error converting to int")
#define DOUBLE_PARSE_ERROR throw logic_error("decimal error converting to double")

using namespace std;
namespace json_cpp {
    void Json_util::write_value(std::ostream &o, const Json_buffer &buffer) {
        Json_base64::write(o, buffer);
    }

    void Json_util::read_value(istream &i, Json_buffer &buffer) {
        Json_base64::read(read_string(i), buffer);
    }

    void Json_util::discard(istream &i) {
        char c;
        i >> c;
    }

    char Json_util::skip_blanks(istream &i, bool s) {
        i >> ws;
        char c;
        if (s) i >> c; else c = i.peek();
        return c;
    }

    char Json_util::skip_blanks(istream &i) {
        return skip_blanks(i, false);
    }

    std::string Json_util::read_string(istream &i) {
        char c;
        if (skip_blanks(i) != '"') STRING_PARSE_ERROR;
        discard(i);
        string s;
        do {
            i >> c;
            if (c != '"') s += c;
        } while (c != '"');
        return s;
    }

    double Json_util::read_double(istream &i) {
        char c = skip_blanks(i);
        if (!isdigit(c) && c != '.' && c != '-') DOUBLE_PARSE_ERROR;
        double r;
        i >> r;
        return r;
    }

    int Json_util::read_int(istream &i) {
        char c = skip_blanks(i);
        if (!isdigit(c) && c != '-') INT_PARSE_ERROR;
        int r;
        i >> r;
        return r;
    }

    bool Json_util::read_name(string &s, istream &i) {
        s = read_string(i);
        return skip_blanks(i, true) == ':';
    }

    void Json_util::read_value(istream &i, bool &v) {
        v = read_int(i);
    }

    void Json_util::read_value(istream &i, double &v) {
        v = read_double(i);
    }

    void Json_util::read_value(istream &i, int &v) {
        v = read_int(i);
    }

    void Json_util::read_value(istream &i, unsigned int &v) {
        v = read_int(i);
    }

    void Json_util::read_value(istream &i, string &v) {
        v = read_string(i);
    }

    void Json_util::write_value(ostream &o,const bool &v) {
        o << v;
    }

    void Json_util::write_value(ostream &o,const double &v) {
        o << v;
    }

    void Json_util::write_value(ostream &o,const int &v) {
        o << v;
    }

    void Json_util::write_value(ostream &o,const unsigned int &v) {
        o << v;
    }

    void Json_util::write_value(ostream &o,const string &v) {
        o << '"' << v << '"';
    }

}