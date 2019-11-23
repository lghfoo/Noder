#pragma once
#include"..//..//applications/mather/data.hpp"
#include"../..//core/noder/node.hpp"
#include"../..//core/noder/base_node.hpp"
#include"file_node.hpp"
#include"utility/utility.hpp"
namespace Filer {
	class FilelenNode : public Noder::TNode<1, 1> {
	public:
		enum {
			FILENAME_INPUT,
		};
		enum{
			FILELEN_OUTPUT	// Number<uint64_t>
		};
		FilelenNode() {
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
	class PickBufferFromFilenameNode : public Noder::TNode<3, 2> {
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
		PickBufferFromFilenameNode() {
			this->GetInputPort(FILENAME_INPUT)->FlushData(new Text());
			this->GetInputPort(BEGIN_ADDRESS_INPUT)->FlushData(new Mather::Number<uint64_t>());
			this->GetInputPort(BUFFER_SIZE_INPUT)->FlushData(new Mather::Number<uint64_t>());

			this->GetOutputPort(END_ADDRESS_OUTPUT)->FlushData(new Mather::Number<uint64_t>());
			this->GetOutputPort(BUFFER_OUTPUT)->FlushData(nullptr);
		}
		virtual void ProcessData()override {
			
		}
	};

	class PickBufferFromBufferNode : public Noder::Node {

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
		virtual void ProcessData()override {

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
		virtual void ProcessData()override {

		}
	};
}