#pragma once
#include"..//..//..//src/applications/mather/data.hpp"
#include<iostream>
using namespace std;
namespace Mather {
	class NumberTest {
	public:
		static void Run() {
			Number<int> a = 10;
			Number<float> b = 15.5f;
			auto c = a + b;
			auto d = 3 + a;
			auto e = b + 10;
			cout << c << " " << d << " " << e << endl;

			Number<int> f = 30;
			cout << a << endl;
			a.UpdateValue(f.GetValue());
			cout << a << endl;
		}

		
	};
}