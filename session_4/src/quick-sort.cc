#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

template <typename T>
std::vector<T> quickSort(const std::vector<T>& vec) {
  if (vec.size() <= 1) {
    return vec;
  }

  T pivot = vec[0];
  std::vector<T> less, equal, greater;

  for (T element : vec) {
    if (element < pivot) {
      less.push_back(element);
    }
    else if (element > pivot) {
      greater.push_back(element);
    }
    else {
      equal.push_back(element);
    }
  }

  std::vector<T> lessSorted = quickSort(less);
  std::vector<T> greaterSorted = quickSort(greater);

  std::vector<T> result;

  result.reserve(lessSorted.size() + equal.size() + greaterSorted.size());
  result.insert(result.end(), lessSorted.begin(), lessSorted.end());
  result.insert(result.end(), equal.begin(), equal.end());
  result.insert(result.end(), greaterSorted.begin(), greaterSorted.end());

  return result;
};

TEST_CASE("quickSort should sort the vector ascending") {
  std::vector<int> expected = {1, 2, 3};
  std::vector<int> vec1 = {1, 2, 3};
  std::vector<int> vec2 = {2, 1, 3};
  std::vector<int> vec3 = {3, 2, 1};

  std::vector<int> result1 = quickSort(vec1);
  std::vector<int> result2 = quickSort(vec2);
  std::vector<int> result3 = quickSort(vec3);

  CHECK_EQ(expected, result1);
  CHECK_EQ(expected, result2);
  CHECK_EQ(expected, result3);
}
