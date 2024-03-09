#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#include <regex>
#include <string>

namespace string_utils {
    static const std::regex LABEL_PATTERN(R"([a-zA-Z_]+:)");
    static const std::regex OPERATION_PATTERN(R"(^[a-z]+\b)");
    static const std::regex REGISTER_PATTERN(R"(^(r[0-6])|(zero)|(sp)\b)");
    static const std::regex IMM_PATTERN(R"(^[+-]?0?[xob]?\d+)");

    static const std::regex WHITESPACE_PATTERN(R"(^\s+)");
    static const std::regex COMMA_PATTERN(R"(^,\s*)");

    std::string trim(std::string_view str);
    std::string getRgx(std::string &_str, std::smatch &match,
                       const std::regex &rgx);
}

#endif
