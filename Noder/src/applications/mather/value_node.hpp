#pragma once
#include"..//..//core/noder/node.hpp"
#include"..//..//core/noder/port.hpp"
#include"..//..//core/noder/base_node.hpp"
#include"data.hpp"
using namespace Noder;
namespace Mather {
#define UnaryOpNode Node_1_1
    class ValueNode : public UnaryOpNode{
	public:
		ValueNode(PObject arg = nullptr) {}
        virtual void ProcessData()override {
            auto data = input_port->GetData<Data>();
            if (data) {
                output_port->UpdateData(data->GetValue());
            }
        }
    };
	using HistogramNode = ValueNode;
#undef UnaryOpNode
}
