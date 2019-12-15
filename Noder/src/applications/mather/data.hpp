#pragma once
#include"..//..//core/noder/data.hpp"
#include<iostream>
#include<random>
using std::ostream;
using namespace Noder;
namespace Mather {
	struct Float1 {
		float x = 0.0f;
		explicit Float1(float x = 0) :x(x) {}
		Float1 X() { return Float1{ x }; }
		Float1 operator+(const Float1& r) { return Float1{ x + r.x}; }
		Float1 operator-(const Float1& r) { return Float1{ x - r.x}; }
		Float1 operator*(const Float1& r) { return Float1{ x * r.x}; }
		Float1 operator/(const Float1& r) {
			if (r.x == 0)return Float1{ 1 }; // todo: return inf
			return Float1{ x / r.x };
		}
		float SquaredDistance() const {
			return x * x;
		}
		float Distance() const {
			return std::sqrtf(this->SquaredDistance());
		}
		void Normalize() {
			float Dist = this->Distance();
			if (Dist == 0.0f)return;
			x /= Dist;
		}
		Float1 Normalized() const {
			Float1 Ret{ x };
			Ret.Normalize();
			return Ret;
		}
		float Dot(const Float1& r) const { return x * r.x; }
		Float1 Floored() const { return Float1{ std::floorf(x) }; }
		Float1 Ceiled() const { return Float1{ std::ceilf(x) }; }
		Float1 Fraced() const { return Float1{ x - std::floorf(x) }; }
		Float1 Sined() const { return Float1{ std::sinf(x) }; }
		Float1 Cosed() const { return Float1{ std::cosf(x) }; }
		Float1 Absed() const { return Float1{std::fabsf(x) }; }
	};
	Float1 operator+(float v, const Float1& f) { return Float1{ f.x + v }; }
	Float1 operator+(const Float1& f, float v) { return v + f; }
	Float1 operator-(const Float1& f, float v) { return Float1{ f.x - v }; }
	Float1 operator*(const Float1& f, float v) { return Float1{ f.x * v }; }
	Float1 operator*(float v, const Float1& f) { return f * v; }
	Float1 operator/(const Float1& f, float v) { return v == 0.0f ? f : Float1{ f.x / v }; }
	struct Float2 {
		float x = 0.0f;
		float y = 0.0f;
		explicit Float2(float x = 0, float y = 0):x(x), y(y){}
		Float1 X() { return Float1{ x }; }
		Float1 Y() { return Float1{ y }; }
		Float2 XY() { return Float2{ x, y }; }
		Float2 YX() { return Float2{ y, x }; }
		Float2 operator+(const Float2& r) {	return Float2{ x + r.x, y + r.y }; }
		Float2 operator-(const Float2& r) { return Float2{ x - r.x, y - r.y }; }
		Float2 operator*(const Float2& r) { return Float2{ x * r.x, y * r.y }; }
		Float2 operator/(const Float2& r) {
			if (r.x == 0 || r.y == 0)return Float2{ 1, 1 }; // todo: return inf
			return Float2{ x / r.x, y / r.y };
		}
		float SquaredDistance() const {
			return x * x + y * y;
		}
		float Distance() const {
			return std::sqrtf(this->SquaredDistance());
		}
		void Normalize() {
			float Dist = this->Distance();
			if (Dist == 0.0f)return;
			x /= Dist;
			y /= Dist;
		}
		Float2 Normalized() const {
			Float2 Ret{ x, y };
			Ret.Normalize();
			return Ret;
		}
		float Dot(const Float2& r) const{ return x * r.x + y * r.y; }
		Float2 Corss() const { return Float2{ y, -x }; }
		Float2 Floored() const { return Float2{ std::floorf(x), std::floorf(y) }; }
		Float2 Ceiled() const { return Float2{ std::ceilf(x), std::ceilf(y) }; }
		Float2 Fraced() const { return Float2{ x - std::floorf(x), y - std::floorf(y) }; }
		Float2 Sined() const { return Float2{ std::sinf(x), std::sinf(y) }; }
		Float2 Cosed() const { return Float2{ std::cosf(x), std::cosf(y) }; }
		Float2 Absed() const { return Float2{ std::fabsf(x), std::fabsf(y) }; }
	};
	Float2 operator+(float v, const Float2& f) { return Float2{ f.x + v, f.y + v }; }
	Float2 operator+(const Float2& f, float v) { return v + f; }
	Float2 operator-(const Float2& f, float v) { return Float2{ f.x - v, f.y - v }; }
	Float2 operator*(const Float2& f, float v) { return Float2{ f.x * v, f.y * v }; }
	Float2 operator*(float v, const Float2& f) { return f * v; }
	Float2 operator/(const Float2& f, float v) { return v == 0.0f ? f : Float2{ f.x / v, f.y / v }; }
	struct Float3 {
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		explicit Float3(float x = 0, float y = 0, float z = 0) :x(x), y(y), z(z) {}
		explicit Float3(const Float2& f, float z = 0.0f) : x(f.x), y(f.y), z(z) {}
		Float1 X() { return Float1{ x }; }
		Float1 Y() { return Float1{ y }; }
		Float1 Z() { return Float1{ z }; }
		Float2 XY() { return Float2{ x, y }; }
		Float2 XZ() { return Float2{ x, z }; }
		Float2 YX() { return Float2{ y, x }; }
		Float2 YZ() { return Float2{ y, z }; }
		Float2 ZX() { return Float2{ z, x }; }
		Float2 ZY() { return Float2{ z, y }; }
		Float3 XYZ() { return Float3{ x, y, z }; }
		Float3 XZY() { return Float3{ x, z, y }; }
		Float3 YXZ() { return Float3{ y, x, z }; }
		Float3 YZX() { return Float3{ y, z, x }; }
		Float3 ZXY() { return Float3{ z, x, y }; }
		Float3 ZYX() { return Float3{ z, y, x }; }
		Float2 ToFloat2() { return this->XY(); }
		Float3 operator+(const Float3& r) { return Float3{ x + r.x, y + r.y , z + r.z }; }
		Float3 operator-(const Float3& r) { return Float3{ x - r.x, y - r.y , z - r.z }; }
		Float3 operator*(const Float3& r) { return Float3{ x * r.x, y * r.y , z * r.z }; }
		Float3 operator/(const Float3& r) {
			if (r.x == 0 || r.y == 0 || r.z == 0)return Float3{ 1, 1, 1 }; // todo: return inf
			return Float3{ x / r.x, y / r.y, z / r.z };
		}
		float SquaredDistance() const {
			return x * x + y * y + z * z;
		}
		float Distance() const {
			return std::sqrtf(this->SquaredDistance());
		}
		void Normalize() {
			float Dist = this->Distance();
			if (Dist == 0.0f)return;
			x /= Dist;
			y /= Dist;
			z /= Dist;
		}
		Float3 Normalized() const {
			Float3 Ret{ x, y, z };
			Ret.Normalize();
			return Ret;
		}
		float Dot(const Float3& r) const { return x * r.x + y * r.y + z * r.z; }
		Float3 Cross(const Float3& r) const { return Float3{ y * r.z - z * r.y, z * r.x - x * r.z, x * r.y - y * r.x }; }
		Float3 Floored() const { return Float3{ std::floorf(x), std::floorf(y), std::floorf(z) }; }
		Float3 Ceiled() const { return Float3{ std::ceilf(x), std::ceilf(y), std::ceilf(z) }; }
		Float3 Fraced() const { return Float3{ x - std::floorf(x), y - std::floorf(y), z - std::floorf(z) }; }
		Float3 Sined() const { return Float3{ std::sinf(x), std::sinf(y), std::sinf(z) }; }
		Float3 Cosed() const { return Float3{ std::cosf(x), std::cosf(y), std::cosf(z) }; }
		Float3 Absed() const { return Float3{ std::fabsf(x), std::fabsf(y), std::fabsf(z) }; }
	};
	Float3 operator+(float v, const Float3& f) { return Float3{ f.x + v, f.y + v, f.z + v }; }
	Float3 operator+(const Float3& f, float v) { return v + f; }
	Float3 operator-(const Float3& f, float v) { return Float3{ f.x - v, f.y - v, f.z - v }; }
	Float3 operator*(const Float3& f, float v) { return Float3{ f.x * v, f.y * v, f.z * v }; }
	Float3 operator*(float v, const Float3& f) { return f * v; }
	Float3 operator/(const Float3& f, float v) { return v == 0.0f ? f : Float3{ f.x / v, f.y / v, f.z / v }; }
	struct Float4 {
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;
		explicit Float4(float x = 0, float y = 0, float z = 0, float w = 0) :x(x), y(y), z(z), w(x) {}
		explicit Float4(const Float2& f, float z = 0.0f, float w = 0.0f) : x(f.x), y(f.y), z(z), w(w) {}
		explicit Float4(const Float3& f, float w = 0.0f) :x(f.x), y(f.y), z(f.z), w(w) {}
		Float1 X() { return Float1{ x }; }
		Float1 Y() { return Float1{ y }; }
		Float1 Z() { return Float1{ z }; }
		Float1 W() { return Float1{ w }; }
		Float2 XY() { return Float2{ x, y }; }
		Float2 XZ() { return Float2{ x, z }; }
		Float2 XW() { return Float2{ x, w }; }
		Float2 YX() { return Float2{ y, x }; }
		Float2 YZ() { return Float2{ y, z }; }
		Float2 YW() { return Float2{ y, w }; }
		Float2 ZX() { return Float2{ z, x }; }
		Float2 ZY() { return Float2{ z, y }; }
		Float2 ZW() { return Float2{ z, w }; }
		Float3 XYZ() { return Float3{ x, y, z }; }
		Float3 XYW() { return Float3{ x, y, w }; }
		Float3 XZY() { return Float3{ x, z, y }; }
		Float3 XZW() { return Float3{ x, z, w }; }
		Float3 XWY() { return Float3{ x, w, y }; }
		Float3 XWZ() { return Float3{ x, w, z }; }
		Float3 YXZ() { return Float3{ y, x, z }; }
		Float3 YXW() { return Float3{ y, x, w }; }
		Float3 YZX() { return Float3{ y, z, x }; }
		Float3 YZW() { return Float3{ y, z, w }; }
		Float3 YWX() { return Float3{ y, w, x }; }
		Float3 YWZ() { return Float3{ y, w, z }; }
		Float3 ZXY() { return Float3{ z, x, y }; }
		Float3 ZXW() { return Float3{ z, x, w }; }
		Float3 ZYX() { return Float3{ z, y, x }; }
		Float3 ZYW() { return Float3{ z, y, w }; }
		Float3 ZWX() { return Float3{ z, w, x }; }
		Float3 ZWY() { return Float3{ z, w, y }; }
		Float3 WXY() { return Float3{ w, x, y }; }
		Float3 WXZ() { return Float3{ w, x, z }; }
		Float3 WYX() { return Float3{ w, y, x }; }
		Float3 WYZ() { return Float3{ w, y, z }; }
		Float3 WZX() { return Float3{ w, z, x }; }
		Float3 WZY() { return Float3{ w, z, y }; }
		//for (var i = 0; i < str.length; i++) {
		//	for (var j = 0; j < str.length; j++) {
		//		if (j != i) {
		//			for (var k = 0; k < str.length; k++) {
		//				if (k != i && k != j) {
		//					for (var l = 0; l < str.length; l++) {
		//						if (l != k && l != i && l != j) {
		//							v = str.charAt(i) + str.charAt(j) + str.charAt(k) + str.charAt(l);
		//							console.log('Float4 ' + v.toUpperCase() + '() { return Float4{ ' + str.charAt(i) + ', ' + str.charAt(j) + ', ' + str.charAt(k) + ', ' + str.charAt(l) + '}; }');
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
		Float4 XYZW() { return Float4{ x, y, z, w }; }
	    Float4 XYWZ() { return Float4{ x, y, w, z }; }
	    Float4 XZYW() { return Float4{ x, z, y, w }; }
	    Float4 XZWY() { return Float4{ x, z, w, y }; }
	    Float4 XWYZ() { return Float4{ x, w, y, z }; }
	    Float4 XWZY() { return Float4{ x, w, z, y }; }
	    Float4 YXZW() { return Float4{ y, x, z, w }; }
	    Float4 YXWZ() { return Float4{ y, x, w, z }; }
	    Float4 YZXW() { return Float4{ y, z, x, w }; }
	    Float4 YZWX() { return Float4{ y, z, w, x }; }
	    Float4 YWXZ() { return Float4{ y, w, x, z }; }
	    Float4 YWZX() { return Float4{ y, w, z, x }; }
	    Float4 ZXYW() { return Float4{ z, x, y, w }; }
	    Float4 ZXWY() { return Float4{ z, x, w, y }; }
	    Float4 ZYXW() { return Float4{ z, y, x, w }; }
	    Float4 ZYWX() { return Float4{ z, y, w, x }; }
	    Float4 ZWXY() { return Float4{ z, w, x, y }; }
	    Float4 ZWYX() { return Float4{ z, w, y, x }; }
	    Float4 WXYZ() { return Float4{ w, x, y, z }; }
	    Float4 WXZY() { return Float4{ w, x, z, y }; }
	    Float4 WYXZ() { return Float4{ w, y, x, z }; }
	    Float4 WYZX() { return Float4{ w, y, z, x }; }
	    Float4 WZXY() { return Float4{ w, z, x, y }; }
	    Float4 WZYX() { return Float4{ w, z, y, x }; }
		Float2 ToFloat2() { return this->XY(); }
		Float3 ToFloat3() { return this->XYZ(); }
		Float4 operator+(const Float4& r) { return Float4{ x + r.x, y + r.y , z + r.z, w + r.w }; }
		Float4 operator-(const Float4& r) { return Float4{ x - r.x, y - r.y , z - r.z, w - r.w }; }
		Float4 operator*(const Float4& r) { return Float4{ x * r.x, y * r.y , z * r.z, w * r.w }; }
		Float4 operator/(const Float4& r) {
			if (r.x == 0 || r.y == 0 || r.z == 0 || r.w == 0)return Float4{ 1, 1, 1 }; // todo: return inf
			return Float4{ x / r.x, y / r.y, z / r.z, w / r.w };
		}
		float SquaredDistance() const {
			return x * x + y * y + z * z + w * w;
		}
		float Distance() const {
			return std::sqrtf(this->SquaredDistance());
		}
		void Normalize() {
			float Dist = this->Distance();
			if (Dist == 0.0f)return;
			x /= Dist;
			y /= Dist;
			z /= Dist;
			w /= Dist;
		}
		Float4 Normalized() const {
			Float4 Ret{ x, y, z, w };
			Ret.Normalize();
			return Ret;
		}
		float Dot(const Float4& r) const { return x * r.x + y * r.y + z * r.z + w * r.w; }
		Float4 Floored() const { return Float4{ std::floorf(x), std::floorf(y), std::floorf(z), std::floorf(w) }; }
		Float4 Ceiled() const { return Float4{ std::ceilf(x), std::ceilf(y), std::ceilf(z), std::ceilf(w) }; }
		Float4 Fraced() const { return Float4{ x - std::floorf(x), y - std::floorf(y), z - std::floorf(z), w - std::floorf(w) }; }
		Float4 Sined() const { return Float4{ std::sinf(x), std::sinf(y), std::sinf(z), std::sinf(w) }; }
		Float4 Cosed() const { return Float4{ std::cosf(x), std::cosf(y), std::cosf(z), std::cosf(w) }; }
		Float4 Absed() const { return Float4{ std::fabsf(x), std::fabsf(y), std::fabsf(z), std::fabsf(w) }; }
	};
	Float4 operator+(float v, const Float4& f) { return Float4{ f.x + v, f.y + v, f.z + v, f.w + v }; }
	Float4 operator+(const Float4& f, float v) { return v + f; }
	Float4 operator-(const Float4& f, float v) { return Float4{ f.x - v, f.y - v, f.z - v, f.w - v }; }
	Float4 operator-(float v, const Float4& f) { return Float4{ v - f.x, v - f.y, v - f.x, v - f.w }; }
	Float4 operator*(const Float4& f, float v) { return Float4{ f.x * v, f.y * v, f.z * v, f.w * v }; }
	Float4 operator*(float v, const Float4& f) { return f * v; }
	Float4 operator/(const Float4& f, float v) { return v == 0.0f ? f : Float4{ f.x / v, f.y / v, f.z / v, f.w / v }; }
	Float4 operator/(float v, const Float4& f) { return f.x == 0 || f.y == 0 || f.z == 0 || f.w == 0 ? f : Float4(v / f.x, v / f.y, v / f.z, v / f.w); }
	float Floor(float t) { return std::floorf(t); }
	float Ceil(float t) { return std::ceilf(t); }
	float Frac(float t) { return t - std::floorf(t); }
	float Sin(float t) { return std::sinf(t); }
	float Cos(float t) { return std::cosf(t); }
	float Abs(float t) { return std::fabsf(t); }
	float Clamp(float min, float t, float max) { return std::min(max, std::max(min, t)); }
	float Lerp(float a, float b, float t) { return a + (b - a) * Clamp(0, t, 1); }
	float SmoothStep(float a, float b, float t) {
		if (a == b)return b;
		t = Clamp(0, (t - a) / (b - a), 1);
		return t * t * (3.0f - 2.0f * t);
	}
	template<typename LType, typename RType> float Dot(LType l, RType r) { return l.Dot(r); }
	template<typename Type> Type Normalize(Type t) { return t.Normalized(); }
	template<typename Type> Type Floor(Type t) { return t.Floored(); }
	template<typename Type> Type Ceil(Type t) { return t.Ceiled(); }
	template<typename Type> Type Frac(Type t) { return t.Fraced(); }
	template<typename Type> Type Sin(Type t) { return t.Sined(); }
	template<typename Type> Type Cos(Type t) { return t.Cosed(); }
	template<typename Type> Type Abs(Type t) { return t.Absed(); }
	float Rand3DTo1D(const Float3& Value, const Float3& DotDir = Float3{ 12.9898f, 78.233f, 37.719f }) {
		return Frac(Sin(Value.Sined().Dot(DotDir)) * 143758.5453f);
	}
	float Rand2DTo1D(const Float2& Value, const Float2& DotDir = Float2{ 12.9898f, 78.233f }) {
		return Frac(Sin(Value.Sined().Dot(DotDir)) * 143758.5453f);
	}
	float Rand1DTo1D(float Value, float Mutator = 0.546f) {
		return Frac(Sin(Value + Mutator) * 143758.5453f);
	}
	Float2 Rand3DTo2D(const Float3& Value) {
		return Float2{
			Rand3DTo1D(Value, Float3{12.989f, 78.233f, 37.719f}),
			Rand3DTo1D(Value, Float3{39.346f, 11.135f, 83.155f})
		};
	}
	Float2 Rand2DTo2D(const Float2& Value) {
		return Float2{
			Rand2DTo1D(Value, Float2{12.989f, 78.233f}),
			Rand2DTo1D(Value, Float2{39.346f, 11.135f})
		};
	}
	Float2 Rand1DTo2D(float Value) {
		return Float2{
			Rand1DTo1D(Value, 3.9812f),
			Rand1DTo1D(Value, 7.1536f)
		};
	}
	Float3 Rand3DTo3D(const Float3& Value) {
		return Float3{
			Rand3DTo1D(Value, Float3(12.989f, 78.233f, 37.719f)),
			Rand3DTo1D(Value, Float3(39.346f, 11.135f, 83.155f)),
			Rand3DTo1D(Value, Float3(73.156f, 52.235f, 09.151f))
		};
	}
	Float3 Rand2DTo3D(Float2 value) {
		return Float3{
			Rand2DTo1D(value, Float2(12.989f, 78.233f)),
			Rand2DTo1D(value, Float2(39.346f, 11.135f)),
			Rand2DTo1D(value, Float2(73.156f, 52.235f))
		};
	}
	Float3 Rand1DTo3D(float value) {
		return Float3{
			Rand1DTo1D(value, 3.9812f),
			Rand1DTo1D(value, 7.1536f),
			Rand1DTo1D(value, 5.7241f)
		};
	}
	float CRand(float l = 0.0f, float r = 1.0f) {
		static std::uniform_real_distribution<float>dis(l, std::nextafterf(r, FLT_MAX));
		static std::mt19937 gen(2019);
		return dis(gen);
	}
	Float2 CRand2D(float l = 0.0f, float r = 1.0f) {
		return Float2{ CRand(l, r), CRand(l, r) };
	}
	Float3 Crand3D(float l = 0.0f, float r = 1.0f) {
		return Float3{ CRand(l, r), CRand(l, r), CRand(l, r) };
	}
	enum NumberType{
		UINT8, INT8,
		UINT16, INT16,
		UINT32, INT32,
		UINT64, INT64,
		FLOAT32,
		FLOAT64,
		TYPE_COUNT
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