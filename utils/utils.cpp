#include <string>
#include <unistd.h>
#include <curl/curl.h>

#include "root_directory.h"
#include "utils.hpp"

std::string find_accessible_file(const char *url)
{
    std::string full_path = std::string(source_dir) + std::string("/") + std::string(url);

    if (access(full_path.c_str(), F_OK) == 0) {
        return full_path;
    }

    full_path = std::string(prefix_dir) + std::string("/data/") + std::string(url);

    if (access(full_path.c_str(), F_OK) == 0) {
        return full_path;
    }

    return "";
}
