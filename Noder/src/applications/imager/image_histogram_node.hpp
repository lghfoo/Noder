#pragma once
#include"..//..//core/noder/base_node.hpp"
#include"../mather/data.hpp"
#include"data.hpp"
namespace Imager {
	class ImageHistogramNode : public Noder::Node_1_1 {
	public:
		ImageHistogramNode(PObject arg = nullptr){}
		void ProcessData()override {
			auto image_data = input_port->GetData<ImageData>();
			if (!image_data || image_data->IsInvalid())return;
			auto src_image = image_data->image;
			if (histogram.size() != 0x100) {
				histogram.resize(0x100);
			}
			std::fill(histogram.begin(), histogram.end(), 0);
			for (int i = 0; i < src_image->width; i++) {
				for (int j = 0; j < src_image->height; j++) {
					auto gray_level = src_image->GetPixel(i, j).GetRed();
					histogram[gray_level]++;
				}
			}
			output_port->UpdateData(&histogram);
		}
	private:
		std::vector<int> histogram;
	};
}