#pragma once
#include"port.hpp"
namespace Noder {
	class Connection : public NObject{
		InputPort* input_port;
		OutputPort* output_port;
	public:
		Connection(InputPort* const input_port, OutputPort* const output_port):
			input_port(input_port), output_port(output_port) {
			output_port->AddFlushDataListener([=](Data* const data) {
				input_port->FlushData(data);
			});
		}
	};
}