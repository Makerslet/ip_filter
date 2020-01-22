#include "Parser.h"
#include "IpAddr.h"
#include "Filter.h"
#include <list>
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

TEST(IPADDR_CLASS, WRONG_TOKENS_NUMBER)
{
    // Arrange
    std::vector<std::string> tokens;

    // Act
    ipv4_addr ip_addr(tokens);

    // Assert
    ASSERT_TRUE(ip_addr.empty());
}

TEST(IPADDR_CLASS, NUMBER_IN_TOKEN_OUT_OF_RANGE)
{
    // Arrange
    std::vector<std::string> tokens = {"192","168","1","600"};

    // Act
    try {
        ipv4_addr ip_addr(tokens);
    } catch (const std::invalid_argument& ex) {
        std::string error_msg = ex.what();
        ASSERT_EQ(error_msg, "token out of range");
    }
}

TEST(IPADDR_CLASS, OPERATOR_SQ_BRACES)
{
    // Arrange
    std::vector<std::string> wrong_tokens;
    std::vector<std::string> right_tokens = {"192","168","1","1"};
    ipv4_addr empty_addr(wrong_tokens);
    ipv4_addr right_addr(right_tokens);

    // Act & Asssert
    try {
        unsigned char value = empty_addr[0];
        (void)value;
    } catch (const std::out_of_range& ex) {
        std::string error_msg = ex.what();
        ASSERT_EQ(error_msg, "index out of range");
    }

    ASSERT_EQ(right_addr[0], 192);
    ASSERT_EQ(right_addr[1], 168);
    ASSERT_EQ(right_addr[2], 1);
    ASSERT_EQ(right_addr[3], 1);
    try {
        unsigned char value = right_addr[4];
        (void)value;
    } catch (const std::out_of_range& ex) {
        std::string error_msg = ex.what();
        ASSERT_EQ(error_msg, "index out of range");
    }
}

TEST(IPADDR_CLASS, CONTAINS_METHOD)
{
    // Arrange
    std::vector<std::string> tokens = {"192","168","1","10"};
    ipv4_addr ip_addr(tokens);

    // Act & Assert
    ASSERT_TRUE(ip_addr.contains(192));
    ASSERT_TRUE(ip_addr.contains(168));
    ASSERT_TRUE(ip_addr.contains(1));
    ASSERT_TRUE(ip_addr.contains(10));
    ASSERT_FALSE(ip_addr.contains(75));
}

TEST(IPADDR_CLASS, OPERATOR_LESS)
{
    // Arrange
    std::vector<std::string> tokens_1 = {"192","168","1","10"};
    ipv4_addr ip_addr_1(tokens_1);
    std::vector<std::string> tokens_2 = {"192","168","1","20"};
    ipv4_addr ip_addr_2(tokens_2);

    // Act & Assert
    ASSERT_TRUE(ip_addr_1 < ip_addr_2);
    ASSERT_FALSE(ip_addr_1 < ip_addr_1);
}

TEST(IPADDR_CLASS, OPERATOR_GREATER)
{
    // Arrange
    std::vector<std::string> tokens_1 = {"192","168","1","10"};
    ipv4_addr ip_addr_1(tokens_1);
    std::vector<std::string> tokens_2 = {"192","168","1","20"};
    ipv4_addr ip_addr_2(tokens_2);

    // Act & Assert
    ASSERT_TRUE(ip_addr_2 > ip_addr_1);
    ASSERT_FALSE(ip_addr_1 > ip_addr_1);
}

TEST(IPADDR_CLASS, OPERATOR_EQ)
{
    // Arrange
    std::vector<std::string> tokens_1 = {"192","168","1","10"};
    ipv4_addr ip_addr_1(tokens_1);
    ipv4_addr ip_addr_2(tokens_1);

    // Act & Assert
    ASSERT_TRUE(ip_addr_1 == ip_addr_2);
}

