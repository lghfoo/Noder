#pragma once
#include"..//..//core/noder/data.hpp"
namespace Texter {
	using namespace Noder;
	struct Text : Data {
		std::string value = "";
		virtual void UpdateValueImpl(PObject data)override {
			this->value = *static_cast<string*>(data);
		}

		PObject GetValue() override{
			return &value;
		}
	};
}