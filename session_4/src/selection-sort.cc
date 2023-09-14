#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

auto selection_sort = []<typename T>(std::vector<T> vec) {
  std::vector<T> result = vec;

  unsigned long int i, j, indexOfMin;

  for (i = 0; i < result.size() - 1; i++) {
    indexOfMin = i;
    for (j = i + 1; j < result.size(); j++) {
      if (result[j] < result[indexOfMin]) {
        indexOfMin = j;
      }
    }
    
    if (indexOfMin != i) {
      T temp = result[i];
      result[i] = result[indexOfMin];
      result[indexOfMin] = temp;
    }
  }



  return result;
};

TEST_CASE("selection_sort should sort the vector ascending") {
  std::vector<char> expected = {'A', 'B', 'C'};
  std::vector<char> vec1 = {'A', 'B', 'C'};
  std::vector<char> vec2 = {'B', 'A', 'C'};
  std::vector<char> vec3 = {'C', 'B', 'A'};

  std::vector<char> result1 = selection_sort(vec1);
  std::vector<char> result2 = selection_sort(vec2);
  std::vector<char> result3 = selection_sort(vec3);

  CHECK_EQ(expected, result1);
  CHECK_EQ(expected, result2);
  CHECK_EQ(expected, result3);
}
