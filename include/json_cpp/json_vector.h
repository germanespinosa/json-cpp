#include <json_cpp/json_wrapper.h>
#include<span>
namespace json_cpp {
    template<class T>
    struct Json_vector : Json_base, std::vector<T> {
        Json_vector () {};
        Json_vector (size_t s): std::vector<T>(s) {

        }
        Json_vector (size_t s, T e): std::vector<T>(s,e) {

        }
        const std::span<T> slice(unsigned int b, unsigned int e) const {
            if (b > e) throw std::logic_error("beginning index larger than end index");
            auto v = (std::vector<T> *)this;
            const std::span<T> s(*v);
            return s.subspan(b, e-b);
        }
        const std::span<T> slice(unsigned int e) const {
            return this->slice(0,e);
        }
        void json_parse(std::istream &i) override {
            if constexpr (std::is_default_constructible<T>::value) {
                if (Json_util::skip_blanks(i) != '[') throw std::logic_error("format error");
                Json_util::discard(i);
                Json_vector<T> &o = *this;
                o.clear();
                while ((Json_util::skip_blanks(i) != ']')) {
                    T value;
                    if constexpr (std::is_base_of<Json_base, T>::value) {
                        i >> value;
                    } else {
                        Json_object_wrapper<T> wrapped(value);
                        i >> wrapped;
                    }
                    o.push_back(value);
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
    };
}