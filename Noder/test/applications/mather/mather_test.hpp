#pragma once
#include"op_node_test.hpp"
#include"number_test.hpp"
#include"value_node_test.hpp"
namespace Mather {
	class MatherTest {
	public:
		static void Run() {
			OpNodeTest::Run();
			ValueNodeTest::Run();
			NumberTest::Run();
		}
	};
}