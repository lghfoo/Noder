#pragma once
#include"../../core/noder/data.hpp"
namespace Imager {
	using namespace Noder;
	struct Pixel : Data {
		unsigned int color = 0xffffffff;

		Pixel() {
		}

		Pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 0xff) {
			this->SetRed(red);
			this->SetGreen(green);
			this->SetBlue(blue);
			this->SetAlpha(alpha);
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

		Pixel Grayen() {
			unsigned char value = (this->GetRed() + this->GetGreen() + this->GetBlue()) / 3.0f;
			return Pixel(value, value, value);
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

	struct Image {
		Pixel** pixels = nullptr;
		int width = 0;
		int height = 0;
		Image() {

		}
		Image(int width, int height) {
			this->width = width;
			this->height = height;
			pixels = new Pixel * [height];
			for (int i = 0; i < height; i++) {
				pixels[i] = new Pixel[width];
			}
		}

		int GetWidth() {
			return width;
		}

		int GetHeight() {
			return height;
		}

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
			return pixels[y][x];
		}

		void SetPixel(int x, int y, const Pixel& pixel) {
			pixels[y][x] = pixel;
		}

		Image(const Image& image){
			if (image.width <= 0 || image.height <= 0)return;
			if (this->width == image.width && this->height == image.height) {
				for (int i = 0; i < height; i++) {
					memcpy(this->pixels[i], image.pixels[i], sizeof(Pixel) * width);
				}
				return;
			}
			if (this->pixels) {
				this->ClearData();
			}
			this->width = image.width;
			this->height = image.height;
			this->pixels = new Pixel * [height];
			for (int i = 0; i < height; i++) {
				this->pixels[i] = new Pixel[width];
				memcpy(this->pixels[i], image.pixels[i], sizeof(Pixel) * width);
			}
		}

		void ClearData() {
			if (!pixels)return;
			for (int i = 0; i < height; i++) {
				delete pixels[i];
			}
			this->width = this->height = 0;
			delete pixels;
			this->pixels = nullptr;
		}
	};

	struct ImageData : Data {
		//Pointer<Image> image;
		Image* image = nullptr;
		virtual PObject GetValue()override {
			return image;
		}

		virtual void UpdateValueImpl(PObject data)override {
			//this->image = *static_cast<Pointer<Image>*>(data);
			if (data != nullptr) {
				this->image = static_cast<Image*>(data);
			}
		}

		bool IsValid() { return image != nullptr; }

		bool HasPixels() { return image->width > 0 && image->height > 0; }

		//bool IsValid() {
		//	return image != nullptr;
		//}
	};
}

// Alt+43081 ¨I
// Alt+43082 ¨J
// Alt+43083 ¨K
// Alt+43084 ¨L
// Alt+41466 ¡ú
// Alt+41467 ¡û
// Alt+41468 ¡ü
// Alt+41469 ¡ý