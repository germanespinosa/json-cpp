#include <json_cpp/python/json_descriptor.h>
#include <json_cpp/json_builder.h>
#include <json_cpp/json_object.h>

namespace json_cpp {

    void Json_descriptor::json_write(std::ostream &o) const {
        o << "null";
    }

    void Json_descriptor::json_parse(std::istream &i) {
        Json_util::read_null(i);
    }

    void Json_bool_descriptor::json_write(std::ostream &o) const {
        Json_util::write_value(o, value);
    }

    void Json_bool_descriptor::json_parse(std::istream &i) {
        value = Json_util::read_bool(i);
    }

    void Json_int_descriptor::json_write(std::ostream &o) const {
        Json_util::write_value(o, value);
    }

    void Json_int_descriptor::json_parse(std::istream &i) {
        value = Json_util::read_int(i);
    }


    void Json_float_descriptor::json_write(std::ostream &o) const {
        Json_util::write_value(o, value);
    }

    void Json_float_descriptor::json_parse(std::istream &i) {
        value = (float)Json_util::read_double(i);
    }

    void Json_string_descriptor::json_write(std::ostream &o) const {
        Json_util::write_value(o, value);
    }

    void Json_string_descriptor::json_parse(std::istream &i) {
        value = Json_util::read_string(i);
    }

    void Json_object_descriptor::json_write(std::ostream &o) const {
        Json_builder jb;
        for (size_t index = 0; index < members_descriptor.size(); index++){
            Add_member_with_name(*members_descriptor[index], members_mandatory[index], members_name[index]);
        }
        jb.json_write(o);
    }

    void Json_object_descriptor::json_parse(std::istream &i) {
        Json_builder jb;
        for (size_t index = 0; index < members_descriptor.size(); index++){
            Add_member_with_name(*members_descriptor[index], members_mandatory[index], members_name[index]);
        }
        jb.json_parse(i);
    }

    void Json_object_descriptor::add_member(const std::string &member_name, Json_descriptor &member_descriptor, bool member_mandatory) {
        members_descriptor.emplace_back(member_descriptor.new_item());
        members_name.emplace_back(member_name);
        members_mandatory.emplace_back(member_mandatory);
    }

    void Json_list_descriptor::json_parse(std::istream &i) {
        if (Json_util::skip_blanks(i) != '[') throw std::logic_error("format error");
        Json_util::discard(i);
        value.clear();
        while ((Json_util::skip_blanks(i) != ']')) {
            auto item = value.emplace_back(item_descriptor->new_item());
            item->json_parse(i);
            if (Json_util::skip_blanks(i) != ',') break;
            Json_util::discard(i);
        }
        if (Json_util::skip_blanks(i, true) != ']') throw std::logic_error("format error");
    }

    void Json_list_descriptor::json_write(std::ostream &o) const {
        o << '[';
        bool first = true;
        for (auto &e:value){
            if (!first) o << ',';
            first = false;
            e->json_write(o);
        }
        o << ']';
    }

    void Json_list_descriptor::set_item_descriptor(const Json_descriptor &id) {
        item_descriptor = &id;
    }

    Json_list_descriptor::~Json_list_descriptor() {
    }

    Json_descriptor_container::~Json_descriptor_container() {
        for (auto *p:*this) delete p;
    }

    Json_descriptor_container &Json_descriptor_container::operator=(const Json_descriptor_container &o) {
        clear();
        for (auto *i:o) push_back(i->new_item());
        return *this;
    }
}