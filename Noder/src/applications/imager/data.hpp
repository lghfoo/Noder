#pragma once
#include"../../core/noder/data.hpp"
namespace Imager {
	using namespace Noder;
	struct Pixel : Data {
		unsigned int color = 0xffffffff;

		Pixel() {
		}

		Pixel(unsigned char red, unsigned char green, unsigned char blue) {
			this->SetRed(red);
			this->SetGreen(green);
			this->SetBlue(blue);
		}

		unsigned char GetRed() {
			return ((unsigned char*)& color)[0];
		}
		
		unsigned char GetGreen() {
			return ((unsigned char*)& color)[1];
		}

		unsigned char GetBlue() {
			return ((unsigned char*)& color)[2];
		}

		unsigned char GetAlpha() {
			return ((unsigned char*)& color)[3];
		}

		void SetRed(unsigned char red) {
			((unsigned char*)& color)[0] = red;
		}

		void SetGreen(unsigned char green) {
			((unsigned char*)& color)[1] = green;
		}

		void SetBlue(unsigned char blue) {
			((unsigned char*)& color)[2] = blue;
		}

		void SetAlpha(unsigned char alpha) {
			((unsigned char*)& color)[3] = alpha;
		}

#define RANGE 255.0f
		float GetRedF() {
			return this->GetRed() / RANGE;
		}
		
		float GetGreenF() {
			return this->GetGreen() / RANGE;
		}

		float GetBlueF() {
			return this->GetBlue() / RANGE;
		}

		float GetAlphaF() {
			return this->GetAlpha() / RANGE;
		}
#undef RANGE
	};

	struct ImageData : Data {
		Pixel** value = nullptr;
		int width = 0;
		int height = 0;

		ImageData() {

		}

		ImageData(int width, int height) {
			this->width = width;
			this->height = height;
			value = new Pixel * [height];
			for (int i = 0; i < height; i++) {
				value[i] = new Pixel[width];
			}
		}

		virtual PObject GetValue()override {
			return &value;
		}

		int GetWidth() {
			return width;
		}

		int GetHeight() {
			return height;
		}

		// Alt+43081 ¨I
		// Alt+43082 ¨J
		// Alt+43083 ¨K
		// Alt+43084 ¨L
		// Alt+41466 ¡ú
		// Alt+41467 ¡û
		// Alt+41468 ¡ü
		// Alt+41469 ¡ý
		// x -> (0, width)
		// y -> (0, height)
		// coord:
		//  ¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡úx
		// Ø­
		// Ø­
		// Ø­
		// Ø­
		// Ø­
		// ¡ý
		// y
		Pixel GetPixel(int x, int y) {
			return value[y][x];
		}

		void SetPixel(int x, int y, const Pixel& pixel) {
			value[y][x] = pixel;
		}

		// bad impl....
		virtual void UpdateValueImpl(PObject data)override {
			ImageData* image_data = static_cast<ImageData*>(data);
			if (this->value) {
				this->ClearData();
			}
			this->width = image_data->width;
			this->height = image_data->height;
			this->value = new Pixel*[height];
			for (int i = 0; i < height; i++) {
				this->value[i] = new Pixel[width];
				memcpy(this->value[i], image_data->value[i], sizeof(Pixel) * width);
			}
		}

		void ClearData() {
			for (int i = 0; i < height; i++) {
				delete value[i];
			}
			delete value;
			this->value = nullptr;
		}
	};
}