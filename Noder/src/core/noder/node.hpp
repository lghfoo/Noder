#pragma once
#include<string>
#include"..//object.hpp"
using std::string;
using std::to_string;
namespace Noder {
	class Node : public NObject{
	private:

	public:
		virtual void ProcessData() {}
	};
}