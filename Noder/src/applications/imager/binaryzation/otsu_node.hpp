#pragma once
#include"../..//..//core/noder/base_node.hpp"
#include"../data.hpp"
namespace Imager {
	class OTSUNode : public Noder::Node_1_1 {
	public:
		OTSUNode(PObject arg = nullptr) {}
		virtual void ProcessData() override {
			auto image_data = input_port->GetData<ImageData>();
			if (!image_data || image_data->IsInvalid())return;
			auto src_image = image_data->image;
			image.SetSize(src_image->width, src_image->height);
			int WH = src_image->width * src_image->height;
			constexpr int gray_scale = 0x100;
			int hist[gray_scale] = {};
			for (int i = 0; i < src_image->width; i++) {
				for (int j = 0; j < src_image->height; j++) {
					auto gray_level = src_image->GetPixel(i, j).GetRed();
					hist[gray_level]++;
				}
			}

			float p_hist[gray_scale] = {};
			for (int i = 0; i < gray_scale; i++) {
				p_hist[i] = float(hist[i]) / WH;
			}
			
			float max_ob = 0;
			byte threshold = 0;
			for (int i = 0; i < gray_scale; i++) {
				float m0 = 0, m1 = 0, r0 = 0, r1 = 0;
				for (int j = 0; j <= i; j++) {
					m0 += p_hist[j] * j;
					r0 += p_hist[j];
				}

				for (int j = i + 1; j < gray_scale; j++) {
					m1 += p_hist[j] * j;
					r1 += p_hist[j];
				}
				if (r0 == 0 || r1 == 0)continue;
				m0 /= r0;
				m1 /= r1;
				float ob = r0 * r1 * ((m0 - m1) * (m0 - m1));
				//printf("i: %d\tm0: %f\tm1: %f\tr0: %f\tr1: %f\tob: %f\n", i, m0, m1, r0, r1, ob);
				if (i == 0)max_ob = ob;
				else {
					if (max_ob < ob) {
						max_ob = ob;
						threshold = i;
					}
				}
			}
			printf("threshold: %d\n", threshold);
			for (int i = 0; i < src_image->width; i++) {
				for (int j = 0; j < src_image->height; j++) {
					if (src_image->GetPixel(i, j).GetRed() < threshold) {
						image.SetPixel(i, j, Pixel(0, 0, 0));
					}
					else {
						image.SetPixel(i, j, Pixel(0xff, 0xff, 0xff));
					}
				}
			}
			output_port->UpdateData(&image);
		}

		Image image;
	};
}