#pragma once
#include"node.hpp"
#include"port.hpp"
#include"..//utility/utility.hpp"
namespace Noder {
	class GenericNode :public Node {
	private:
		Array<InputPort*>input_ports;
		Array<OutputPort*>output_ports;
	public:
		void AddInputPort(InputPort* const input_port) {
			this->input_ports.Append(input_port);
		}
		void AddOutputPort(OutputPort* const output_port) {
			this->output_ports.Append(output_port);
		}
	};
}