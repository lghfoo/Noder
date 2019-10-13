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
	//template<class T>
	//ostream& operator<<(ostream& out, const Number<T> number) {
	//	out << number.value;
	//	return out;
	//}
	//struct Int8 {
	//	char value;
	//	Int8(char value = 0):value(value){}
	//};
	//struct Int16 {
	//	short value;
	//	Int16(short value = 0):value(value){}
	//};
	//struct Int32 {
	//	int value;
	//	Int32(int value = 0):value(value){}
	//};
	//struct Int64 {
	//	long long value;
	//	Int64(long long value = 0):value(value){}
	//};
	//struct Float32 {
	//	float value;
	//	Float32(float value = 0):value(value){}
	//};
	//struct Float64 {
	//	double value;
	//	Float64(double value = 0):value(value){}
	//};
	

	

	//class NumericData : public Data {
	//public:
	//	virtual NumericData* Add(NumericData* const data) { return nullptr; }
	//	virtual NumericData* Substract(NumericData* const data) { return nullptr; }
	//	virtual NumericData* Multiply(NumericData* const data) { return nullptr; }
	//	virtual NumericData* Divide(NumericData* const data) { return nullptr; }
	//	virtual NumericData* Minus() { return nullptr; }
	//	static NumericData* Add(NumericData* lhs, NumericData* rhs) { return lhs->Add(rhs); }
	//	static NumericData* Substract(NumericData* lhs, NumericData* rhs) { return lhs->Substract(rhs); }
	//	static NumericData* Multiply(NumericData* lhs, NumericData* rhs) { return lhs->Multiply(rhs); }
	//	static NumericData* Divide(NumericData* lhs, NumericData* rhs) { return lhs->Divide(rhs); }
	//	static NumericData* Minus(NumericData* opn) { return opn->Minus(); }
	//};
//#define DEFINE_DATA_CLASS(CLASS_NAME, DATA_TYPE)												\
//	class CLASS_NAME : public NumericData {														\
//	private:																					\
//		DATA_TYPE data;																			\
//	public:																						\
//		CLASS_NAME(DATA_TYPE data) :data(data) {}											\
//		DATA_TYPE GetData() {																	\
//			return data;																		\
//		}																						\
//		virtual NumericData* Add(NumericData* const data) override {							\
//			return new CLASS_NAME(this->data->data + dynamic_cast<CLASS_NAME*>(data->data)->GetData());		\
//		}																						\
//		virtual NumericData* Substract(NumericData* const data) override {						\
//			return new CLASS_NAME(this->data->data - dynamic_cast<CLASS_NAME*>(data->data)->GetData());		\
//		}																						\
//		virtual NumericData* Multiply(NumericData* const data) override {						\
//			return new CLASS_NAME(this->data->data * dynamic_cast<CLASS_NAME*>(data->data)->GetData());		\
//		}																						\
//		virtual NumericData* Divide(NumericData* const data)override {							\
//			return new CLASS_NAME(this->data->data / dynamic_cast<CLASS_NAME*>(data->data)->GetData());		\
//		}																						\
//		virtual NumericData* Minus() {															\
//			return new CLASS_NAME(-data->data);														\
//		}																						\
//	};
//DEFINE_DATA_CLASS(FloatData, Float32)
//DEFINE_DATA_CLASS(DoubleData, Float64)
//DEFINE_DATA_CLASS(Int32Data, Int32)
//DEFINE_DATA_CLASS(Int64Data, Int64)





	//class Int32Data : public NumericData {
	//private:
	//	int data;
	//public:
	//	Int32Data(int data = 0):data(data){}
	//	int GetData(){
	//		return data;
	//	}
	//	virtual NumericData* Add(NumericData* const data) override{
	//		return new Int32Data(this->data + dynamic_cast<Int32Data*>(data)->GetData());
	//	}
	//	virtual NumericData* Substract(NumericData* const data) override {
	//		return new Int32Data(this->data - dynamic_cast<Int32Data*>(data)->GetData());
	//	}
	//	virtual NumericData* Multiply(NumericData* const data) override {
	//		return new Int32Data(this->data * dynamic_cast<Int32Data*>(data)->GetData());
	//	}
	//	virtual NumericData* Divide(NumericData* const data)override {
	//		return new Int32Data(this->data / dynamic_cast<Int32Data*>(data)->GetData());
	//	}
	//	virtual NumericData* Minus() { 
	//		return new Int32Data(-data);
	//	}
	//};

	//class Int64Data : public NumericData {
	//private:
	//	long long data;
	//public:
	//	Int64Data(long long data = 0) :data(data) {}
	//	long long GetData() {
	//		return data;
	//	}
	//	virtual NumericData* Add(NumericData* const data) override {
	//		return new Int64Data(this->data + dynamic_cast<Int64Data*>(data)->GetData());
	//	}
	//	virtual NumericData* Substract(NumericData* const data) override {
	//		return new Int64Data(this->data - dynamic_cast<Int64Data*>(data)->GetData());
	//	}
	//	virtual NumericData* Multiply(NumericData* const data) override {
	//		return new Int64Data(this->data * dynamic_cast<Int64Data*>(data)->GetData());
	//	}
	//	virtual NumericData* Divide(NumericData* const data)override {
	//		return new Int64Data(this->data / dynamic_cast<Int64Data*>(data)->GetData());
	//	}
	//	virtual NumericData* Minus() {
	//		return new Int64Data(-data);
	//	}
	//};

	//class FloatData : public NumericData {
	//private:
	//	float data;
	//public:
	//	FloatData(float data = 0) :data(data) {}
	//	float GetData() {
	//		return data;
	//	}
	//	virtual NumericData* Add(NumericData* const data) override {
	//		return new FloatData(this->data + dynamic_cast<FloatData*>(data)->GetData());
	//	}
	//	virtual NumericData* Substract(NumericData* const data) override {
	//		return new FloatData(this->data - dynamic_cast<FloatData*>(data)->GetData());
	//	}
	//	virtual NumericData* Multiply(NumericData* const data) override {
	//		return new FloatData(this->data * dynamic_cast<FloatData*>(data)->GetData());
	//	}
	//	virtual NumericData* Divide(NumericData* const data)override {
	//		return new FloatData(this->data / dynamic_cast<FloatData*>(data)->GetData());
	//	}
	//	virtual NumericData* Minus() {
	//		return new FloatData(-data);
	//	}
	//};

	//class DoubleData : public NumericData {
	//private:
	//	double data;
	//public:
	//	DoubleData(double data = 0) :data(data) {}
	//	double GetData() {
	//		return data;
	//	}
	//	virtual NumericData* Add(NumericData* const data) override {
	//		return new DoubleData(this->data + dynamic_cast<DoubleData*>(data)->GetData());
	//	}
	//	virtual NumericData* Substract(NumericData* const data) override {
	//		return new DoubleData(this->data - dynamic_cast<DoubleData*>(data)->GetData());
	//	}
	//	virtual NumericData* Multiply(NumericData* const data) override {
	//		return new DoubleData(this->data * dynamic_cast<DoubleData*>(data)->GetData());
	//	}
	//	virtual NumericData* Divide(NumericData* const data)override {
	//		return new DoubleData(this->data / dynamic_cast<DoubleData*>(data)->GetData());
	//	}
	//	virtual NumericData* Minus() {
	//		return new DoubleData(-data);
	//	}
	//};
}