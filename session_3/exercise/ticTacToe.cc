#include <iostream>
#include <numeric>
#include <utility>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using Token = char;
using Line = std::vector<Token>;
using Board = std::vector<Line>;
using Coordinate = std::pair<int, int>;

const std::vector<Coordinate> VALID_COORDINATES = {
  std::make_pair(0, 0),
  std::make_pair(0, 1),
  std::make_pair(0, 2),
  std::make_pair(1, 0),
  std::make_pair(1, 1),
  std::make_pair(1, 2),
  std::make_pair(2, 0),
  std::make_pair(2, 1),
  std::make_pair(2, 2),
};

auto all_of_collection = [](const auto& collection) {
  return [&collection = std::as_const(collection)](const auto& unaryPredicate) {
    return std::all_of(collection.begin(), collection.end(), unaryPredicate);
  };
};

auto any_of_collection = [](const auto& collection) {
  return [&collection = std::as_const(collection)](const auto& unaryPredicate) {
    return std::any_of(collection.begin(), collection.end(), unaryPredicate);
  };
};

auto none_of_collection = [](const auto& collection) {
  return [&collection = std::as_const(collection)](const auto& unaryPredicate) {
    return std::none_of(collection.begin(), collection.end(), unaryPredicate);
  };
};

TEST_CASE("all_of_collection") {
  std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  CHECK(all_of_collection(v)([](const auto& x) { return x >= 0 && x <= 9; }));
}

TEST_CASE("any_of_collection") {
  std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  CHECK(any_of_collection(v)([](const auto& x) { return x >= 3 && x <= 6; }));
}

TEST_CASE("none_of_collection") {
  std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  CHECK(none_of_collection(v)([](const auto& x) { return x >= 10 || x <= -1; }));
}

auto is_line_filled_with_token = [](const Line& line) {
  return [&line = std::as_const(line)](const Token& token) {
    return all_of_collection(line)([&token = std::as_const(token)](const Token& t) { return t == token; });
  };
};

auto is_line_filled_with_x = [](const Line& line) -> bool {
  return is_line_filled_with_token(line)('X');
};

auto is_line_filled_with_o = [](const Line& line) -> bool {
  return is_line_filled_with_token(line)('O');
};

TEST_CASE("is_line_filled_with_x") {
  Line line = {'X', 'X', 'X'};
  CHECK(is_line_filled_with_x(line));
}

TEST_CASE("is_line_filled_with_o") {
  Line line = {'O', 'O', 'O'};
  CHECK(is_line_filled_with_o(line));
}

template<typename TResult>
auto transform_all = [](const auto& collection) {
  return [&collection = std::as_const(collection)](const auto& lambda) {
    TResult result;
    result.reserve(collection.size());
    std::transform(collection.begin(), collection.end(), std::back_inserter(result), lambda);
    return result;
  };
};

auto access_at_coordinate = [](const Board& board) {
  return [&board = std::as_const(board)](const Coordinate& coordinate) {
    return board[coordinate.first][coordinate.second];
  };
};

auto project_coordinates = [](const Board& board) {
  return [&board = std::as_const(board)](const std::vector<Coordinate>& coordinates) {
    return transform_all<Line>(coordinates)(access_at_coordinate(board));
  };
};

auto project_all_coordinates = [](const Board& board) {
  return project_coordinates(board)(VALID_COORDINATES);
};

TEST_CASE("access_at_coordinate") {
  Board board = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };

  CHECK_EQ(access_at_coordinate(board)(std::make_pair(0, 0)), 'X');
  CHECK_EQ(access_at_coordinate(board)(std::make_pair(1, 1)), 'O');
  CHECK_EQ(access_at_coordinate(board)(std::make_pair(2, 2)), ' ');
}

TEST_CASE("project_all_coordinates") {
  Board board = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };

  Line expected_result = {'X', ' ', 'O', 'X', 'O', ' ', ' ', ' ', ' '};

  CHECK_EQ(expected_result, project_all_coordinates(board));
}

auto to_range = [](const auto& collection) {
  std::vector<int> range(collection.size());
  std::iota(begin(range), end(range), 0);
  return range;
};

auto get_coordinates_by_row_index = [](const Board& board) {
  return [&board = std::as_const(board)](const int index) {
    const auto range = to_range(board);
    return transform_all<std::vector<Coordinate>>(range)([index](const auto i) {
      return std::make_pair(index, i);
    });
  };
};

auto get_coordinates_by_column_index = [](const Board& board) {
  return [&board = std::as_const(board)](const int index) {
    const auto range = to_range(board);
    return transform_all<std::vector<Coordinate>>(range)([index](const auto i) {
      return std::make_pair(i, index);
    });
  };
};

auto get_row_by_row_index = [](const Board& board) {
  return [&board = std::as_const(board)](const int index) {
    return project_coordinates(board)(get_coordinates_by_row_index(board)(index));
  };
};

auto get_column_by_column_index = [](const Board& board) {
  return [&board = std::as_const(board)](const int index) {
    return project_coordinates(board)(get_coordinates_by_column_index(board)(index));
  };
};

TEST_CASE("get_row_by_row_index") {
  Board board = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };

  Line expected_line_1 = {'X', ' ', 'O'};
  Line expected_line_2 = {'X', 'O', ' '};
  Line expected_line_3 = {' ', ' ', ' '};

  CHECK_EQ(expected_line_1, get_row_by_row_index(board)(0));
  CHECK_EQ(expected_line_2, get_row_by_row_index(board)(1));
  CHECK_EQ(expected_line_3, get_row_by_row_index(board)(2));
}

