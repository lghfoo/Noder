#pragma once
#include"../../core/noder/data.hpp"
namespace Filer {
	using namespace Noder;
	struct Buffer {
		char* buffer = nullptr;
		int size;
		void Reset(int count = 0) {
			if (buffer) {
				delete buffer;
				buffer = nullptr;
			}
			if (count > 0) {
				size = count;
				buffer = new char[count];
			}
			else {
				size = 0;
			}
		}
		~Buffer(){
			delete buffer;
			buffer = nullptr;
		}
	};
	struct BufferData : Data {
		Buffer* buffer = nullptr;
		virtual PObject GetValue()override {
			return buffer;
		}

		virtual void UpdateValueImpl(PObject data)override {
			//this->image = *static_cast<Pointer<Image>*>(data);
			if (data != nullptr) {
				this->buffer = static_cast<Buffer*>(data);
			}
		}
	};
}