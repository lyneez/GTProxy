#pragma once
#include <string_view>

namespace utils {
    constexpr uint32_t quick_hash(const std::string_view& data) {
        uint32_t hash = 5381;
        for (const auto& c : data)
            hash = ((hash << 5) + hash) + c;
        return hash;
    }

    uint32_t proton_hash(const char* data, uint32_t length) {
        if (data) {
            uint32_t hash = 0x55555555;
            if (length >= 1) {
                while (length) {
                    hash = (hash >> 27) + (hash << 5) + *reinterpret_cast<const char*>(data++);
                    length--;
                }
            }
            else {
                while (*data) {
                    hash = (hash >> 27) + (hash << 5) + *reinterpret_cast<const char*>(data++);
                }
            }
            return hash;
        }
        return 0;
    }
}

constexpr uint32_t operator "" _qh(const char* str, std::size_t len) {
    return utils::quick_hash(std::string_view{ str, len });
}
