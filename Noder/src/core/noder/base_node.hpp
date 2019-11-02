#pragma once
#include"node.hpp"
#include"port.hpp"
namespace Noder {
	class Node_2_1 : public Node{
	public:
		Node_2_1() {
			this->SetInputPort1(Pointer<InputPort>(new InputPort()));
			this->SetInputPort2(Pointer<InputPort>(new InputPort()));
			this->SetOutputPort(Pointer<OutputPort>(new OutputPort()));
		}

		Pointer<InputPort> GetInputPort1() {
			return input_port_1;
		}

		Pointer<InputPort> GetInputPort2() {
			return input_port_2;
		}

		Pointer<OutputPort> GetOutputPort() {
			return output_port;
		}
	private:
		void SetInputPort1(const Pointer<InputPort>& input_port) {
			this->input_port_1 = input_port;
			if (input_port_1) {
				//input_port_1->AddFlushDataListener(flush_data_listener);
				input_port_1->AddUpdateDataListener(update_data_listener);
			}
		}

		void SetInputPort2(const Pointer<InputPort>& input_port) {
			this->input_port_2 = input_port;
			if (input_port_2) {
				//input_port_2->AddFlushDataListener(flush_data_listener);
				input_port_2->AddUpdateDataListener(update_data_listener);
			}
		}
		void SetOutputPort(const Pointer<OutputPort>& output_port) {
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
		Port::FlushDataListener flush_data_listener = [&](Data* data) {
			if (this->input_port_1->HasData() && input_port_2->HasData() && output_port) {
				this->ProcessData();
			}
		};
	protected:
		Pointer<InputPort> input_port_1;
		Pointer<InputPort> input_port_2;
		Pointer<OutputPort> output_port;
	};

	class Node_1_1 : public Node {
	public:
		Node_1_1() {
			this->SetInputPort(Pointer<InputPort>(new InputPort()));
			this->SetOutputPort(Pointer<OutputPort>(new OutputPort()));
		}
		Pointer<InputPort> GetInputPort() {
			return input_port;
		}
		Pointer<OutputPort> GetOutputPort() {
			return output_port;
		}
	private:
		void SetInputPort(const Pointer<InputPort>& input_port) {
			this->input_port = input_port;
			if (this->input_port) {
				//this->input_port->AddFlushDataListener(flush_data_listener);
				this->input_port->AddUpdateDataListener(update_data_listener);
			}
		}
		void SetOutputPort(const Pointer<OutputPort>& output_port) {
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
		Port::FlushDataListener flush_data_listener = [&](Data* data) {
			if (this->input_port->HasData() && output_port) {
				this->ProcessData();
			}
		};
	protected:
		Pointer<InputPort> input_port;
		Pointer<OutputPort> output_port;
	};
}