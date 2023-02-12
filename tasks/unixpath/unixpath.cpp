#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string normalized_path = "/";
    if (!path.starts_with("/")) {
        while (!current_working_dir.empty()) {
            size_t index_of_slash = current_working_dir.find("/");
            if (index_of_slash == std::string_view::npos) {
                index_of_slash = current_working_dir.length();
            }
            std::string directory = static_cast<std::string>(current_working_dir.substr(0, index_of_slash));
            if (directory == "..") {
                normalized_path = normalized_path.substr(0, normalized_path.rfind("/"));
                if (normalized_path.empty()) {
                    normalized_path = "/";
                }
            } else if (directory != "." && !directory.empty()) {
                if (normalized_path == "/") {
                    normalized_path.clear();
                }
                normalized_path += "/" + directory;
            }
            current_working_dir.remove_prefix(index_of_slash == current_working_dir.length() ? index_of_slash : index_of_slash + 1);
        }
    }
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
        } else if (directory != "." && !directory.empty()) {
            if (normalized_path == "/") {
                normalized_path.clear();
            }
            normalized_path += "/" + directory;
        }
        path.remove_prefix(index_of_slash == path.length() ? index_of_slash : index_of_slash + 1);
    }
    return normalized_path;
}
