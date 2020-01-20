#pragma once

#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>

template <typename T>
using Optional = boost::optional<T>;
