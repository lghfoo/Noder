#pragma once
#include"..//..//core/noder/node.hpp"
#include"..//..//core/noder/port.hpp"
#include"..//..//core/noder/base_node.hpp"
#include"data.hpp"
using namespace Noder;
namespace Texter {
	class TextNode : public Node_1_1 {
	public:
		void ProcessData() override {
			auto input_text = input_port->GetData<Text>();
			if (input_port) {
				output_port->UpdateData(input_text->GetValue());
			}
		}
	};
}