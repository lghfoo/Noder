#pragma once
#include"..//..//..//src/applications/mather/value_node.hpp"
#include<iostream>
using namespace std;
namespace Mather {
	class ValueNodeTest {
	public:
		static void Run() {
			ValueNode node;
			auto input_port = node.GetInputPort();
			auto output_port = node.GetOutputPort();
			// HasData: false

			cout << output_port->HasData() << endl;//0

			input_port->FlushData(new Number<int>(30));

			cout << output_port->HasData() << endl;// 0

			output_port->FlushData(new Number<int>());

			cout << output_port->HasData() << endl; // 1

			cout << output_port->GetData<Number<int>>()->value << endl; // 30

			int x = 17;
			input_port->UpdateData(&x);

			cout << output_port->GetData<Number<int>>()->value << endl; // 17

			x = 38;
			input_port->UpdateData(&x);
			cout << output_port->GetData<Number<int>>()->value << endl; // 38;
		}
	};
}