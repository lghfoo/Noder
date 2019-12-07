#pragma once
#include"../object.hpp"
namespace Noder {
	class Data : public NObject{
	public:
		//using UpdateDataListener = Listener<void, PObject>;
		//using AfterUpdateDataListener = Listener<void, PObject>;
		void UpdateValue(PObject data) {
			// todo : skip?
			//for (auto listener : update_data_listeners) {
			//	listener(data);
			//}
			this->UpdateValueImpl(data);
			//for (auto listener : after_update_data_listeners) {
			//	listener(data);
			//}
		}
		virtual PObject GetValue(){
			return nullptr;
		}
		virtual void UpdateValueImpl(PObject data) {
		}
	//	void AddUpdateDataListener(const UpdateDataListener& listener) {
	//		update_data_listeners.Append(listener);
	//	}
	//	void RemoveUpdateDataListener(const UpdateDataListener& listener) {
	//		update_data_listeners.Remove(listener);
	//	}
	//	void AddAfterUpdateDataListener(const AfterUpdateDataListener& listener) {
	//		after_update_data_listeners.Append(listener);
	//	}
	//	void RemoveAfterUpdateDataListener(const AfterUpdateDataListener& listener) {
	//		after_update_data_listeners.Remove(listener);
	//	}
	//private:
	//	LinkedList<UpdateDataListener> update_data_listeners;
	//	LinkedList<AfterUpdateDataListener> after_update_data_listeners;
		
	};

}