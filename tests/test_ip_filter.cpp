#include "Parser.h"
#include <gtest/gtest.h>


TEST(PARSER, EMPTY_INPUT)
{
    // Arrange
    std::string input;

    // Act
    std::vector<std::string> tokens = split(input, '.');

    // Assert
    ASSERT_EQ(tokens.size(), 0);
}

TEST(PARSER, DOESNT_CONTAIN_DELIMETER)
{
    // Arrange
    std::string input = "192";

    // Act
    std::vector<std::string> tokens = split(input, '.');

    // Assert
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(input, tokens[0]);
}

TEST(PARSER, EXTRA_DELIMITER)
{
    // Arrange
    std::string first = "192";
    std::string second = "168";
    std::string input = first + "." + second + ".";

    // Act
    std::vector<std::string> tokens = split(input, '.');

    // Assert
    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(first, tokens[0]);
    ASSERT_EQ(second, tokens[1]);
}

TEST(PARSER, RIGHT_INPUT)
{
    // Arrange
    std::string first = "192";
    std::string second = "168";
    std::string input = first + "." + second;

    // Act
    std::vector<std::string> tokens = split(input, '.');

    // Assert
    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(first, tokens[0]);
    ASSERT_EQ(second, tokens[1]);
}
