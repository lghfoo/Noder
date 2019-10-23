#pragma once
#include"..//..//core/noder/base_node.hpp"
#include"..//..//applications/filer/file_node.hpp"
#include"..//..//applications/filer/data.hpp"
namespace Imager {
	using namespace Noder;
	using namespace Filer;
	// image from file
	class FImageNode : public Node_1_1{
	public:
		void ProcessData()override {
			auto filename_text = input_port->GetData<Text>();

		}
	};
}