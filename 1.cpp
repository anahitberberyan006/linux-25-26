#include "../include/argument.h"

argument::argument()
        : m_name(), m_value(std::nullopt), m_type(argument_type::unknown) {}

argument::argument(std::string name, argument_type type)
        : m_name(std::move(name)), m_value(std::nullopt), m_type(type) {}

argument::argument(std::string name, std::string value)
        : m_name(std::move(name)), m_value(std::move(value)), m_type(argument_type::option) {}

argument_type argument::type() const noexcept {
return m_type;
}

const std::string& argument::name() const noexcept {
return m_name;
}

const std::optional<std::string>& argument::value() const noexcept {
return m_value;
}

bool argument::is_flag() const noexcept {
return m_type == argument_type::flag;
}

bool argument::is_option() const noexcept {
return m_type == argument_type::option;
}

bool argument::is_positional() const noexcept {
return m_type == argument_type::positional;
}

bool argument::has_value() const noexcept {
return m_value.has_value();
}

std::string argument::string() const {
    std::ostringstream oss;
    oss << m_name;
    if (m_value) oss << "=" << *m_value;
    return oss.str();
}
