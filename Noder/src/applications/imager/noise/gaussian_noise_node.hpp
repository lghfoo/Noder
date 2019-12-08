#pragma once
#include"../..//..//core/noder/base_node.hpp"
#include"../..//..//applications/mather/data.hpp"
#include"../data.hpp"
#include<cmath>
namespace Imager {
	class GaussianNoiseNode : public Noder::TNode<3,1> {
	public:
		enum {
			SAMPLE_NUM_INPUT,	// int32_t
			WIDTH_INPUT,		// int32_t
			HEIGHT_INPUT		// int32_t
		};
		enum {
			IMAGE_OUTPUT		// image
		};
		GaussianNoiseNode(PObject arg = nullptr) {
			this->GetInputPort(SAMPLE_NUM_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));
			this->GetInputPort(WIDTH_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));
			this->GetInputPort(HEIGHT_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));

			this->GetOutputPort(IMAGE_OUTPUT)->FlushData(Pointer<Data>(new ImageData));
		}
		virtual void ProcessData()override {
			
			auto sample_num = this->GetInputPort(SAMPLE_NUM_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			auto width = this->GetInputPort(WIDTH_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			auto height = this->GetInputPort(HEIGHT_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			if (sample_num <= 0 || width <= 0 || height <= 0)return;

			output.SetSize(width, height);
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					int sum = 0;
					for (int k = 0; k < sample_num; k++) {
						sum += (std::rand() % 255);
					}
					uint8_t value = (uint8_t)(((float)(sum)) / ((float)(sample_num)));
					output.SetPixel(i, j, Pixel(value, value, value));
				}
			}

			this->GetOutputPort(IMAGE_OUTPUT)->UpdateData(&output);
		}
		Image output;
	};
}