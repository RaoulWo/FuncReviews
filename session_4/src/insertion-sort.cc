#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <vector>

auto insertion_sort = []<typename T>(const std::vector<T>& vec) {
  std::vector<T> result = vec;

  unsigned long int i;
  int j;
  T key;
  for (i = 1; i < result.size(); i++) {
    key = result[i];
    j = i - 1;

    while (j >= 0 && result[j] > key) {
      result[j + 1] = result[j];
      j = j - 1;
    }
    result[j + 1] = key;
  }

  return result;
};

TEST_CASE("insertion_sort should sort the vector ascending") {
  std::vector<char> expected = {'A', 'B', 'C'};
  std::vector<char> vec1 = {'A', 'B', 'C'};
  std::vector<char> vec2 = {'B', 'A', 'C'};
  std::vector<char> vec3 = {'C', 'B', 'A'};

  std::vector<char> result1 = insertion_sort(vec1);
  std::vector<char> result2 = insertion_sort(vec2);
  std::vector<char> result3 = insertion_sort(vec3);

  CHECK_EQ(expected, result1);
  CHECK_EQ(expected, result2);
  CHECK_EQ(expected, result3);
}
