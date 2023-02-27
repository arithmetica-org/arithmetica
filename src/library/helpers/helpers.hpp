#pragma once

#include <string>
#include <vector>

namespace arithmetica
{
namespace helpers
{
/// @brief Get all non-inverse trigonometric functions.
/// @return Returns a vector of all non-inverse trigonometric functions.
std::vector<std::string> &get_trigonometric_functions ();

/// @brief Get the names of all supported functions: functions that are
/// recognized by the parser.
/// @return Returns a vector of all supported functions.
std::vector<std::string> &get_supported_functions ();

/// @brief Replace all instances of a substring with another substring.
/// @param str The string to replace in.
/// @param from The substring to replace.
/// @param to The substring to replace with.
void replace_all (std::string &str, const std::string &from,
                  const std::string &to);

/// @brief Get the index of the matching bracket.
/// @param str The string to search in.
/// @param index The index of the opening or closing bracket.
size_t get_matching_bracket (const std::string &str, const size_t &index);

/// @brief Converts an array of objects to a string.
/// @tparam T The type of the objects in the array.
/// @param arr The array to convert to a string.
/// @param split The string to insert between each element of the array.
/// @param brackets The pair of strings to insert at the beginning and end of
/// the array.
/// @return Returns the array as a string.
template <typename T>
std::string
array_to_string (std::vector<T> arr, const std::string &split,
                 const std::pair<std::string, std::string> &brackets);
}
}