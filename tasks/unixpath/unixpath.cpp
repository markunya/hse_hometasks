#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string normalized_path = static_cast<std::string>(current_working_dir);
    while (path.length() > 0) {
        size_t index_of_slash = path.find("/");
        if (index_of_slash == std::string_view::npos) {
            if (path == "..") {
                normalized_path = normalized_path.substr(0, normalized_path.rfind("/"));
                if (normalized_path.empty()) {
                    normalized_path = "/";
                }
            } else if (path != ".") {
                if (normalized_path == "/") {
                    normalized_path += path;
                } else {
                    normalized_path += "/" + static_cast<std::string>(path);
                }
            }
            break;
        }
        std::string directory = static_cast<std::string>(path.substr(0, index_of_slash));
        if (directory == "..") {
            normalized_path = normalized_path.substr(0, normalized_path.rfind("/"));
            if (normalized_path.empty()) {
                normalized_path = "/";
            }
        } else if (directory != "." && !directory.empty()) {
            if (normalized_path == "/") {
                normalized_path += directory;
            } else {
                normalized_path += "/" + directory;
            }
        }
        path.remove_prefix(index_of_slash + 1);
    }
    return normalized_path;
}
