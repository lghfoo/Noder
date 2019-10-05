#pragma once
#include"utility/utility.hpp"
namespace Noder {
	using PObject = void*;
	class NObject {
	private:

	public:
		virtual String ToString() {
			return String::ToString(reinterpret_cast<unsigned long long>(this));
		}

	};

}