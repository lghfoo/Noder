#pragma once
#include"..//..//applications/mather/data.hpp"
#include"../..//core/noder/node.hpp"
#include"../..//core/noder/base_node.hpp"
#include"file_node.hpp"
#include"utility/utility.hpp"
#include"data.hpp"
#include"utility/buffer_stream.hpp"
namespace Filer {
	class FilelenNode : public Noder::TNode<1, 1> {
	public:
		enum {
			FILENAME_INPUT,
		};
		enum{
			FILELEN_OUTPUT	// Number<uint64_t>
		};
		FilelenNode(PObject arg = nullptr) {
			this->GetInputPort(FILENAME_INPUT)->FlushData(new Text());
			this->GetOutputPort(FILELEN_OUTPUT)->FlushData(new Mather::Number<uint64_t>());
		}
		virtual void ProcessData()override {
			Pointer<InputPort>filename_port = this->GetInputPort(FILENAME_INPUT);

			auto filename = filename_port->GetData<Text>();
			Mather::Number<uint64_t>filelen = Utility::GetFileSize(filename->value.c_str());

			Pointer<OutputPort>filelen_port = this->GetOutputPort(FILELEN_OUTPUT);
			filelen_port->UpdateData(filelen.GetValue());
		}
	};
	class PickBufferFromFileNode : public Noder::TNode<3, 2> {
	public:
		enum {
			FILENAME_INPUT,
			BEGIN_ADDRESS_INPUT,
			BUFFER_SIZE_INPUT,		// byte count
		};
		enum{
			END_ADDRESS_OUTPUT,
			BUFFER_OUTPUT
		};
		PickBufferFromFileNode(PObject arg = nullptr) {
			this->GetInputPort(FILENAME_INPUT)->FlushData(new Text);
			this->GetInputPort(BEGIN_ADDRESS_INPUT)->FlushData(new Mather::Number<uint64_t>);
			this->GetInputPort(BUFFER_SIZE_INPUT)->FlushData(new Mather::Number<uint64_t>);

			this->GetOutputPort(END_ADDRESS_OUTPUT)->FlushData(new Mather::Number<uint64_t>);
			this->GetOutputPort(BUFFER_OUTPUT)->FlushData(new BufferData);
		}
		virtual void ProcessData()override {
			auto filename = this->GetInputPort(FILENAME_INPUT)->GetData<Text>()->value.c_str();
			auto start_address = this->GetInputPort(BEGIN_ADDRESS_INPUT)->GetData<Mather::Number<uint64_t>>()->value;
			auto buffer_size = this->GetInputPort(BUFFER_SIZE_INPUT)->GetData<Mather::Number<uint64_t>>()->value;

			buffer.Reset(buffer_size);
			auto file = fopen(filename, "rb");
			fseek(file, start_address, SEEK_SET);
			fread(buffer.buffer, sizeof(char), buffer_size, file);
			fclose(file);
			auto end_address = start_address + buffer_size;

			this->GetOutputPort(END_ADDRESS_OUTPUT)->UpdateData(&end_address);
			this->GetOutputPort(BUFFER_OUTPUT)->UpdateData(&buffer);
		}

		Buffer buffer;
	};

	class PickBufferFromBufferNode : public Noder::Node {
	public:
		PickBufferFromBufferNode(PObject arg = nullptr){}
	};

	class PickNumberFromBufferNode : public Noder::TNode<5, 2> {
	public:
		enum {
			BUFFER_INPUT,
			BEGIN_ADDRESS_INPUT,	// Number<uint64_t>
			NUMBER_TYPE_INPUT,		// UINT/INT8/16/32/64 / FLOAT32/64
			FORMAT_INPUT,			// Text or Binray
			ENDIAN_INPUT,			// BIG/LITTLE ENDIAN
		};
		enum{
			END_ADDRESS_OUTPUT,		// Number<uint64_t>
			NUMBER_OUTPUT			// Number<???>
		};
		PickNumberFromBufferNode(PObject arg = nullptr) {
			this->GetInputPort(BUFFER_INPUT)->FlushData(new BufferData);
			this->GetInputPort(BEGIN_ADDRESS_INPUT)->FlushData(new Mather::Number<uint64_t>);
			this->GetInputPort(NUMBER_TYPE_INPUT)->FlushData(new Mather::Number<int>);
			this->GetInputPort(FORMAT_INPUT)->FlushData(new Mather::Number<int>);
			this->GetInputPort(ENDIAN_INPUT)->FlushData(new Mather::Number<int>);

			this->GetOutputPort(END_ADDRESS_OUTPUT)->FlushData(new Mather::Number<uint64_t>);
		}
		virtual void ProcessData()override {
			Buffer* buffer_wrapper = this->GetInputPort(BUFFER_INPUT)->GetData<BufferData>()->buffer;
			uint64_t begin_address = this->GetInputPort(BEGIN_ADDRESS_INPUT)->GetData<Mather::Number<uint64_t>>()->value;
			int number_type = this->GetInputPort(NUMBER_TYPE_INPUT)->GetData<Mather::Number<int>>()->value;
			int format = this->GetInputPort(FORMAT_INPUT)->GetData<Mather::Number<int>>()->value;
			int endian = this->GetInputPort(ENDIAN_INPUT)->GetData<Mather::Number<int>>()->value;

			BufferInputStream stream(buffer_wrapper->buffer, buffer_wrapper->size);
			stream.SetPos(begin_address);
			Data* number = stream.NextNumber(static_cast<Mather::NumberType>(number_type), 
				static_cast<BufferInputStream::Mode>(format), 
				static_cast<BufferInputStream::Endian>(endian));
			uint64_t end_address = stream.GetPos();

			this->GetOutputPort(NUMBER_OUTPUT)->FlushData(number);
			this->GetOutputPort(END_ADDRESS_OUTPUT)->UpdateData(&end_address);
		}
	};

	class PickStringFromBufferNode : public Noder::TNode<3, 2> {
	public:
		enum {
			BUFFER_INPUT,
			BEGIN_ADDRESS_INPUT,
			STRING_SIZE_INPUT,
		};
		enum{
			END_ADDRESS_OUTPUT,
			STRING_OUTPUT
		};
		PickStringFromBufferNode(PObject arg = nullptr) {

		}
		virtual void ProcessData()override {

		}
	};
}