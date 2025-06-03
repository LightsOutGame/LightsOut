#pragma once

#include <string>
#include <type_traits>

typedef std::string ComponentKey;

template<typename T>
concept ComponentLike = std::is_same<decltype(T::key), ComponentKey>::value;
