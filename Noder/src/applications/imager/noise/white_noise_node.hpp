#pragma once
#include"../..//..//core/noder/base_node.hpp"
#include"../..//..//applications/mather/data.hpp"
#include"../data.hpp"

namespace Imager {
	class WhiteNoiseNode : public Noder::TNode<4, 1> {
	public:
		enum {
			CELLW_INPUT,		// int32_t
			CELLH_INPUT,		// int32_t
			WIDTH_INPUT,		// int32_t
			HEIGHT_INPUT		// int32_t
		};
		enum {
			IMAGE_OUTPUT		// image
		};
		WhiteNoiseNode(PObject arg = nullptr) {
			this->GetInputPort(CELLW_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));
			this->GetInputPort(CELLH_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));
			this->GetInputPort(WIDTH_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));
			this->GetInputPort(HEIGHT_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));

			this->GetOutputPort(IMAGE_OUTPUT)->FlushData(Pointer<Data>(new ImageData));
		}
		virtual void ProcessData()override {
			auto cell_w = this->GetInputPort(CELLW_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			auto cell_h = this->GetInputPort(CELLH_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			auto width = this->GetInputPort(WIDTH_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			auto height = this->GetInputPort(HEIGHT_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			if (cell_w <= 0 || cell_h <= 0 || width <= 0 || height <= 0)return;
			output.SetSize(width, height);
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					Mather::Float3 ratio = Mather::Rand2DTo3D(Mather::Float2{ Mather::Floor(float(i) / float(cell_w)), Mather::Floor(float(j) / float(cell_h)) });
					uint8_t r = (uint8_t)(255.0f * ratio.x);
					uint8_t g = (uint8_t)(255.0f * ratio.y);
					uint8_t b = (uint8_t)(255.0f * ratio.z);
					output.SetPixel(i, j, Pixel(r, g, b));
				}
			}

			this->GetOutputPort(IMAGE_OUTPUT)->UpdateData(&output);
		}
		Image output;
	};
}