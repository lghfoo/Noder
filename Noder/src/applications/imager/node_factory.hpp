#pragma once
#include"data.hpp"
#include"image_node.hpp"
#include"ppm_fimage_node.hpp"
#include"grayen_node.hpp"
#include"binaryzation/otsu_node.hpp"
using namespace Noder;
namespace Imager {
	class NodeFactory {
	public:
		enum NodeType {
			IMAGE_VALUE,
			PPM_FILE_2_IMAGE,
			GRAYEN,
			OTSU_BINARYZATION
		};
		static Node* CreateNode(const NodeType& type) {
			Node* ret = nullptr;
			switch (type)
			{
			case IMAGE_VALUE:
				ret = new ImageNode;
				break;
			case PPM_FILE_2_IMAGE:
				ret = new PPMFImageNode;
				break;
			case GRAYEN:
				ret = new GrayenNode;
				break;
			case OTSU_BINARYZATION:
				ret = new OTSUNode;
				break;
			default:
				break;
			}
			return ret;
		}
	};
}
