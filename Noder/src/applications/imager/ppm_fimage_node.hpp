#pragma once
#include"..//..//core/noder/base_node.hpp"
#include"..//..//applications/filer/file_node.hpp"
#include"..//..//applications/filer/data.hpp"
#include"coder/ppm_coder.hpp"
namespace Imager {
	using namespace Noder;
	using namespace Filer;
	// image from file
	class PPMFImageNode : public Node_1_1{
	public:
		void ProcessData()override {
			auto filename_text = input_port->GetData<Text>();
			if (!filename_text->IsEmpty()) {
				PPMCoder coder;
				Image* image = coder.Decode(filename_text->value.c_str()); 
				last_result = Pointer<Image>(image);
				output_port->UpdateData(image);
			}
		}
	private:
		Pointer<Image> last_result;
	};
}