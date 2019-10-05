#pragma once
#include"add_node_test.hpp"
#include"substract_node_test.hpp"
#include"multiply_node_test.hpp"
#include"divide_node_test.hpp"
#include"minus_node_test.hpp"
#include"plus_node_test.hpp"
namespace Mather {
	class OpNodeTest {
	public:
		static void Run() {
			AddNodeTest::Run();
			SubstractNodeTest::Run();
			MultiplyNodeTest::Run();
			DivideNodeTest::Run();
			MinusNodeTest::Run();
			PlusNodeTest::Run();
		}
	};
}