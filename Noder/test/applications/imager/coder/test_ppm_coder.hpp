#pragma once
#include<iostream>
using namespace std;
#include"..//..//..//..//src/applications/imager/coder/ppm_coder.hpp"
namespace Test {
	namespace ImagerTest {
		namespace CoderTest {
			namespace PPMCoderTest {
				using namespace Imager;
				static void TestDecode() {
					const char* filename = "C:\\Users\\35974\\Pictures\\Saved Pictures\\ppm\\»Æ°×ÇúÏßìÅÍ¼.ppm";
					PPMCoder* coder = new PPMCoder;
					auto image_data = coder->Decode(filename);
					delete coder;
				}

				static void TestEncode() {
					const char* filename = "C:\\Users\\35974\\Pictures\\Saved Pictures\\ppm\\»Æ°×ÇúÏßìÅÍ¼.ppm";
					PPMCoder* coder = new PPMCoder;
					auto image_data = coder->Decode(filename);
					const char* dst_file = "C:\\Users\\35974\\Pictures\\Saved Pictures\\ppm\\output_»Æ°×ÇúÏßìÅÍ¼.ppm";
					coder->Encode(image_data, dst_file);
					delete coder;
				}

				static void Run() {
					//TestDecode();
					TestEncode();
				}
			}
		}
	}
}