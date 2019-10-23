#pragma once
#include<iostream>
#include"../..//filer/utility/buffer_stream.hpp"
#include"../data.hpp"
using namespace std;
namespace Imager {
	class PPMCoder {
	public:
		ImageData* Decode(const char* src_filename) {
			cout << "Decoding...." << endl;
			ImageData* ret = nullptr;
			BufferInputStream stream(src_filename);
			if (!stream.StateInvalid()) {
				char magic_number[3] = {};
				stream.NextChars(magic_number);
				int width = stream.Next<int>(BufferInputStream::Text);
				int height = stream.Next<int>(BufferInputStream::Text);
				int max_value = stream.Next<int>(BufferInputStream::Text);
				stream.SkipWhiteSpaces();
				if (strcmp(magic_number, "P6") == 0) {
					ret = new ImageData(width, height);
					for (int i = 0; i < height; i++) {
						for (int j = 0; j < width; j++) {
							if (max_value < 256) {
								auto red = stream.NextByte();
								auto green = stream.NextByte();
								auto blue = stream.NextByte();
								ret->SetPixel(j, i, Pixel(red, green, blue));
							}
							else {
								continue;
							}
						}
					}
				}
			}
			return ret;
		}

		void Encode(ImageData* image_data, const char* dst_filename) {
			cout << "Encoding...." << endl;
			ofstream dst_file(dst_filename, ios::binary | ios::out);
			if (dst_file) {
				dst_file << "P6\n";
				dst_file << std::to_string(image_data->width);
				dst_file << " ";
				dst_file << std::to_string(image_data->height);
				dst_file << "\n";
				dst_file << "255";
				dst_file << "\n";
				for (int i = 0; i < image_data->height; i++) {
					for (int j = 0; j < image_data->width; j++) {
						Pixel pixel = image_data->GetPixel(j, i);
						auto r = pixel.GetRed();
						auto g = pixel.GetGreen();
						auto b = pixel.GetBlue();
						dst_file.write((char*)& r, sizeof(unsigned char));
						dst_file.write((char*)& g, sizeof(unsigned char));
						dst_file.write((char*)& b, sizeof(unsigned char));
					}
				}
				dst_file.close();
			}
		}
	};
}