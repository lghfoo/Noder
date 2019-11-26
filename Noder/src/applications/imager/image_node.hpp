#pragma once
#include"..//..//core/noder/base_node.hpp"
#include"data.hpp"
namespace Imager {
	using namespace Noder;
	// show/pass image
	class ImageNode : public Node_1_1 {
	public:
		ImageNode(PObject arg = nullptr){}
		void ProcessData()override {
			ImageData* input_image = this->input_port->GetData<ImageData>();
			this->output_port->UpdateData(input_image->GetValue());
		}
	};
}