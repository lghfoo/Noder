#pragma once
#include"../..//..//core/noder/base_node.hpp"
#include"../..//..//applications/mather/data.hpp"
#include"../data.hpp"

namespace Imager {
	class PerlinNoiseNode : public Noder::TNode<4, 1> {
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
		PerlinNoiseNode(PObject arg = nullptr) {
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
			using Float2 = Mather::Float2;
			output.SetSize(width, height);
			auto EaseIn = [](float x)->float {return x * x; };
			auto EaseOut = [&](float x)->float {return 1 - EaseIn(1 - x); };
			auto EaseInOut = [&](float x)->float {return Mather::Lerp(EaseIn(x), EaseOut(x), x); };
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					float ratio = 1.0f;
					Float2 cur_pos{ float(i) / cell_w, float(j) / cell_h };
					Float2 left_up_cell = Mather::Floor(cur_pos);
					Float2 left_down_cell = left_up_cell + Float2{ 0, 1 };
					Float2 right_down_cell = Mather::Ceil(cur_pos);// left_up_cell + Float2{ 1, 1 };
					Float2 right_up_cell =  left_up_cell + Float2{ 1, 0 };
					
					
					Float2 left_up_noise_inc = Mather::Rand2DTo2D(left_up_cell) * 2 - 1;
					Float2 left_down_noise_inc = Mather::Rand2DTo2D(left_down_cell) * 2 - 1;
					Float2 right_up_noise_inc = Mather::Rand2DTo2D(right_up_cell) * 2 - 1;
					Float2 right_down_noise_inc = Mather::Rand2DTo2D(right_down_cell) * 2 - 1;

					left_up_noise_inc.Normalize();
					left_down_noise_inc.Normalize();
					right_up_noise_inc.Normalize();
					right_down_noise_inc.Normalize();

					auto frac = Mather::Frac(cur_pos);
					float left_up_noise = left_up_noise_inc.Dot(frac);
					float right_up_noise = right_up_noise_inc.Dot(frac + Float2{ -1, 0 });
					float left_down_noise = left_down_noise_inc.Dot(frac + Float2{ 0, -1 });
					float right_down_noise = right_down_noise_inc.Dot(frac + Float2{ -1, -1 });

					float interplator_x = EaseInOut(Mather::Frac(cur_pos).x);
					float interplator_y = EaseInOut(Mather::Frac(cur_pos).y);
					float lerp_up = Mather::Lerp(left_up_noise, right_up_noise, interplator_x);
					float lerp_cur = Mather::Lerp(left_down_noise, right_down_noise, interplator_x);
					float lerp_up_cur = Mather::Lerp(lerp_up, lerp_cur, interplator_y);
					ratio = Mather::Clamp(0.0f, lerp_up_cur + 0.5, 1.0f);
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