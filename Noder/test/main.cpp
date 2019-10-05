#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include"tester.hpp"
#include<iostream>
#include"../src/core/noder/node.hpp"
#include"../src/applications/mather/op_node.hpp"
#include<algorithm>
using namespace std;
using namespace Mather;
using namespace Test;

int main() {
	Tester::Run();
	//InputPort* input_port_1 = new InputPort();
	//InputPort* input_port_2 = new InputPort();
	//OutputPort* output_port = new OutputPort();
	//AddNode* add_node = new AddNode(input_port_1, input_port_2, output_port);
	//input_port_1->FlushData(new FloatData(80.5f));
	//input_port_2->FlushData(new FloatData(30.997f));
	//FloatData* result = output_port->GetData<FloatData*>();
	//cout << result->GetData() << endl;
}