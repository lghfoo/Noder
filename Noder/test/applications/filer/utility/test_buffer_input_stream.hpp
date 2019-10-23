#pragma once
#include<iostream>
#include"..//..//..//..//src/applications/filer/utility/buffer_stream.hpp"
using namespace std;
using namespace Filer;
namespace Test {
	namespace FilerTest {
		namespace UtilityTest {
			namespace BufferInputStreamTest {
				static void TestBufferInputStream() {
					ofstream output_stream;
					output_stream.open("lgh_test", ios::out | ios::binary);
					output_stream << "123 456.0   789 \t 9999.0\n";
					output_stream << "#1732992398423\n";
					int x1 = 123;
					float x2 = 456.0f;
					long long x3 = 789;
					double x4 = 9999.0;
					output_stream.write((char*)&x1, sizeof(x1));
					output_stream.write((char*)&x2, sizeof(x2));
					output_stream.write((char*)&x3, sizeof(x3));
					output_stream.write((char*)&x4, sizeof(x4));
					output_stream.close();

					BufferInputStream stream("lgh_test");
					int x123 = stream.Next<int>(BufferInputStream::Text);
					stream.Skip();
					float x456 = stream.Next<float>(BufferInputStream::Text);
					stream.SkipWhiteSpaces();
					long long x789 = stream.Next<long long>(BufferInputStream::Text);
					stream.Skip();
					char tab = stream.Peek();
					stream.SkipWhiteSpaces();
					double x9999 = stream.Next<double>(BufferInputStream::Text);
					stream.SkipWhiteSpaces();
					if (stream.Peek() == '#') {
						stream.SkipLine();
					}
					cout << x123 << " " << x456 << " " << x789 << tab << x9999 << endl;
					x123 = stream.Next<int>();
					x456 = stream.Next<float>();
					x789 = stream.Next<long long>();
					x9999 = stream.Next<double>();
					cout << x123 << " " << x456 << " " << x789 << tab << x9999;

				}
				static void Run() {
					TestBufferInputStream();
				}
			}
		}
	}
}