#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <functional>
#include <string>
#include <vector>

auto bubble_sort = []<typename T>(const std::vector<T>& vec) {
  return [&vec = std::as_const(vec)](const std::function<bool(const T&, const T&)> comparator) {
    std::vector<T> result = vec;

    long unsigned int i, j;
    bool swapped;
    for (i = 0; i < result.size() - 1; i++) {
      swapped = false;
      for (j = 0; j < result.size() - i - 1; j++) {
        if (comparator(result[j], result[j + 1])) {
          T temp = result[j];
          result[j] = result[j+1];
          result[j+1] = temp;
          swapped = true;
        }
      }

      if (!swapped) {
        return result;
      }
    }

    return result;
  };
};

TEST_CASE("bubble_sort should sort the vector ascending") {
  std::vector<int> expected = {1, 2, 3, 4, 5};
  std::vector<int> vec1 = {1, 2, 3, 4, 5};
  std::vector<int> vec2 = {3, 2, 1, 5, 4};
  std::vector<int> vec3 = {5, 4, 3, 2, 1};

  std::vector<int> result1 = bubble_sort(vec1)([](const int& left, const int& right) { return left > right; });
  std::vector<int> result2 = bubble_sort(vec2)([](const int& left, const int& right) { return left > right; });
  std::vector<int> result3 = bubble_sort(vec3)([](const int& left, const int& right) { return left > right; });

  CHECK_EQ(expected, result1);
  CHECK_EQ(expected, result2);
  CHECK_EQ(expected, result3);
}

TEST_CASE("bubble_sort should sort the vector descending") {
  std::vector<std::string> expected = {"E", "D", "C", "B", "A"};
  std::vector<std::string> vec1 = {"E", "D", "C", "B", "A"};
  std::vector<std::string> vec2 = {"C", "B", "A", "E", "D"};
  std::vector<std::string> vec3 = {"A", "B", "C", "D", "E"};

  std::vector<std::string> result1 = bubble_sort(vec1)([](const std::string& left, const std::string& right) { return left < right; });
  std::vector<std::string> result2 = bubble_sort(vec2)([](const std::string& left, const std::string& right) { return left < right; });
  std::vector<std::string> result3 = bubble_sort(vec3)([](const std::string& left, const std::string& right) { return left < right; });

  CHECK_EQ(expected, result1);
  CHECK_EQ(expected, result2);
  CHECK_EQ(expected, result3);
}