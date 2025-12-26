#pragma once

#include <string>
#include <type_traits>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

namespace io {

    template <typename T>
    void serialize(const T& obj, const std::string& file) {
        static_assert(std::is_trivially_copyable<T>::value,
                      "T must be trivially copyable");

        int fd = open(file.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644);
        write(fd, &obj, sizeof(T));
        close(fd);
    }

    template <typename T>
    T deserialize(const std::string& file) {
        static_assert(std::is_trivially_copyable<T>::value,
                      "T must be trivially copyable");

        T obj = {};
        int fd = open(file.c_str(), O_RDONLY);
        read(fd, &obj, sizeof(T));
        close(fd);
        return obj;
    }

}
