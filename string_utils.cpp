#include "string_utils.h"
#include <iostream>
#include <regex>

namespace string_utils {
    static const std::regex TRIM_PATTERN(R"(^[\s]+|[\s]+$)");

    // https://stackoverflow.com/a/58773060
    std::string trim(std::string_view str) {
        return std::regex_replace(str.data(), TRIM_PATTERN, "");
    }

    std::string getRgx(std::string &_str, std::smatch &match,
                       const std::regex &rgx) {
        std::regex_search(_str, match, rgx);
        if (!match.empty()) {
            std::cout << match[0] << '\n';
            _str = _str.substr(match[0].str().length());
            return match[0];
        }

        std::cout << "Invalid Operation !!!\n";
        return "";
    }
}
