#include "string_utils.h"
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

    // NOTE: start >= end for reverse
    std::string reverseSlice(std::string &str, unsigned int start,
                             unsigned int end) {
        std::string slice =
            str.substr(str.length() - 1 - start, start - end + 1);
        return slice;
    }

}
