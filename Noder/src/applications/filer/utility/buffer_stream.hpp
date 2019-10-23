#pragma once
#include<cstdio>
#include<cctype>
#include<fstream>
namespace Filer {
	class BufferInputStream {
		char* buffer = nullptr;
		int len = 0;
		int pos = 0;
	public:
		BufferInputStream(const char* filename) {
			std::ifstream stream(filename, std::ios::binary | std::ios::in);
			if (!stream) {
				return;
			}
			stream.seekg(0, std::ios::end);
			len = stream.tellg();
			buffer = new char[len];
			stream.seekg(0, std::ios::beg);
			stream.read(buffer, len);
			stream.close();
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

		DECLARE_NEXT_FROM_TEXT(int, "%d%n")
		DECLARE_NEXT_FROM_TEXT(long long, "%lld%n")
		DECLARE_NEXT_FROM_TEXT(float, "%f%n")
		DECLARE_NEXT_FROM_TEXT(double, "%lf%n")
#undef DECLARE_NEXT_FROM_TEXT(TYPE, FORMAT)
	};
}