#pragma once
#include"../..//..//core/noder/base_node.hpp"
#include"../..//..//applications/mather/data.hpp"
#include"../data.hpp"

namespace Imager {
	class ValueNoiseNode : public Noder::TNode<4, 1> {
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
		ValueNoiseNode(PObject arg = nullptr) {
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
			auto EaseIn = [](float x)->float {return x * x; };
			auto EaseOut = [&](float x)->float {return 1 - EaseIn(1-x); };
			auto EaseInOut = [&](float x)->float {return Mather::Lerp(EaseIn(x), EaseOut(x), x); };
			using Float2 = Mather::Float2;
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					float ratio = 1.0f;
					Float2 cur_pos{ float(i) / cell_w, float(j) / cell_h };
					Float2 cur_cell = Mather::Floor(cur_pos);
					Float2 left_up_cell = cur_cell + Float2{-1, -1};
					Float2 left_cell = cur_cell + Float2{ -1, 0 };
					Float2 up_cell = cur_cell + Float2{ 0, -1 };
					float left_up_noise = Mather::Rand2DTo1D(left_up_cell);
					float left_noise = Mather::Rand2DTo1D(left_cell);
					float up_noise = Mather::Rand2DTo1D(up_cell);
					float cur_noise = Mather::Rand2DTo1D(cur_cell);
					float interplator_x = EaseInOut(Mather::Frac(cur_pos).x);
					float interplator_y = EaseInOut(Mather::Frac(cur_pos).y);
					float lerp_up = Mather::Lerp(left_up_noise, up_noise, interplator_x);
					float lerp_cur = Mather::Lerp(left_noise, cur_noise, interplator_x);
					float lerp_up_cur = Mather::Lerp(lerp_up, lerp_cur, interplator_y);
					ratio = lerp_up_cur;
					uint8_t value = (uint8_t)(255.0f * ratio);
					output.SetPixel(i, j, Pixel(value, value, value));
				}
			}

			this->GetOutputPort(IMAGE_OUTPUT)->UpdateData(&output);
		}
		Image output;
	};

	//auto EaseIn = [](float x)->float {return x * x; };
	//auto EaseOut = [&](float x)->float {return 1 - EaseIn(1 - x); };
	//auto EaseInOut = [&](float x)->float {return Mather::Lerp(EaseIn(x), EaseOut(x), x); };
	//for (int i = 0; i < width; i++) {
	//	for (int j = 0; j < height; j++) {
	//		float ratio = 1.0f;
	//		float PreviousNoise = Mather::Rand1DTo1D(Mather::Floor(float(i) / float(cell_w))) * 32 + 250;
	//		float NextNoise = Mather::Rand1DTo1D(Mather::Ceil(float(i) / float(cell_w))) * 32 + 250;
	//		float Noise = Mather::Lerp(PreviousNoise, NextNoise, EaseInOut(Mather::Frac(float(i) / float(cell_w))));
	//		float Dist = Mather::Abs(float(j) - Noise);
	//		float FWidth = 2.0f;
	//		ratio *= Mather::SmoothStep(0, FWidth, Dist);
	//		uint8_t value = (uint8_t)(255.0f * ratio);
	//		output.SetPixel(i, j, Pixel(value, value, value));
	//	}
	//}
}