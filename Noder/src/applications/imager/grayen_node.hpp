#pragma once
#include"..//..//core/noder/base_node.hpp"
#include"data.hpp"
namespace Imager {
	using namespace Noder;
	// show/pass image
	class GrayenNode : public Node_1_1 {
	public:
		void ProcessData()override {
			printf("Grayen Process Data\n");
			if (!this->input_port->HasData())return;
			ImageData* input_image = this->input_port->GetData<ImageData>();
			if (!input_image->IsValid() || !input_image->HasPixels())return;
			printf("Grayen Begin...\n");
			auto image = input_image->image;
			target.SetSize(image->width, image->height);
			for (int i = 0; i < image->height; i++) {
				for (int j = 0; j < image->width; j++) {
					target.SetPixel(j, i, image->GetPixel(j, i).Grayen());
				}
			}
			printf("Grayen End\n");
			this->output_port->UpdateData(&target);
			printf("Grayen Updated Data\n");
		}
		Image target;
	};
}