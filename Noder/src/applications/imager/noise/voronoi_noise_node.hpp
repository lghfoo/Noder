#pragma once
#include"../..//..//core/noder/base_node.hpp"
#include"../..//..//applications/mather/data.hpp"
#include"../data.hpp"
#include<cmath>

namespace Imager {
	class VoronoiNoiseNode : public Noder::TNode<5, 1> {
	public:
		enum {
			CELLW_INPUT,		// int32_t
			CELLH_INPUT,		// int32_t
			ORDER_INPUT,		// int32_t
			WIDTH_INPUT,		// int32_t
			HEIGHT_INPUT		// int32_t
		};
		enum {
			IMAGE_OUTPUT		// image
		};
		VoronoiNoiseNode(PObject arg = nullptr) {
			this->GetInputPort(CELLW_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));
			this->GetInputPort(CELLH_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));
			this->GetInputPort(ORDER_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));
			this->GetInputPort(WIDTH_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));
			this->GetInputPort(HEIGHT_INPUT)->FlushData(Pointer<Data>(new Mather::Number<int32_t>));

			this->GetOutputPort(IMAGE_OUTPUT)->FlushData(Pointer<Data>(new ImageData));
		}
		virtual void ProcessData()override {
			auto cell_w = this->GetInputPort(CELLW_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			auto cell_h = this->GetInputPort(CELLH_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			auto order = this->GetInputPort(ORDER_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			auto width = this->GetInputPort(WIDTH_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			auto height = this->GetInputPort(HEIGHT_INPUT)->GetData<Mather::Number<int32_t>>()->value;
			if (cell_w <= 0 || cell_h <= 0 || width <= 0 || height <= 0 || order < 0)return;
			int min_i = -1, max_i = 1, min_j = -1, max_j = 1;
			if (cell_w <= cell_h) {
				min_j = -1;
				max_j = 1;
				int count = (int)std::ceilf((cell_h - cell_w) / (cell_w));
				min_i = min_j - count;
				max_i = max_j + count;
			}
			else {
				min_i = -1;
				max_i = 1;
				int count = (int)std::ceilf((cell_w - cell_h) / (cell_h));
				min_j = min_i - count;
				max_j = max_i + count;
			}
			int sample_num = (max_i - min_i + 1) * (max_j - min_j + 1);
			if (order >= sample_num)return;
			output.SetSize(width, height);
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					float ratio = VoronoiVoise(float(i), float(j), cell_w, cell_h, order,
						min_i, max_i, min_j, max_j, sample_num);
					ratio = std::min(1.0f, std::max(ratio, 0.0f));
					uint8_t value = (uint8_t)(255.0f * ratio);
					
					output.SetPixel(i, j, Pixel(value, value, value));
				}
			}

			this->GetOutputPort(IMAGE_OUTPUT)->UpdateData(&output);
		}
		Image output;
	private:
		float VoronoiVoise(float x, float y, float cell_w, float cell_h, float order, 
			int min_i, int max_i, int min_j, int max_j, int sample_num) {
			std::vector<float>samples(sample_num);
			float cell_index_x = x / cell_w;
			float cell_index_y = y / cell_h;
			float max_dist = std::hypotf(float(cell_w), float(cell_h));
			auto rand2d_to_1d = [](float x, float y, float dot_x, float dot_y) -> float {
				float small_x = std::sin(x);
				float small_y = std::sin(y);
				float random = dot_x * small_x + dot_y * small_y;
				return random - std::floor(random);
			};
			auto rand2d_to_2d = [&](float x, float y, float& ret_x, float& ret_y) {
				ret_x = rand2d_to_1d(x, y, 12.989f, 78.233f);
				ret_y = rand2d_to_1d(x, y, 39.346f, 11.135f);
			};
			float base_cell_x = std::floorf(cell_index_x);
			float base_cell_y = std::floorf(cell_index_y);
			//float min_dist = max_dist * 3;
			
			int count = 0;
			for (int i = min_i; i <= max_i; i++) {
				for (int j = min_j; j <= max_j; j++) {
					float cell_x = (base_cell_x + i) * cell_w;
					float cell_y = (base_cell_y + j) * cell_h;
					float cell_random_x = 0, cell_random_y = 0;
					rand2d_to_2d(cell_x, cell_y, cell_random_x, cell_random_y);
					float cell_pos_x = cell_x + cell_random_x * cell_w;
					float cell_pos_y = cell_y + cell_random_y * cell_h;
					// distance between CURRENT PIXEL and THE RANDOM POINT IN CELL[I, J]
					float dist = std::hypotf(x - cell_pos_x, y - cell_pos_y);
					samples[count++] = dist;
					//if (dist < min_dist) {
					//	min_dist = dist;
					//}
				}
			}
			std::sort(samples.begin(), samples.end());
			return samples[order] / max_dist;
		}
		//float VoronoiVoise(float x, float y, float cell_w, float cell_h) {
		//	x /= cell_w;
		//	y /= cell_h;
		//	float max_dist = std::hypotf(float(cell_w), float(cell_h));
		//	auto rand2d_to_1d = [](float x, float y, float dot_x, float dot_y) -> float {
		//		float small_x = std::sin(x);
		//		float small_y = std::sin(y);
		//		float random = dot_x * small_x + dot_y * small_y;
		//		return random - std::floor(random);
		//	};
		//	auto rand2d_to_2d = [&](float x, float y, float& ret_x, float& ret_y) {
		//		ret_x = rand2d_to_1d(x, y, 12.989f, 78.233f);
		//		ret_y = rand2d_to_1d(x, y, 39.346f, 11.135f);
		//	};
		//	float base_cell_x = std::floorf(x);
		//	float base_cell_y = std::floorf(y);
		//	float min_dist = 99999.0f;
		//	for (int i = -1; i <= 1; i++) {
		//		for (int j = -1; j <= 1; j++) {
		//			float cell_x = base_cell_x + i;
		//			float cell_y = base_cell_y + j;
		//			float cell_random_x = 0, cell_random_y = 0;
		//			rand2d_to_2d(cell_x, cell_y, cell_random_x, cell_random_y);
		//			float cell_pos_x = cell_x + cell_random_x;
		//			float cell_pos_y = cell_y + cell_random_y;
		//			float dist = std::hypotf(float(x) - cell_pos_x, float(y) - cell_pos_y);
		//			if (dist < min_dist) {
		//				min_dist = dist;
		//			}
		//		}
		//	}
		//	return min_dist;
		//}
	};
}