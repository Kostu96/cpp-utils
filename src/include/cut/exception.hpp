#pragma once
#include <format>
#include <stacktrace>
#include <stdexcept>
#include <string>
#include <ranges>
#include <filesystem>

namespace cut {

class Exception :
    public std::runtime_error {
public:
    explicit Exception(const std::string& what, size_t skip = 0) :
        std::runtime_error(what),
        trace_(std::stacktrace::current(skip + 1)) {}

    const std::stacktrace& stacktrace() const { return trace_; }
private:
    std::stacktrace trace_;
};

template<typename ...Args>
void ensure(bool predicate, std::string_view msg, Args&& ...args) {
    if (!predicate) {
        throw Exception(std::vformat(msg, std::make_format_args(args...)), 1);
    }
}

} // namespace cut

template<>
struct std::formatter<cut::Exception> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return cbegin(ctx);
    }

    auto format(const cut::Exception& obj, std::format_context& ctx) const {
        std::stringstream stream;
        auto& stack = obj.stacktrace();
        auto root = std::filesystem::current_path();
        for (auto&& [idx, entry] : std::views::enumerate(stack)) {
            std::string source_file = entry.source_file();
            std::filesystem::path path{ source_file };
            path = path.lexically_relative(root);
            std::string path_str = !path.empty() ? path.string() : source_file;
            if (!path_str.empty()) {
                stream << std::format("{:2}> {}({}): {}\n", idx, path_str, entry.source_line(), entry.description());
            }
            else {
                stream << std::format("{:2}> {}\n", idx, entry.description());
            }
        }
        return std::format_to(ctx.out(), "Exception: {}\n{}", obj.what(), stream.view());
    }
};
