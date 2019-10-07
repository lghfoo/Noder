#pragma once
#include"..//object.hpp"
#include"data.hpp"
namespace Noder {
	class Port : public NObject{
	public:
		using FlushDataListener = Listener<void, Data* const>;
		using UpdateDataListener = Listener<void, PObject const>;
	private:
		String port_name = "Port";
		Data* data = nullptr;
		LinkedList<FlushDataListener> flush_data_listeners = LinkedList<FlushDataListener>({});
		LinkedList<UpdateDataListener> update_data_listeners = LinkedList<UpdateDataListener>({});
	public:
		void FlushData(Data* const data) {
			if (this->data != nullptr && this->data != data)
				delete this->data;
			this->data = data;
			for (auto listener : flush_data_listeners) {
				listener(data);
			}
		}
		void UpdateData(PObject data) {
			if (this->data) {
				this->data->UpdateValue(data);
			}
			for (auto listener : update_data_listeners) {
				listener(data);
			}
		}
		void AddFlushDataListener(const FlushDataListener& listener) {
			this->flush_data_listeners.Append(listener);
		}

		void RemoveFlushDataListener(const FlushDataListener& listener) {
			this->flush_data_listeners.Remove(listener);
		}

		void AddUpdateDataListener(const UpdateDataListener& listener) {
			this->update_data_listeners.Append(listener);
		}

		void RemoveUpdateDataListener(const UpdateDataListener& listener) {
			this->update_data_listeners.Remove(listener);
		}
		template<typename Type>
		Type* GetData() {
			auto ret = dynamic_cast<Type*>(data);
			if (!ret) {
				return nullptr;
			}
			return ret;
		}

		bool HasData() {
			return data != nullptr;
		}
	};

	class InputPort : public Port {

	};

	class OutputPort : public Port {

	};
}