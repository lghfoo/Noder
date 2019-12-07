#pragma once
#include"..//object.hpp"
#include"data.hpp"
namespace Noder {
	class Port : public NObject{
	public:
		using FlushDataListener = Listener<void, Pointer<Data>>;
		using UpdateDataListener = Listener<void, PObject const>;
		enum PortType{INPUT_PORT, OUTPUT_PORT};
	private:
		//String port_name = "Port";
		Pointer<Data> data;
		LinkedList<FlushDataListener> flush_data_listeners = LinkedList<FlushDataListener>({});
		LinkedList<UpdateDataListener> update_data_listeners = LinkedList<UpdateDataListener>({});
	protected:
		bool is_busy = false;
		void ToggleBusy() { is_busy = !is_busy; }
	public:
		bool IsBusy() { return is_busy; }
		virtual PortType GetPortType()const = 0;
		bool IsInputPort() {
			return this->GetPortType() == INPUT_PORT;
		}
		bool IsOutputPort() {
			return this->GetPortType() == OUTPUT_PORT;
		}
		void FlushData(Pointer<Data> data) {
			this->data = data;
			this->NotifyFlush(data);
		}
		void UpdateData(PObject data) {
			if (this->IsBusy())return;
			this->ToggleBusy();
			if (this->data) {
				this->data->UpdateValue(data);
				this->NotifyUpdate(data);
			}
			this->ToggleBusy();
		}
		void NotifyUpdate(PObject data) {
			for (auto listener : update_data_listeners) {
				listener(data);
			}
		}
		void NotifyFlush(Pointer<Data> data) {
			for (auto listener : flush_data_listeners) {
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
		Pointer<Type> GetData() {
			auto ret = std::dynamic_pointer_cast<Type>(data);
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
	public:
		virtual PortType GetPortType()const override {
			return PortType::INPUT_PORT;
		}
	};

	class OutputPort : public Port {
	public:
		virtual PortType GetPortType()const override {
			return PortType::OUTPUT_PORT;
		}
	};
}