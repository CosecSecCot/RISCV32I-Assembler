#include <regex>
#include <string_utils.h>

namespace string_utils {
    static const std::regex trimPattern = std::regex("^[\\s\\n]+|[\\s\\n]+$");
    std::string trim(std::string_view str) {
        return std::regex_replace(str.data(), trimPattern, "");
    }

}
