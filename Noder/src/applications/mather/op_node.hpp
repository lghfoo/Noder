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

		Pointer<InputPort> GetInputPort1() {
			return input_port_1;
		}

		Pointer<InputPort> GetInputPort2() {
			return input_port_2;
		}

		Pointer<OutputPort> GetOutputPort() {
			return output_port;
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
				input_port_1->AddFlushDataListener(flush_data_listener);
				input_port_1->AddUpdateDataListener(update_data_listener);
			}
		}

		void SetInputPort2(const Pointer<InputPort>& input_port) {
			this->input_port_2 = input_port;
			if (input_port_2) {
				input_port_2->AddFlushDataListener(flush_data_listener);
				input_port_2->AddUpdateDataListener(update_data_listener);
			}
		}
		void SetOutputPort(const Pointer<OutputPort>& output_port) {
			this->output_port = output_port;
			if (this->output_port) {
				this->output_port->AddFlushDataListener(flush_data_listener);
			}
		}

		Port::UpdateDataListener update_data_listener = [&](PObject data) {
			if (this->input_port_1->HasData() && input_port_2->HasData() && output_port) {
				this->ProcessData();
			}
		};
		Port::FlushDataListener flush_data_listener = [&](Data* data) {
			if (this->input_port_1->HasData() && input_port_2->HasData() && output_port) {
				this->ProcessData();
			}
		};
	protected:
		Pointer<InputPort> input_port_1;
		Pointer<InputPort> input_port_2;
		Pointer<OutputPort> output_port;
	};

	class UnaryOpNode : public Node {
	public:
		//UnaryOpNode(InputPort* const input_port = nullptr, OutputPort* const output_port = nullptr)
		//	: input_port(input_port), output_port(output_port){

		//}
		UnaryOpNode() {
			this->SetInputPort(Pointer<InputPort>(new InputPort()));
			this->SetOutputPort(Pointer<OutputPort>(new OutputPort()));
		}
		Pointer<InputPort> GetInputPort() {
			return input_port;
		}
		Pointer<OutputPort> GetOutputPort() {
			return output_port;
		}
	private:
		void SetInputPort(const Pointer<InputPort>& input_port) {
			this->input_port = input_port;
			if (this->input_port) {
				this->input_port->AddFlushDataListener(flush_data_listener);
				this->input_port->AddUpdateDataListener(update_data_listener);
			}
		}
		void SetOutputPort(const Pointer<OutputPort>& output_port) {
			this->output_port = output_port;
			if (this->output_port) {
				this->output_port->AddFlushDataListener(flush_data_listener);
			}
		}
	private:
		Port::UpdateDataListener update_data_listener = [&](PObject data) {
			if (this->input_port->HasData() && output_port) {
				this->ProcessData();
			}
		};
		Port::FlushDataListener flush_data_listener = [&](Data* data) {
			if (this->input_port->HasData() && output_port) {
				this->ProcessData();
			}
		};
	protected:
		Pointer<InputPort> input_port;
		Pointer<OutputPort> output_port;
	};

	template<class Type1, class Type2, class ResType>
	class AddOpNode : public BinaryOpNode {
	public:
		virtual void ProcessData()override {
			auto lhs = input_port_1->GetData<Number<Type1>>();
			auto rhs = input_port_2->GetData<Number<Type2>>();
			if (lhs && rhs) {
				output_port->UpdateData((*lhs + *rhs).GetValue());
			}
		}
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