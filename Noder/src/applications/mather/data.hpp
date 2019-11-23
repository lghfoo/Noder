#pragma once
#include"..//..//core/noder/data.hpp"
#include<iostream>
using std::ostream;
using namespace Noder;
namespace Mather {
	enum NumberType{
		UINT8, INT8,
		UINT16, INT16,
		UINT32, INT32,
		UINT64, INT64,
		FLOAT32,
		FLOAT64
	};
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
		virtual String ToString()override {
			return String::ToString(value);
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

	template<typename Type>
	struct VectorData : Data{
		std::vector<Type>* data = nullptr;
		VectorData() {

		}
		VectorData(int size) {
			data = new std::vector<Type>(size);
		}
		virtual PObject GetValue()override {
			return data;
		}
		virtual void UpdateValueImpl(PObject data)override {
			this->data = static_cast<vector<Type>*>(data);
		}

		void SetSize(int size) {
			if (!data) {
				data = new std::vector<Type>(size);
			}
			else {
				data->resize(size);
			}
		}

		Type Get(int i) {
			return (*data)[i];
		}

		void Set(int i, const Type& value) {
			(*data)[i] = value;
		}

		Type& operator[](int i) {
			return (*data)[i];
		}

		int Size() {
			return data->size();
		}

		~VectorData() {
			if (data) {
				delete data;
			}
		}
	};
}