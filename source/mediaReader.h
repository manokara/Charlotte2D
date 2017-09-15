#pragma once

#include<string>
#include<map>

namespace miwa
{
	namespace externalFiles
	{
		class dataBuffer
		{
			uint8_t* _dataPointer = nullptr;
			size_t _dataSize = 0;
		public:
			dataBuffer(uint8_t* dataPointer, size_t dataSize);
			dataBuffer();
			size_t getSize() const;
			uint8_t* getData() const;
		};

		std::map<std::string, dataBuffer>& getMap();

		dataBuffer getFileBuffer(std::string path);

		int getSize();

		void fillFileBuffer();
	}
}