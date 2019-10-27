#pragma once
#include"data.hpp"
#include"value_node.hpp"
#include"op_node.hpp"
using namespace Noder;
namespace Mather {
	class NodeFactory{
	public:
		enum NodeType {
			INT64_ADD,
			INT64_SUBSTRACT,
			INT64_MULTIPLY,
			INT64_DIVIDE,
			INT64_MODULUS,
			INT64_VALUE
		};
		static Node* CreateNode(const NodeType& type) {

#define BIN_OP_CASE(e, classname, type)									\
		case e:															\
			ret = new classname<type, type, type>();					\
			break;

			Node* ret = nullptr;
			switch (type)
			{
			BIN_OP_CASE(INT64_ADD, AddOpNode, long long)
			BIN_OP_CASE(INT64_SUBSTRACT, SubstractOpNode, long long)
			BIN_OP_CASE(INT64_MULTIPLY, MultiplyOpNode, long long)
			BIN_OP_CASE(INT64_DIVIDE, DivideOpNode, long long)
			BIN_OP_CASE(INT64_MODULUS, ModulusOpNode, long long)
			case INT64_VALUE:
				ret = new ValueNode();
				break;
			default:
				break;
                        }
			return ret;
#undef BIN_OP_CASE(e, classname, type)
		}
	};
}
