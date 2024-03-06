#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#include <regex>
#include <string>

namespace string_utils {
    std::string trim(std::string_view str);

    // https://stackoverflow.com/a/58773060
    // return std::regex_replace(str.data(), trimPattern, "");

}

#endif
