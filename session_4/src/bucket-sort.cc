#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <algorithm>
#include <vector>

auto bucket_sort = []<typename T>(const std::vector<T>& vec) {
  std::vector<T> result = vec;
  std::vector<std::vector<T>> buckets(result.size());

  for (unsigned long int i = 0; i < result.size(); i++) {
    int bucketIndex = static_cast<int>(result.size() * result[i]);
    buckets[bucketIndex].push_back(result[i]);
  }

  for (unsigned long int i = 0; i < result.size(); i++) {
    std::sort(buckets[i].begin(), buckets[i].end());
  }

  int index = 0;
  for (unsigned long int i = 0; i < result.size(); i++) {
    for (unsigned long int j = 0; j < buckets[i].size(); j++) {
      result[index] = buckets[i][j];
      index++;
    }
  }

  return result;
};

TEST_CASE("bucket_sort should sort the vector ascending") {
  std::vector<double> expected = {0.12, 0.24, 0.36, 0.48, 0.6};
  std::vector<double> vec1 = {0.12, 0.24, 0.36, 0.48, 0.6};
  std::vector<double> vec2 = {0.36, 0.12, 0.6, 0.24, 0.48};
  std::vector<double> vec3 = {0.6, 0.48, 0.36, 0.24, 0.12};

  std::vector<double> result1 = bucket_sort(vec1);
  std::vector<double> result2 = bucket_sort(vec2);
  std::vector<double> result3 = bucket_sort(vec3);

  CHECK_EQ(expected, result1);
  CHECK_EQ(expected, result2);
  CHECK_EQ(expected, result3);
}
