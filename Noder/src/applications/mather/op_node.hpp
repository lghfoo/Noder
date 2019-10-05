#pragma once
#include"..//..//core/noder/node.hpp"
#include"..//..//core/noder/port.hpp"
#include"data.hpp"
using namespace Noder;
namespace Mather {
	class BinaryOpNode : public Node{
	public:
		BinaryOpNode() {
			this->SetInputPort1(Pointer<InputPort>(new InputPort()));
			this->SetInputPort2(Pointer<InputPort>(new InputPort()));
			this->SetOutputPort(Pointer<OutputPort>(new OutputPort()));
		}
	private:
		//BinaryOpNode(InputPort* const input_port_1 = nullptr, InputPort* const input_port_2 = nullptr, OutputPort* const output_port = nullptr){
		//	this->SetOutputPort(output_port);
		//	this->SetInputPort1(input_port_1);
		//	this->SetInputPort2(input_port_2);
		//}
		void SetInputPort1(const Pointer<InputPort>& input_port) {
			this->input_port_1 = input_port;
			if (input_port_1) {
				input_port_1->AddFlushDataListener([&](Data* data) {
					if (input_port_1->HasData() && input_port_2->HasData() && output_port) {
						this->ProcessData();
					}
				});
			}
		}
		void SetInputPort2(const Pointer<InputPort>& input_port) {
			this->input_port_2 = input_port;
			if (input_port_2) {
				input_port_2->AddFlushDataListener([&](Data* const data) {
					if (input_port_1->HasData() && input_port_2->HasData() && output_port) {
						this->ProcessData();
					}
				});
			}
		}
		void SetOutputPort(const Pointer<OutputPort>& output_port) {
			this->output_port = output_port;
			if (input_port_1->HasData() && input_port_2->HasData() && this->output_port) {
				this->ProcessData();
			}
		}
	protected:
		//InputPort* input_port_1 = nullptr;
		//InputPort* input_port_2 = nullptr;
		//OutputPort* output_port = nullptr;
		Pointer<InputPort> input_port_1;
		Pointer<InputPort> input_port_2;
		Pointer<OutputPort> output_port;
	};

	class UnaryOpNode : public Node {
	public:
		UnaryOpNode(InputPort* const input_port = nullptr, OutputPort* const output_port = nullptr)
			: input_port(input_port), output_port(output_port){

		}

		void SetInputPort(InputPort* const input_port) {
			this->input_port = input_port;
			if (this->input_port) {
				this->input_port->AddFlushDataListener([&](Data* data) {
					if (this->input_port->HasData() && output_port) {
						this->ProcessData();
					}
				});
			}
		}
		void SetOutputPort(OutputPort* const output_port) {
			this->output_port = output_port;
			if (input_port->HasData() && this->output_port) {
				this->ProcessData();
			}
		}
	protected:
		InputPort* input_port = nullptr;
		OutputPort* output_port = nullptr;
	};

	template<class Type1, class Type2, class ResType>
	class AddOpNode : public BinaryOpNode {

	};

	//class PlusOpNode : public UnaryOpNode {
	//	PlusOpNode(InputPort* const input_port = nullptr, OutputPort* const output_port = nullptr)
	//		: UnaryOpNode(input_port, output_port) {

	//	}

	//	virtual void ProcessData()override {
	//		output_port->FlushData(input_port->GetData<NumericData*>());
	//	}
	//};

	

	//class MinusOpNode : public UnaryOpNode {
	//	MinusOpNode(InputPort* const input_port = nullptr, OutputPort* const output_port = nullptr)
	//		: UnaryOpNode(input_port, output_port) {

	//	}

	//	virtual void ProcessData()override {
	//		output_port->FlushData(NumericData::Minus(input_port->GetData<NumericData*>()));
	//	}
	//};

//#define DEFINE_NODE_CLASS(CLASS_NAME, OP)																										\
//	class CLASS_NAME : BinaryOpNode {																											\
//	public:																																		\
//		CLASS_NAME(InputPort* const input_port_1 = nullptr, InputPort* const input_port_2 = nullptr, OutputPort* const output_port = nullptr)	\
//			:BinaryOpNode(input_port_1, input_port_2, output_port) {																			\
//																																				\
//		}																																		\
//		virtual void ProcessData()override {																									\
//			NumericData* lhs = input_port_1->GetData<NumericData*>();																			\
//			NumericData* rhs = input_port_2->GetData<NumericData*>();																			\
//			NumericData* result = NumericData::OP(lhs, rhs);																					\
//			output_port->FlushData(result);																										\
//		}																																		\
//	};
//DEFINE_NODE_CLASS(AddNode, Add)
//DEFINE_NODE_CLASS(SubstractNode, Substract)
//DEFINE_NODE_CLASS(MultiplyNode, Multiply)
//DEFINE_NODE_CLASS(DivideNode, Divide)

	//class AddNode : BinaryOpNode{
	//public:
	//	AddNode(InputPort* const input_port_1 = nullptr, InputPort* const input_port_2 = nullptr, OutputPort* const output_port = nullptr)
	//		:BinaryOpNode(input_port_1, input_port_2, output_port) {

	//	}
	//	virtual void ProcessData()override {
	//		NumericData* lhs = input_port_1->GetData<NumericData*>();
	//		NumericData* rhs = input_port_2->GetData<NumericData*>();
	//		NumericData* result = NumericData::Add(lhs, rhs);
	//		output_port->FlushData(result);
	//	}
	//};

	//class SubstractNode {

	//};

	//class MultiplyNode {

	//};

	//class DivideNode {

	//};
}