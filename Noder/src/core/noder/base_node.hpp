#pragma once
#include"node.hpp"
#include"port.hpp"
namespace Noder {
	template<int I, int O>
	class TNode : public Node {
	private:
		InputPort* input_ports[I] = {};
		OutputPort* output_ports[O] = {};
	public:
		TNode() {
			for (int i = 0; i < I; i++) {
				input_ports[i] = new InputPort();
				input_ports[i]->AddUpdateDataListener(update_data_listener);
			}
			for (int i = 0; i < O; i++) {
				output_ports[i] = new OutputPort();
				output_ports[i]->AddFlushDataListener([=](Pointer<Data> data) {
					output_ports[i]->UpdateData(data->GetValue());
				});
			}
		}
		InputPort* GetInputPort(int index) {
			return index >= 0 && index < I ? input_ports[index] : nullptr;
		}

		OutputPort* GetOutputPort(int index) {
			return index >= 0 && index < O ? output_ports[index] : nullptr;
		}
	private:
		Port::UpdateDataListener update_data_listener = [&](PObject data) {
			for (int i = 0; i < I; i++) {
				if (!(this->input_ports[i]->HasData())) {
					return;
				}
			}
			this->ProcessData();
		};
	};
	class Node_2_1 : public Node{
	public:
		Node_2_1() {
			this->SetInputPort1(new InputPort());
			this->SetInputPort2(new InputPort());
			this->SetOutputPort(new OutputPort());
		}

		InputPort* GetInputPort1() {
			return input_port_1;
		}

		InputPort* GetInputPort2() {
			return input_port_2;
		}

		OutputPort* GetOutputPort() {
			return output_port;
		}
	private:
		void SetInputPort1(InputPort* input_port) {
			this->input_port_1 = input_port;
			if (input_port_1) {
				//input_port_1->AddFlushDataListener(flush_data_listener);
				input_port_1->AddUpdateDataListener(update_data_listener);
			}
		}

		void SetInputPort2(InputPort* input_port) {
			this->input_port_2 = input_port;
			if (input_port_2) {
				//input_port_2->AddFlushDataListener(flush_data_listener);
				input_port_2->AddUpdateDataListener(update_data_listener);
			}
		}
		void SetOutputPort(OutputPort* output_port) {
			this->output_port = output_port;
			//if (this->output_port) {
			//	this->output_port->AddFlushDataListener(flush_data_listener);
			//}
		}

		Port::UpdateDataListener update_data_listener = [&](PObject data) {
			if (this->input_port_1->HasData() && input_port_2->HasData() && output_port) {
				this->ProcessData();
			}
		};
		Port::FlushDataListener flush_data_listener = [&](Pointer<Data> data) {
			if (this->input_port_1->HasData() && input_port_2->HasData() && output_port) {
				this->ProcessData();
			}
		};
	protected:
		InputPort* input_port_1;
		InputPort* input_port_2;
		OutputPort* output_port;
	};

	class Node_1_1 : public Node {
	public:
		Node_1_1() {
			this->SetInputPort(new InputPort());
			this->SetOutputPort(new OutputPort());
		}
		InputPort* GetInputPort() {
			return input_port;
		}
		OutputPort* GetOutputPort() {
			return output_port;
		}
	private:
		void SetInputPort(InputPort* input_port) {
			this->input_port = input_port;
			if (this->input_port) {
				//this->input_port->AddFlushDataListener(flush_data_listener);
				this->input_port->AddUpdateDataListener(update_data_listener);
			}
		}
		void SetOutputPort(OutputPort* output_port) {
			this->output_port = output_port;
			//if (this->output_port) {
			//	this->output_port->AddFlushDataListener(flush_data_listener);
			//}
		}
	private:
		Port::UpdateDataListener update_data_listener = [&](PObject data) {
			if (this->input_port->HasData() && output_port) {
				this->ProcessData();
			}
		};
		Port::FlushDataListener flush_data_listener = [&](Pointer<Data> data) {
			if (this->input_port->HasData() && output_port) {
				this->ProcessData();
			}
		};
	protected:
		InputPort* input_port;
		OutputPort* output_port;
	};
}