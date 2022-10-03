#pragma once
#include <json_cpp/json_wrapper.h>
namespace json_cpp {
    template<class T>
    struct Json_vector : Json_base, std::vector<T> {
        Json_vector () {};
        Json_vector (size_t s): std::vector<T>(s) {

        }
        Json_vector (size_t s, T e): std::vector<T>(s,e) {

        }
        std::string json_type() const override {
            return "array";
        }

        virtual inline T &new_item() { return this->template emplace_back(); }

        void json_parse(std::istream &i) override {
            if constexpr (std::is_default_constructible<T>::value) {
                if (Json_util::skip_blanks(i) != '[') throw std::logic_error("format error");
                Json_util::discard(i);
                Json_vector<T> &o = *this;
                o.clear();
                while ((Json_util::skip_blanks(i) != ']')) {
                    auto &value = new_item();
                    if constexpr (std::is_base_of<Json_base, T>::value) {
                        i >> value;
                    } else {
                        Json_object_wrapper<T> wrapped(value);
                        i >> wrapped;
                    }
                    //o.push_back(value);
                    if (Json_util::skip_blanks(i) != ',') break;
                    Json_util::discard(i);
                }
                if (Json_util::skip_blanks(i, true) != ']') throw std::logic_error("format error");
            }
        }

        void json_write(std::ostream &o) const override {
            o << "[";
            bool first = true;
            for (const auto &i:*this) {
                if (!first) o << ",";
                first = false;
                if constexpr (std::is_base_of<Json_base, T>::value) {
                    o << i;
                } else {
                    Json_object_wrapper<T> wrapped(i);
                    o << wrapped;
                }
            }
            o << "]";
        }

        int index_of(const T &o) const {
            for (unsigned int i=0;i<this->size(); i++) if ((*this)[i]==o) return i;
            return -1;
        }

        bool contains(const T &o) const {
            return index_of(o) != -1;
        }

        T get_item_at(unsigned int index) {
            return (*(this))[index];
        }

        void set_item_at(unsigned int index, T &item) {
            if (index >= this->size()) {
                throw std::runtime_error("key " + std::to_string(index) + " not found.");
            }
            (*(this))[index] = item;
        }

        Json_vector<T> reversed() const {
            Json_vector<T> r(this->size());
            size_t index = this->size();
            for(const auto &i:(*this)){
                r[--index] = i;
            }
            return r;
        }

        Json_vector<T> &operator = (const std::vector<T>&v) {
            this->clear();
            for (const auto &i:v) this->push_back(i);
            return *this;
        };
    };
}