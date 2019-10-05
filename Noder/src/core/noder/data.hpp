#pragma once
#include"../object.hpp"
namespace Noder {
	class Data : public NObject{
	public:
		//using UpdateDataListener = Function<void(PObject data)>;
		//using AfterUpdateDataListener = Function<void(PObject data)>;
		//using PUpdateDataListener = UpdateDataListener *;
		//using PAfterUpdateDataListener = AfterUpdateDataListener *;
		using UpdateDataListener = Listener<void, PObject>;
		using AfterUpdateDataListener = Listener<void, PObject>;
		void Update(PObject data) {
			// todo : skip?
			for (auto listener : update_data_listeners) {
				listener(data);
			}
			this->UpdateImpl(data);
			for (auto listener : after_update_data_listeners) {
				listener(data);
			}
		}
		virtual void UpdateImpl(PObject data) {

		}
		void AddUpdateDataListener(const UpdateDataListener& listener) {
			update_data_listeners.Append(listener);
		}
		void RemoveUpdateDataListener(const UpdateDataListener& listener) {
			update_data_listeners.Remove(listener);
		}
		void AddAfterUpdateDataListener(const AfterUpdateDataListener& listener) {
			after_update_data_listeners.Append(listener);
		}
		void RemoveAfterUpdateDataListener(const AfterUpdateDataListener& listener) {
			after_update_data_listeners.Remove(listener);
		}
	private:
		LinkedList<UpdateDataListener> update_data_listeners;
		LinkedList<AfterUpdateDataListener> after_update_data_listeners;
		
	};

}