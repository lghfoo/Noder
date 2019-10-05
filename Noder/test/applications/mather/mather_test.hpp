#pragma once
#include"op_node_test.hpp"
#include"number_test.hpp"
namespace Mather {
	class MatherTest {
	public:
		static void Run() {
			OpNodeTest::Run();
			NumberTest::Run();
		}
	};
}