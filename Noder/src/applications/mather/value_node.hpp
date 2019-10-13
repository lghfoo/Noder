#pragma once
#include"..//..//core/noder/node.hpp"
#include"..//..//core/noder/port.hpp"
#include"data.hpp"
#include"op_node.hpp"
using namespace Noder;
namespace Mather {
    class ValueNode : public UnaryOpNode{
	public:
        virtual void ProcessData()override {
            auto data = input_port->GetData<Data>();
            if (data) {
                output_port->UpdateData(data->GetValue());
            }
        }
    };
}
