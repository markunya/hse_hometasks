#pragma once

#include <string>
#include <string_view>
#include <iostream>

class UnixPath {
public:
    explicit UnixPath(std::string_view initial_dir) {
        std::string normalized_path = "/";
        while (!initial_dir.empty()) {
            size_t index_of_slash = initial_dir.find("/");
            if (index_of_slash == std::string_view::npos) {
                index_of_slash = initial_dir.length();
            }
            std::string directory = static_cast<std::string>(initial_dir.substr(0, index_of_slash));
            if (directory == "..") {
                normalized_path = normalized_path.substr(0, normalized_path.rfind("/"));
                if (normalized_path.empty()) {
                    normalized_path = "/";
                }
                initial_dir.remove_prefix(index_of_slash == initial_dir.length() ? index_of_slash
                                                                                                 : index_of_slash + 1);
                continue;
            }
            if (directory != "." && !directory.empty()) {
                if (normalized_path == "/") {
                    normalized_path.clear();
                }
                normalized_path += "/" + directory;
            }
            initial_dir.remove_prefix(index_of_slash == initial_dir.length() ? index_of_slash
                                                                                             : index_of_slash + 1);
        }
        initial_dir_ = normalized_path;
        absolute_path_ = normalized_path;
    };

    void ChangeDirectory(std::string_view path) {
        std::string normalized_path = path.starts_with("/") ? "/" : absolute_path_;
        while (!path.empty()) {
            size_t index_of_slash = path.find("/");
            if (index_of_slash == std::string_view::npos) {
                index_of_slash = path.length();
            }
            std::string directory = static_cast<std::string>(path.substr(0, index_of_slash));
            if (directory == "..") {
                normalized_path = normalized_path.substr(0, normalized_path.rfind("/"));
                if (normalized_path.empty()) {
                    normalized_path = "/";
                }
                path.remove_prefix(index_of_slash == path.length() ? index_of_slash : index_of_slash + 1);
                continue;
            }
            if (directory != "." && !directory.empty()) {
                if (normalized_path == "/") {
                    normalized_path.clear();
                }
                normalized_path += "/" + directory;
            }
            path.remove_prefix(index_of_slash == path.length() ? index_of_slash : index_of_slash + 1);
        }
        absolute_path_ = normalized_path;
    };

    std::string GetAbsolutePath() const {
        return absolute_path_;
    };

    std::string GetRelativePath() const {
        std::string relative_path;
        std::string_view initial_dir = initial_dir_;
        if (!initial_dir.empty()) {
            initial_dir.remove_prefix(1);
        }
        std::string_view absolute_path = absolute_path_;
        if (!absolute_path.empty()) {
            absolute_path.remove_prefix(1);
        }
        size_t index_of_slash_in_absolute_path = absolute_path.find("/");
        size_t index_of_slash_in_initial_dir = initial_dir.find("/");
        if (absolute_path.starts_with(initial_dir)) {
            absolute_path.remove_prefix(initial_dir.length());
            relative_path = "." + static_cast<std::string>(absolute_path);
            return relative_path;
        }
        while (index_of_slash_in_absolute_path != std::string_view::npos &&
               index_of_slash_in_initial_dir != std::string_view::npos) {
            if (absolute_path.substr(0, index_of_slash_in_absolute_path) !=
                initial_dir.substr(0, index_of_slash_in_initial_dir)) {
                break;
            }
            initial_dir.remove_prefix(index_of_slash_in_initial_dir + 1);
            absolute_path.remove_prefix(index_of_slash_in_absolute_path + 1);
            index_of_slash_in_absolute_path = absolute_path.find("/");
            index_of_slash_in_initial_dir = initial_dir.find("/");
        }
        size_t amount_of_slashes = 0;
        for (auto i : initial_dir) {
            if (i == '/') {
                amount_of_slashes += 1;
            }
        }
        for (size_t i = 0; i < amount_of_slashes + 1; ++i) {
            relative_path += "../";
        }
        relative_path += absolute_path;
        return relative_path;
    };

private:
    std::string initial_dir_;
    std::string absolute_path_;
};