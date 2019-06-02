#include <utility>

#pragma once
#include "discord.hpp"

namespace discord {
    bool Asset::operator==(const Asset& rhs) {
        return url == rhs.url;
    }
    bool Asset::operator!=(const Asset& rhs) {
        return url != rhs.url;
    }
    Asset::operator bool() {
        return url.empty();
    }
    Asset::operator std::string() {
        return url;
    }
    int Asset::hash() {
        return std::hash<std::string>{}(url);
    }

    std::string const& operator()() const {
        return url;
    }

    std::string Asset::read() {
        // TODO: exception handling & body
        return {};
    }
    Asset::Asset(std::string const& str)
        : url{ str } {
    }
}  // namespace discord
