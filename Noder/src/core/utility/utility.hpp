#pragma once
#include<vector>
#include<string>
#include<list>
#include<functional>
#include<algorithm>
#include<memory>
using std::vector;
using std::string;
using std::to_string;
using std::function;
using std::list;
namespace Noder{
	class String : public string {
	public:
		String(const string& str):string(str) {
		}
		String(const char* ptr) :string(ptr) {
		}
		static String ToString(int x) {
			return String(to_string(x));
		}
		static String ToString(long long x) {
			return String(to_string(x));
		}
		static String ToString(float x) {
			return String(to_string(x));
		}
		static String ToString(double x) {
			return String(to_string(x));
		}
		static String ToString(unsigned long long x) {
			return String(to_string(x));
		}
	};

	using byte = unsigned char;

	template<class Type>
	using Function = function<Type>;


	//template<typename Type>
	//class Function : public function<Type> {

	//};

	template<typename Type>
	class Array : public vector<Type> {
	public:
		void Append(const Type& data) {
			this->push_back(data);
		}
		void Remove(const Type& data) {
			this->erase(data);
		}
	};

	template<typename Type>
	class LinkedList : public list<Type> {
	public:
		void Append(const Type& data) {
			this->push_back(data);
		}
		void Remove(const Type& data) {
			this->remove(data);
		}
		bool IsEmpty() {
			return this->empty();
		}
	};

	class Utility {
	public:

		template<typename T>
		static void DeletePointer(T& pointer) {
			if (!pointer)return;
			delete pointer;
			pointer = nullptr;
		}

	};

	template<class Ret, class... Types>
	class Callback {
	public:
		using CallbackFunction = std::function<Ret(Types...)>;
		using PCallbackFunction = std::shared_ptr<CallbackFunction>;

		template<typename Type>
		Callback(const Type& t) {
			this->SetFunction(t);
		}
		Callback(const Callback& listener) {
			this->p_func = listener.p_func;
		}
		Callback() {
		}
		void SetFunction(const CallbackFunction& func) {
			p_func = PCallbackFunction(new CallbackFunction(func));
		}
		bool IsValid() {
			return p_func != nullptr;
		}
		Ret operator()(Types... args) const {
			if (p_func == nullptr) {
				throw std::exception("function is null");
			}
			return (*p_func)(_STD forward<Types>(args)...);
		}
		bool operator==(const Callback<Ret, Types...>& callback) const {
			return this->p_func == callback.p_func;
		}
		template<typename Type>
		Callback& operator=(const Type& t) {
			this->p_func = t.p_func;
			return *this;
		}
	private:
		PCallbackFunction p_func;
	};

	template<class Ret, class... Types>
	using Listener = Callback<Ret, Types...>;

	template<class Type>
	using Pointer = std::shared_ptr<Type>;


}