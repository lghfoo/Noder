#pragma once
#include"./applications/mather/mather_test.hpp"
using namespace Mather;
namespace Test {
	class Tester {
	public:
		static void Run() {
			MatherTest::Run();
		}

	};
}