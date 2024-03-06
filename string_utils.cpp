#include <regex>
#include <string_utils.h>

namespace string_utils {
    static const std::regex trimPattern = std::regex("^[\\s\\n]+|[\\s\\n]+$");

    // https://stackoverflow.com/a/58773060
    std::string trim(std::string_view str) {
        return std::regex_replace(str.data(), trimPattern, "");
    }

}
