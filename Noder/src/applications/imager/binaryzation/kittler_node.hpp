#pragma once
#include"../..//..//core/noder/base_node.hpp"
#include"../data.hpp"
#include<cmath>
namespace Imager {
	class KittlerNode : public Noder::Node_1_1 {
	public:
		KittlerNode(PObject arg = nullptr){}
		virtual void ProcessData()override {
			auto data = input_port->GetData<ImageData>();
			if (!data || data->IsInvalid())return;
			Image* input = data->image;
			output.SetSize(input->width, input->height);
			constexpr int gray_scale = 0x100;
			int hist[gray_scale] = {};
			for (int i = 0; i < input->width; i++) {
				for (int j = 0; j < input->height; j++) {
					hist[input->GetPixel(i, j).GetRed()]++;
				}
			}
			int threshold = -1;
			float min_sigma = 0;
			for (int i = 0; i < gray_scale; i++) {
				int pixel_back = 0, pixel_fore = 0, omega_back = 0, omega_fore = 0;
				for (int j = 0; j <= i; j++) {
					pixel_back += hist[j];
					omega_back += j * hist[j];
				}

				for (int j = i + 1; j < gray_scale; j++) {
					pixel_fore += hist[j];
					omega_fore += j * hist[j];
				}

				if (pixel_back != 0)omega_back /= pixel_back;
				if (pixel_fore != 0) omega_fore /= pixel_fore;
				int sigma_back = 0, sigma_fore = 0;
				for (int j = 0; j <= i; j++) {
					sigma_back += (j - omega_back) * (j - omega_back) * hist[j];
				}
				for (int j = i + 1; j < gray_scale; j++) {
					sigma_fore += (j - omega_fore) * (j - omega_back) * hist[j];
				}

				if (sigma_fore == 0 || sigma_back == 0) {
					if (threshold == -1) {
						threshold = i;
					}
				}
				else {
					float f_sigma_back = std::sqrt(float(sigma_back) / pixel_back);
					float f_sigma_fore = std::sqrt(float(sigma_fore) / pixel_fore);
					float sigma = 1 + 2 * (pixel_back * std::log(f_sigma_back / pixel_back) + pixel_fore * std::log(f_sigma_fore / pixel_fore));
					//float sigma = pixel_back * std::log(f_sigma_back / pixel_back) + pixel_fore * std::log(f_sigma_fore / pixel_fore) - pixel_back * std::log(float(pixel_back)) - pixel_fore * std::log(float(pixel_fore));
					if (i == 0) {
						sigma = min_sigma;
					}
					else {
						if (min_sigma > sigma) {
							min_sigma = sigma;
							threshold = i;
						}
					}
				}
			}
		
			for (int i = 0; i < output.width; i++) {
				for (int j = 0; j < output.height; j++) {
					if (input->GetPixel(i, j).GetRed() < threshold) {
						output.SetPixel(i, j, Pixel(0, 0, 0));
					}
					else {
						output.SetPixel(i, j, Pixel(0xff, 0xff, 0xff));
					}
				}
			}
			output_port->UpdateData(&output);
		}
		Image output;
	};
}