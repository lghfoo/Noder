#pragma once
#include<fstream>
namespace Filer {
	struct Utility {
		static uint64_t GetFileSize(const char* filename) {
			std::ifstream stream(filename, std::ios::binary | std::ios::in);
			printf("open file: %s\n", filename);
			if (!stream) {
				printf("cant open file: %s\n", filename);
				return 0;
			}
			stream.seekg(0, std::ios::end);
			uint64_t len = stream.tellg();
			stream.close();
			return len;
		}

		static bool FileExist(const char* filename) {
			struct stat buffer;
			return !stat(filename, &buffer);
		}
	};
}