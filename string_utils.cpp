#include "string_utils.h"
#include <iostream>
#include <regex>

namespace string_utils {
    static const std::regex TRIM_PATTERN(R"(^[\s]+|[\s]+$)");

    // https://stackoverflow.com/a/58773060
    std::string trim(std::string_view str) {
        return std::regex_replace(str.data(), TRIM_PATTERN, "");
    }

    std::string getRgx(std::string &str, const std::regex &rgx) {
        std::smatch match;
        std::regex_search(str, match, rgx);
        return match[0].str();
    }

}
