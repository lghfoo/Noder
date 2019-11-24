#pragma once
#include"..//..//core/noder/node.hpp"
#include"..//..//core/noder/port.hpp"
#include"..//..//core/noder/base_node.hpp"
#include"data.hpp"
using namespace Noder;
namespace Texter {
	class ToStringNode : public TNode<1, 1> {
	public:
		enum {
			DATA_INPUT
		};
		enum {
			STRING_OUTPUT
		};
		ToStringNode() {
			this->GetInputPort(DATA_INPUT)->FlushData(new Data);
			this->GetOutputPort(STRING_OUTPUT)->FlushData(new Text);
		}
		virtual void ProcessData() override {
			auto data_input = this->GetInputPort(DATA_INPUT)->GetData<Data>();
			this->GetOutputPort(STRING_OUTPUT)->UpdateData(&(data_input->ToString().ToStdString()));
		}
	};
}