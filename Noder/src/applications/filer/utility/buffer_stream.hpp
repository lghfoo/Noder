#pragma once
#include<cstdio>
#include<cctype>
#include<fstream>
#include"../..//mather/data.hpp"
namespace Filer {
	class BufferInputStream {
		char* buffer = nullptr;
		int len = 0;
		int pos = 0;
		bool is_from_file = false;
	public:
		BufferInputStream(const char* filename) {
			this->is_from_file = true;
			std::ifstream stream(filename, std::ios::binary | std::ios::in);
			printf("open file: %s\n", filename);
			if (!stream) {
				printf("cant open file\n");
				return;
			}
			stream.seekg(0, std::ios::end);
			len = stream.tellg();
			buffer = new char[len];
			stream.seekg(0, std::ios::beg);
			stream.read(buffer, len);
			stream.close();
		}
		~BufferInputStream() {
			if (this->is_from_file) {
				delete[]buffer;
			}
		}
		BufferInputStream() {

		}
		BufferInputStream(char* buffer, int len): buffer(buffer), len(len){
		}

		enum Endian
		{
			BigEndian,
			LittleEndian
		};
		
		enum Mode
		{
			Binary,
			Text
		};

		int GetPos() {
			return this->pos;
		}

		template<typename T>
		T Next(Mode mode = Binary, Endian endian = LittleEndian) {
			SkipWhiteSpaces();
			if (mode == Binary) {
				return NextFromBinary<T>(endian);
			}
			return NextFromText<T>();
		}

		char NextChar() {
			if (StateInvalid())return 0;
			return buffer[pos++];
		}

		Data* NextNumber(Mather::NumberType type, Mode mode = Mode::Binary, Endian endian = Endian::LittleEndian) {
			Data* Ret = nullptr;
			switch (type)
			{
			case Mather::UINT8:
				Ret = new Mather::Number<uint8_t>(Next<uint8_t>(mode, endian));
				break;
			case Mather::INT8:
				Ret = new Mather::Number<int8_t>(Next<int8_t>(mode, endian));
				break;
			case Mather::UINT16:
				Ret = new Mather::Number<uint16_t>(Next<uint16_t>(mode, endian));
				break;
			case Mather::INT16:
				Ret = new Mather::Number<int16_t>(Next<int16_t>(mode, endian));
				break;
			case Mather::UINT32:
				Ret = new Mather::Number<uint32_t>(Next<uint32_t>(mode, endian));
				break;
			case Mather::INT32:
				Ret = new Mather::Number<int32_t>(Next<int32_t>(mode, endian));
				break;
			case Mather::UINT64:
				Ret = new Mather::Number<uint64_t>(Next<uint64_t>(mode, endian));
				break;
			case Mather::INT64:
				Ret = new Mather::Number<int64_t>(Next<int64_t>(mode, endian));
				break;
			case Mather::FLOAT32:
				Ret = new Mather::Number<float_t>(Next<float_t>(mode, endian));
				break;
			case Mather::FLOAT64:
				Ret = new Mather::Number<double_t>(Next<double_t>(mode, endian));
				break;
			default:
				break;
			}
			return Ret;
		}

		template<size_t size>
		void NextChars(char (&chars)[size]) {
			if (StateInvalid())return;
			int count = 0;
			while (count < size && !IsWhiteSpace(Peek())) {
				chars[count] = NextChar();
				count++;
			}
		}

		void NextChars(char* chars, int size) {
			if (StateInvalid() && size > Avaliable())return;
			memcpy(chars, buffer + pos, size);
			pos += size;
		}

		unsigned char NextByte() {
			if (StateInvalid())return 0;
			return (unsigned char)buffer[pos++];
		}

		void SkipWhiteSpace() {
			if (StateInvalid())return;
			if (!AtEnd() && std::isspace((char)Peek())) {
				Skip();
			}
		}

		bool IsWhiteSpace(int ch) {
			return ch == '\t' || ch == ' ' || ch == '\n' || ch == '\r' || ch == '\v' || ch=='\f';
		}

		void SkipWhiteSpaces() {
			if (StateInvalid())return;
			while (!AtEnd() && IsWhiteSpace(Peek())) {
				Skip();
			}
		}

		void Skip() {
			Skip(1);
		}

		void Skip(unsigned int count) {
			if (StateInvalid())return;
			pos += count;
			if (pos > len)pos = len;
		}

		void SkipLine() {
			if (StateInvalid())return;
			while (Peek() != '\n') {
				Skip();
			}
			Skip();
		}

		void SetPos(int pos) {
			this->pos = pos;
			if (this->pos > len)this->pos = len;
		}

		int Peek() {
			if (StateInvalid())return 0;
			return buffer[pos];
		}

		// is at end
		bool AtEnd() {
			return pos >= len;
		}

		// how many byte left
		unsigned int Avaliable() {
			return len - pos;
		}

		bool StateInvalid() {
			return !buffer || pos >= len;
		}

		template<typename T>
		T NextFromBinary(Endian endian) {
			T ret = 0;
			if (StateInvalid() || sizeof(T) > Avaliable())return ret;
			ret = *(T*)(buffer + pos);
			pos += sizeof(T);
			if (endian == BigEndian) {
				ReverseByteOrder(ret);
			}
			return ret;
		}

		template<typename T>
		void SwitchByte(T& value, int p1, int p2) {
			char* chs = (char*)& value;
			char tmp = chs[p1];
			chs[p1] = chs[p2];
			chs[p2] = tmp;
		}

		template<typename T>
		void ReverseByteOrder(T& t) {
			int byte_count = sizeof(t);
			int half_byte_count = byte_count / 2;
			for (int i = 0; i < half_byte_count; i++) {
				SwitchByte<T>(t, i, byte_count - 1 - i);
			}
		}

		template<typename T>
		T NextFromText() {
			cout << "origin" << endl;
			return T();
		}

#define DECLARE_NEXT_FROM_TEXT(TYPE, FORMAT)					\
		template<>												\
		TYPE NextFromText() {									\
			TYPE ret = 0;										\
			if (StateInvalid())return ret;						\
			int n = 0;											\
			sscanf(buffer + pos, FORMAT, &ret, &n);				\
			pos += n;											\
			return ret;											\
		}
		DECLARE_NEXT_FROM_TEXT(int8_t, "%hhd%n")
		DECLARE_NEXT_FROM_TEXT(uint8_t, "%hhu%n")
		DECLARE_NEXT_FROM_TEXT(int16_t, "%hd%n")
		DECLARE_NEXT_FROM_TEXT(uint16_t, "%hu%n")
		DECLARE_NEXT_FROM_TEXT(int32_t, "%d%n")
		DECLARE_NEXT_FROM_TEXT(uint32_t, "%u%n")
		DECLARE_NEXT_FROM_TEXT(int64_t, "%lld%n")
		DECLARE_NEXT_FROM_TEXT(uint64_t, "%llu%n")
		DECLARE_NEXT_FROM_TEXT(float_t, "%f%n")
		DECLARE_NEXT_FROM_TEXT(double_t, "%lf%n")
#undef DECLARE_NEXT_FROM_TEXT(TYPE, FORMAT)
	};
}