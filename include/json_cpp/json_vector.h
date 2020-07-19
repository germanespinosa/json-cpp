#include <json_cpp/json_wrapper.h>

namespace json_cpp {
    template<class T>
    struct Json_vector : Json_base, std::vector<T> {
//        static_assert(std::is_base_of<Json_base, T>::value ||
//                      std::is_same_v < T, bool > ||
//                                          std::is_same_v < T, int > ||
//                                                              std::is_same_v < T, unsigned int > ||
//                                                                                  std::is_same_v < T, double > ||
//                                                                                                      std::is_same_v <
//                                                                                                      T, std::string > ,
//                      "Vector item type must derive from Json_base");

        void json_parse(std::istream &i) override {
            if (Json_util::skip_blanks(i) != '[') throw std::logic_error("format error");
            Json_util::discard(i);
            Json_vector<T> &o = *this;
            o.clear();
            while ((Json_util::skip_blanks(i) != ']')) {
                T value;
                if constexpr (std::is_base_of<Json_base, T>::value) {
                    i >> value;
                } else {
                    Json_wrapper<T> wrapped(value);
                    i >> wrapped;
                }
                o.push_back(value);
                if (Json_util::skip_blanks(i) != ',') break;
                Json_util::discard(i);
            }
            if (Json_util::skip_blanks(i, true) != ']') throw std::logic_error("format error");
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
                    Json_wrapper<T> wrapped(i);
                    o << wrapped;
                }
            }
            o << "]";
        }
    };
}