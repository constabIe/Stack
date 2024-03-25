#include <string>
#include <stdexcept>

#include "../include/stack.hpp"
#include "../include/utils.hpp"
#include "../googletest/googletest/include/gtest/gtest.h"

using namespace stack;

TEST(Rule_of_five, default_constructor) 
{
	EXPECT_NO_THROW(Stack<std::string> stack_1 {});
}

TEST(Rule_of_five, non_default_constructor) 
{
	EXPECT_NO_THROW(Stack<std::string> stack_1 {3});
}

TEST(Rule_of_five, copy_constructor) 
{
	Stack<std::string> stack_1 {};

	EXPECT_NO_THROW(Stack<std::string> stack_2 {stack_1});
}

TEST(Rule_of_five, move_constructor) 
{
	EXPECT_NO_THROW(Stack<std::string> stack_2 { Stack<std::string> {1} });
}

TEST(Rule_of_five, destructor) 
{
	Stack<std::string> stack_1 {};

	EXPECT_NO_THROW(stack_1.~Stack());
}


TEST(Rule_of_five, copy_assignment) 
{
	Stack<std::string> stack_1 {};
	Stack<std::string> stack_2 {};

	EXPECT_NO_THROW(stack_2 = stack_1);
}

TEST(Rule_of_five, move_assignment) 
{
	Stack<std::string> stack_1 {};

	EXPECT_NO_THROW(stack_1 = Stack<std::string> {1});
}


TEST(Elements_access, top) 
{
	Stack<std::string> stack_1 {1};
	stack_1.push(std::string { "23" });

	EXPECT_EQ(stack_1.top(), std::string { "23" });
}


TEST(Capacity, empty) 
{
	Stack<std::string> stack_1 {};

	EXPECT_FALSE(stack_1.empty());
}

TEST(Capacity, size) 
{
	Stack<std::string> stack_1 {23};

	EXPECT_EQ(stack_1.size(), (size_t) 23);
}

TEST(Modifiers, push_copy) 
{
	Stack<std::string> stack_1 {};
	std::string str { "slaaaay" };

	EXPECT_NO_THROW(stack_1.push(str));
}

TEST(Modifiers, push_move) 
{
	Stack<std::string> stack_1 {};

	EXPECT_NO_THROW(stack_1.push(std::string { "slaaaay" }));

}

TEST(Modifiers, emplace_copy) 
{
	Stack<std::string> stack_1 {};
	std::string str { "slaaaay" };

	EXPECT_NO_THROW(stack_1.emplace(str));
	EXPECT_EQ(stack_1.top(), str);
}

TEST(Modifiers, emplace_move) 
{
	Stack<std::string> stack_1 {};

	EXPECT_NO_THROW(stack_1.emplace(std::string { "slaaaay" }));
	EXPECT_EQ(stack_1.top(), std::string { "slaaaay" });
}

TEST(Modifiers, pop) 
{
	Stack<std::string> stack_1 {2};
	stack_1.pop();

	EXPECT_TRUE(stack_1.size() == (size_t) 1);
}

TEST(Modifiers, swap)
{
	Stack<int> stack_1 {2};
	Stack<int> stack_2 {1};

	stack_1.push(2);
	stack_2.push(3);


	EXPECT_NO_THROW(swap(stack_1, stack_2));

	EXPECT_TRUE(stack_1.top() == 3);
	EXPECT_TRUE(stack_2.top() == 2);

	EXPECT_TRUE(stack_1.size() == 1);
	EXPECT_TRUE(stack_2.size() == 2);
}





