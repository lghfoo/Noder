#pragma once
#include"..//..//core/noder/data.hpp"
#include<iostream>
using std::ostream;
using namespace Noder;
namespace Mather {
	template<class Type>
	struct Number : public Data{
		Type value;
		Number(const Type& value = 0):value(value){}
		virtual PObject GetValue()override {
			return &value;
		}
		virtual void UpdateValueImpl(PObject data)override {
			this->value = *static_cast<Type*>(data);
		}
	};

#define OVERLOAD_OP_FOR_NUMBER(op)																										   \
	template<class LType, class RType>																									   \
	auto operator ##op## (const Number<LType> lhs, const Number<RType> rhs)->Number<decltype(lhs.value ##op## rhs.value)> {				   \
		return lhs.value ##op## rhs.value;																								   \
	}																																	   \
																																		   \
	template<class LType, class RType>																									   \
	auto operator ##op## (const LType& lhs, const Number<RType> rhs) -> Number<decltype(lhs ##op## rhs.value)> {						   \
		return lhs ##op## rhs.value;																									   \
	}																																	   \
																																		   \
	template<class LType, class RType>																									   \
	auto operator ##op## (const Number<LType>& lhs, RType rhs) -> Number<decltype(lhs.value ##op## rhs)> {								   \
		return lhs.value ##op## rhs;																									   \
	}
	
	OVERLOAD_OP_FOR_NUMBER(+)
	OVERLOAD_OP_FOR_NUMBER(-)
	OVERLOAD_OP_FOR_NUMBER(*)
#undef OVERLOAD_OP_FOR_NUMBER(op)

#define OVERLOAD_OP_FOR_NUMBER_ZERO_CHECK(op)																							   \
	template<class LType, class RType>																									   \
	auto operator ##op## (const Number<LType> lhs, const Number<RType> rhs)->Number<decltype(lhs.value ##op## rhs.value)> {				   \
		if(rhs.value==0){																												   \
			return lhs.value;																											   \
		}																																   \
		return lhs.value ##op## rhs.value;																								   \
	}																																	   \
																																		   \
	template<class LType, class RType>																									   \
	auto operator ##op## (const LType& lhs, const Number<RType> rhs) -> Number<decltype(lhs ##op## rhs.value)> {						   \
		if (rhs.value == 0) {																											   \
			return lhs;																													   \
		}																																   \
		return lhs ##op## rhs.value;																									   \
	}																																	   \
																																		   \
	template<class LType, class RType>																									   \
	auto operator ##op## (const Number<LType>& lhs, RType rhs) -> Number<decltype(lhs.value ##op## rhs)> {								   \
		if (rhs == 0) {																													   \
			return lhs.value;																											   \
		}																																   \
		return lhs.value ##op## rhs;																									   \
	}

	OVERLOAD_OP_FOR_NUMBER_ZERO_CHECK(/)
	OVERLOAD_OP_FOR_NUMBER_ZERO_CHECK(%)
#undef OVERLOAD_OP_FOR_NUMBER_ZERO_CHECK(op)
}