TEST_CASE("get_column_by_column_index") {
  Board board = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };

  Line expected_column_1 = {'X', 'X', ' '};
  Line expected_column_2 = {' ', 'O', ' '};
  Line expected_column_3 = {'O', ' ', ' '};

  CHECK_EQ(expected_column_1, get_column_by_column_index(board)(0));
  CHECK_EQ(expected_column_2, get_column_by_column_index(board)(1));
  CHECK_EQ(expected_column_3, get_column_by_column_index(board)(2));
}

// EXERCISE 1: The difference in the number of tokens for the two players > 1

auto count_all = [](const auto& collection) {
  return [&collection = std::as_const(collection)](const auto& value) {
    return std::count(collection.begin(), collection.end(), value);
  };
};

auto get_number_of_tokens = [](const Board& board) {
  return [&board = std::as_const(board)](const Token& token) {
    return count_all(project_all_coordinates(board))(token);
  };
};

auto get_number_of_x = [](const Board& board) {
  return get_number_of_tokens(board)('X');
};

auto get_number_of_o = [](const Board& board) {
  return get_number_of_tokens(board)('O');
};

auto get_difference_of_x_and_o = [](const Board& board) {
  return std::abs(get_number_of_x(board) - get_number_of_o(board));
};

auto is_difference_of_x_and_o_greater_1 = [](const Board& board) {
  return get_difference_of_x_and_o(board) > 1;
};

TEST_CASE("get_number_of_x") {
  Board board = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };

  int expected = 2;

  CHECK_EQ(expected, get_number_of_x(board));
}

TEST_CASE("get_number_of_o") {
  Board board = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };

  int expected = 2;

  CHECK_EQ(expected, get_number_of_o(board));  
}

TEST_CASE("get_difference_of_x_and_o") {
  Board board = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };

  int expected = 0;

  CHECK_EQ(expected, get_difference_of_x_and_o(board));  
}

TEST_CASE("is_difference_of_x_and_o_greater_1") {
  Board board_1 = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };
  Board board_2 = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {'X', ' ', 'X'},
  };
  Board board_3 = {
    {'O', ' ', 'O'},
    {'O', 'O', ' '},
    {'O', ' ', 'X'},
  };

  CHECK(!is_difference_of_x_and_o_greater_1(board_1));  
  CHECK(is_difference_of_x_and_o_greater_1(board_2));  
  CHECK(is_difference_of_x_and_o_greater_1(board_3));  
}

// EXERCISE 2 & 3 : Check for correct/wrong tokens

auto is_token_correct = [](const Token& token) {
  return token == 'X' ||
    token == 'O' ||
    token == ' ';
};

auto are_all_tokens_correct = [](const Board& board) {
  return all_of_collection(project_all_coordinates(board))(is_token_correct);
};

auto is_at_least_one_token_incorrect = [](const Board& board) {
  return !are_all_tokens_correct(board);
};

TEST_CASE("are_all_tokens_correct") {
  Board board_1 = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };
    Board board_2 = {
    {'X', 'F', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };

  CHECK(are_all_tokens_correct(board_1));
  CHECK(!are_all_tokens_correct(board_2));
}

TEST_CASE("is_at_least_one_token_incorrect") {
  Board board_1 = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };
    Board board_2 = {
    {'X', 'F', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };

  CHECK(!is_at_least_one_token_incorrect(board_1));
  CHECK(is_at_least_one_token_incorrect(board_2));
}

// Exercise 4 & 5: Board-dimension is correct/wrong

auto get_all_rows = [](const Board& board) {
  const auto range = to_range(board);
  return transform_all<std::vector<Line>>(range)([&board = std::as_const(board)](const auto index) {
    return get_row_by_row_index(board)(index);
  });
};

auto get_all_columns = [](const Board& board) {
  const auto range = to_range(board);
  return transform_all<std::vector<Line>>(range)([&board = std::as_const(board)](const auto index) {
    return get_column_by_column_index(board)(index);
  });
};

auto collection_has_length = [](const auto& collection) {
  return [&collection = std::as_const(collection)](const int length) {
    return collection.size() == length;
  };
};

auto line_has_length_3 = [](const Line& line) {
  return collection_has_length(line)(3);
};

auto all_rows_have_length_3 = [](const Board& board) {
  return all_of_collection(get_all_rows(board))(line_has_length_3);
};

auto all_columns_have_length_3 = [](const Board& board) {
  return all_of_collection(get_all_columns(board))(line_has_length_3);
};

auto dimension_is_correct = [](const Board& board) {
  return all_rows_have_length_3(board) && all_columns_have_length_3(board);
};

auto dimension_is_wrong = [](const Board& board) {
  return !dimension_is_correct(board);
};

TEST_CASE("dimension_is_correct") {
  Board board_1 = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };
    Board board_2 = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
  };
    Board board_3 = {
    {'X', ' ', 'O'},
    {'X', 'O'},
    {' ', ' ', ' '},
    {' ', ' ', ' ', 'X'},
  };

  CHECK(dimension_is_correct(board_1));
  CHECK(!dimension_is_correct(board_2));
  CHECK(!dimension_is_correct(board_3));
}

TEST_CASE("dimension_is_wrong") {
    Board board_1 = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
  };
    Board board_2 = {
    {'X', ' ', 'O'},
    {'X', 'O', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
  };
    Board board_3 = {
    {'X', ' ', 'O'},
    {'X', 'O'},
    {' ', ' ', ' '},
    {' ', ' ', ' ', 'X'},
  };

  CHECK(!dimension_is_wrong(board_1));
  CHECK(dimension_is_wrong(board_2));
  CHECK(dimension_is_wrong(board_3));
}
