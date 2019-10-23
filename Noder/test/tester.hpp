#pragma once
#include"./applications/mather/mather_test.hpp"
#include"./applications/filer/utility/test_buffer_input_stream.hpp"
#include"./applications/imager/coder/test_ppm_coder.hpp"
using namespace Mather;
using namespace Filer;
namespace Test {
	class Tester {
	public:
		static void Run() {
			//MatherTest::Run();
			ImagerTest::CoderTest::PPMCoderTest::Run();
			//FilerTest::UtilityTest::BufferInputStreamTest::Run();
		}

	};
}