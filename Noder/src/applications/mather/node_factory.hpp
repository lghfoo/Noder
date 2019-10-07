#pragma once
#include"..//..//core/noder/node.hpp"
#include"..//..//core/noder/port.hpp"
#include"data.hpp"
#include"value_node.hpp"
using namespace Noder;
namespace Mather {
	class NodeFactory{
	public:
		enum NodeType {
			INT64_ADD,
			INT64_VALUE
		};
		static Node* CreateNode(const NodeType& type) {
			Node* ret = nullptr;
			switch (type)
			{
			case INT64_ADD:
				break;
			case INT64_VALUE:
				ret = new ValueNode();
				break;
			default:
				break;
			}
			return ret;
		}
	};
}