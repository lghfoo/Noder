#pragma once
#include"port.hpp"
namespace Noder {
	class Connection : public NObject{
	private:
		Port* src_port = nullptr;
		Port* dst_port = nullptr;
		Port::UpdateDataListener update_data_listener = [=](PObject const data) {
			this->dst_port->UpdateData(data);
		};
		Port::FlushDataListener flush_data_listener = [=](Data* const data) {
			this->dst_port->FlushData(data);
		};
	public:
		Connection() {

		}
		Connection(Port* const src_port, Port* const dst_port){
			this->SetSrcPort(src_port);
			this->SetDstPort(dst_port);
		}
		void SetSrcPort(Port* const src_port) {
			this->src_port = src_port;
			src_port->AddFlushDataListener(flush_data_listener);
			src_port->AddUpdateDataListener(update_data_listener);
		}

		void SetDstPort(Port* const dst_port) {
			this->dst_port = dst_port;
		}

		~Connection() {
			src_port->RemoveFlushDataListener(flush_data_listener);
			src_port->RemoveUpdateDataListener(update_data_listener);
		}
	};
}