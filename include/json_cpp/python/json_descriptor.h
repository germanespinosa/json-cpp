#include <json_cpp/json_builder.h>
#include <json_cpp/json_base.h>
#include <json_cpp/json_vector.h>
#include <unordered_map>

namespace json_cpp {


    struct Json_descriptor : Json_base {
        virtual Json_descriptor* new_item() const = 0;
        void json_parse(std::istream &) override;
        void json_write(std::ostream &) const override;
        virtual ~Json_descriptor() = default;
    };

    struct Json_descriptor_container : std::vector<Json_descriptor *> {
        ~Json_descriptor_container();
        Json_descriptor_container &operator = (const Json_descriptor_container &);
    };

    struct Json_bool_descriptor :Json_descriptor {
        [[nodiscard]] Json_descriptor* new_item() const override { return new Json_bool_descriptor(); };
        bool value{};
        void json_parse(std::istream &) override;
        void json_write(std::ostream &) const override;
        ~Json_bool_descriptor() override = default;
    };

    struct Json_int_descriptor :Json_descriptor {
        [[nodiscard]] Json_descriptor* new_item() const override { return new Json_int_descriptor(); };
        int value{};
        void json_parse(std::istream &) override;
        void json_write(std::ostream &) const override;
        ~Json_int_descriptor() override = default;
    };

    struct Json_float_descriptor :Json_descriptor {
        [[nodiscard]] Json_descriptor* new_item() const override { return new Json_float_descriptor(); };
        float value{};
        void json_parse(std::istream &) override;
        void json_write(std::ostream &) const override;
        ~Json_float_descriptor() override = default;
    };

    struct Json_string_descriptor :Json_descriptor {
        [[nodiscard]] Json_descriptor* new_item() const override { return new Json_string_descriptor(); };
        std::string value{};
        void json_parse(std::istream &) override;
        void json_write(std::ostream &) const override;
        ~Json_string_descriptor() override = default;
    };

    struct Json_object_descriptor :Json_descriptor {
        [[nodiscard]] Json_descriptor* new_item() const override {
            auto *i = new Json_object_descriptor();
            *i  = *this;
            return i;
        };
        void add_member(const std::string &, Json_descriptor &, bool member_mandatory);
        Json_descriptor_container members_descriptor;
        std::vector<std::string> members_name;
        std::vector<bool> members_mandatory;
        void json_parse(std::istream &) override;
        void json_write(std::ostream &) const override;
        ~Json_object_descriptor() override = default;
    };

    struct Json_list_descriptor : Json_descriptor {
        Json_descriptor* new_item() const override { return new Json_list_descriptor(); };
        Json_descriptor_container value{};
        const Json_descriptor *item_descriptor{};
        void set_item_descriptor(const Json_descriptor &item_descriptor);
        void json_parse(std::istream &) override;
        void json_write(std::ostream &) const override;
        ~Json_list_descriptor() override;
    };
}