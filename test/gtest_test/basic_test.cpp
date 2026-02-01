#include "gtest/gtest.h"
#include <vector>
#include <string>
#include <memory>
#include <cstdlib>  // 添加这个头文件来使用 _exit

// 测试 fixture 类，用于设置和清理测试环境
class CalculatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 在每个测试用例之前执行
        numbers.push_back(1);
        numbers.push_back(2);
        numbers.push_back(3);
    }

    void TearDown() override {
        // 在每个测试用例之后执行
        numbers.clear();
    }

    std::vector<int> numbers;
};

// 使用参数化的测试
class ParameterizedTest : public ::testing::TestWithParam<std::pair<int, int>> {
protected:
    void SetUp() override {
        auto param = GetParam();
        input = param.first;
        expected = param.second;
    }

    int input;
    int expected;
};

// 简单值测试
TEST(SimpleTest, EqualityAssertion) {
    int x = 10;
    int y = 10;
    EXPECT_EQ(x, y) << "x and y should be equal";
    
    double a = 1.0;
    double b = 1.0001;
    EXPECT_NEAR(a, b, 0.001) << "a and b should be near";
    
    std::string str1 = "hello";
    std::string str2 = "hello";
    EXPECT_STREQ(str1.c_str(), str2.c_str()) << "strings should be equal";
}

// 测试异常
TEST(ExceptionTest, ExceptionHandling) {
    EXPECT_THROW({
        throw std::runtime_error("Test exception");
    }, std::runtime_error);

    EXPECT_NO_THROW({
        int x = 5;
        x += 10;
    });

    EXPECT_ANY_THROW({
        throw "Simple string exception";
    });
}

// 使用 fixture 的测试
TEST_F(CalculatorTest, VectorOperations) {
    EXPECT_EQ(numbers.size(), 3);
    EXPECT_EQ(numbers[0], 1);
    EXPECT_EQ(numbers[1], 2);
    EXPECT_EQ(numbers[2], 3);

    numbers.push_back(4);
    EXPECT_EQ(numbers.size(), 4);
    EXPECT_EQ(numbers.back(), 4);
}

// 参数化测试
INSTANTIATE_TEST_SUITE_P(
    MathOperations,
    ParameterizedTest,
    ::testing::Values(
        std::make_pair(2, 4),
        std::make_pair(3, 9),
        std::make_pair(4, 16),
        std::make_pair(5, 25)
    )
);

TEST_P(ParameterizedTest, SquareCalculation) {
    int result = input * input;
    EXPECT_EQ(result, expected) << "Square of " << input << " should be " << expected;
}

// 测试类型参数化
template<typename T>
class TypedTest : public ::testing::Test {
public:
    using VectorType = std::vector<T>;
};

using MyTypes = ::testing::Types<int, double, float>;
TYPED_TEST_SUITE(TypedTest, MyTypes);

TYPED_TEST(TypedTest, VectorSize) {
    typename TestFixture::VectorType vec(5);
    EXPECT_EQ(vec.size(), 5);
    
    vec.resize(10);
    EXPECT_EQ(vec.size(), 10);
}

// 死亡测试 (如果程序崩溃则测试失败)
TEST(DeathTest, PointerSafety) {
    // 使用宏来避免编译警告，但仍然演示死亡测试的概念
    EXPECT_EXIT(_exit(1), ::testing::ExitedWithCode(1), "");
}

// 更复杂的测试场景
TEST(AdvancedTest, ComplexAssertions) {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, 42);

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3};
    EXPECT_EQ(v1, v2);

    // 自定义谓词测试
    auto isEven = [](int n) { return n % 2 == 0; };
    EXPECT_PRED1(isEven, 4) << "4 should be even";
    EXPECT_FALSE(isEven(3)) << "3 should not be even";

    // 字符串相关测试 - 修复 HasSubstr 错误
    std::string longStr = "This is a long string for testing";
    EXPECT_TRUE(longStr.find("long") != std::string::npos);
    EXPECT_GT(longStr.length(), 10U);
}

// 重复测试以确保稳定性
TEST(StressTest, RepeatedExecution) {
    static int counter = 0;
    counter++;
    EXPECT_GE(counter, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}