TEST(IPADDR_CLASS, OPERATOR_NOT_EQ)
{
    // Arrange
    std::vector<std::string> tokens_1 = {"192","168","1","10"};
    ipv4_addr ip_addr_1(tokens_1);
    std::vector<std::string> tokens_2 = {"192","168","1","20"};
    ipv4_addr ip_addr_2(tokens_2);

    // Act & Assert
    ASSERT_TRUE(ip_addr_1 != ip_addr_2);
}

TEST(FILTER, SIMPLE_FILTER)
{
    // Arrange
    std::list<ipv4_addr> adresses = {
        ipv4_addr({"1","2","3","4"}),
        ipv4_addr({"5","6","7","8"}),
        ipv4_addr({"9","10","11","12"}),
        ipv4_addr({"13","14","15","16"}),
        ipv4_addr({"17","18","19","20"}),
        ipv4_addr({"21","22","23","24"}),
        ipv4_addr({"25","26","27","28"}),
    };

    // Act
    std::list<ipv4_addr> filtered = filter(adresses, {0, 13});

    // Assert
    ASSERT_EQ(filtered.size(), 1);
    ASSERT_EQ(*filtered.begin(), ipv4_addr({"13","14","15","16"}));
}

TEST(FILTER, AND_FILTER)
{
    // Arrange
    std::list<ipv4_addr> adresses = {
        ipv4_addr({"1","2","3","4"}),
        ipv4_addr({"5","6","7","8"}),
        ipv4_addr({"9","10","11","12"}),
        ipv4_addr({"13","14","15","16"}),
        ipv4_addr({"17","18","19","20"}),
        ipv4_addr({"21","22","23","24"}),
        ipv4_addr({"25","26","27","28"}),
    };

    // Act
    std::list<ipv4_addr> filtered = filter_and(adresses, {{0, 13},{1, 14}});

    // Assert
    ASSERT_EQ(filtered.size(), 1);
    ASSERT_NE(std::find(filtered.begin(), filtered.end(), ipv4_addr({"13","14","15","16"})), filtered.end());
}

TEST(FILTER, OR_FILTER)
{
    // Arrange
    std::list<ipv4_addr> adresses = {
        ipv4_addr({"1","2","3","4"}),
        ipv4_addr({"5","6","7","8"}),
        ipv4_addr({"9","10","11","12"}),
        ipv4_addr({"13","14","15","16"}),
        ipv4_addr({"17","18","19","20"}),
        ipv4_addr({"21","22","23","24"}),
        ipv4_addr({"25","26","27","28"}),
    };

    // Act
    std::list<ipv4_addr> filtered = filter_or(adresses, {{0, 13},{0, 9}});

    // Assert
    ASSERT_EQ(filtered.size(), 2);
    ASSERT_NE(std::find(filtered.begin(), filtered.end(), ipv4_addr({"9","10","11","12"})), filtered.end());
    ASSERT_NE(std::find(filtered.begin(), filtered.end(), ipv4_addr({"13","14","15","16"})), filtered.end());
}

TEST(FILTER, ANY_FILTER)
{
    // Arrange
    std::list<ipv4_addr> adresses = {
        ipv4_addr({"1","2","3","4"}),
        ipv4_addr({"5","6","7","8"}),
        ipv4_addr({"9","10","11","12"}),
        ipv4_addr({"13","14","15","16"}),
        ipv4_addr({"17","18","19","20"}),
        ipv4_addr({"21","22","23","24"}),
        ipv4_addr({"25","26","27","28"}),
        ipv4_addr({"10","20","30","40"}),
    };

    // Act
    std::list<ipv4_addr> filtered = filter_any(adresses, 10);

    // Assert
    ASSERT_EQ(filtered.size(), 2);
    ASSERT_NE(std::find(filtered.begin(), filtered.end(), ipv4_addr({"9","10","11","12"})), filtered.end());
    ASSERT_NE(std::find(filtered.begin(), filtered.end(), ipv4_addr({"10","20","30","40"})), filtered.end());
}




