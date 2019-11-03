#pragma once
#include"../..//..//core/noder/base_node.hpp"
#include"../../mather/data.hpp"
#include"../data.hpp"
namespace Imager {
	class BernsenNode : public Noder::Node_2_1 {
	public:
		virtual void ProcessData() override {
			auto image_data = input_port_1->GetData<ImageData>();
			auto window_size = (int)(input_port_2->GetData<Mather::Number<long long>>()->value);
			if (!image_data || image_data->IsInvalid() || window_size <= 0)return;
			auto src_image = image_data->image;
			image.SetSize(src_image->width, src_image->height);
			int WH = src_image->width * src_image->height;
			constexpr int gray_scale = 0x100;
			for (int i = 0; i < src_image->height; i++) {
				for (int j = 0; j < src_image->width; j++) {
					int max_gray = 0, min_gray = gray_scale;
					for (int s_i = i - window_size; s_i < i + window_size; s_i++) {
						for (int s_j = j - window_size; s_j < j + window_size; s_j++) {
							int cur_gray = 0;
							if (s_i < 0 || s_i >= src_image->height || s_j < 0 || s_j >= src_image->width) {
								cur_gray = 0;
							}
							else {
								cur_gray = src_image->GetPixel(s_j, s_i).GetRed();
							}
							if (max_gray < cur_gray)max_gray = cur_gray;
							if (min_gray > cur_gray)min_gray = cur_gray;
						}
					}
					byte threshold = (max_gray + min_gray) / 2;
					if (src_image->GetPixel(j, i).GetRed() < threshold) {
						image.SetPixel(j, i, Pixel(0, 0, 0));
					}
					else {
						image.SetPixel(j, i, Pixel(0xff, 0xff, 0xff));
					}
				}
			}

			output_port->UpdateData(&image);
		}

		Image image;
	};
}