#pragma once
#include"..//..//core/noder/node.hpp"
#include"..//..//core/noder/port.hpp"
#include"..//..//core/noder/base_node.hpp"
#include"data.hpp"
using namespace Noder;
namespace Mather {
#define BinaryOpNode Node_2_1
#define DECLARE_OP_NODE(op, classname)												\
	template<class Type1, class Type2, class ResType>							  	\
	class classname : public BinaryOpNode {										  	\
	public:																		  	\
		virtual void ProcessData()override {									  	\
			auto lhs = input_port_1->GetData<Number<Type1>>();					  	\
			auto rhs = input_port_2->GetData<Number<Type2>>();					  	\
			if (lhs && rhs) {													  	\
				output_port->UpdateData(( *lhs op *rhs).GetValue());				\
			}																	  	\
		}																		  	\
	};

	DECLARE_OP_NODE(+, AddOpNode)
	DECLARE_OP_NODE(-, SubstractOpNode)
	DECLARE_OP_NODE(*, MultiplyOpNode)
	DECLARE_OP_NODE(/, DivideOpNode)
	DECLARE_OP_NODE(%, ModulusOpNode)
#undef DECLARE_OP_NODE(op, classname)
}