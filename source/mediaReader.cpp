#include "stdafx.h"
#include"mediaReader.h"
#include<map>
#include<vector>
#include<iostream>

extern std::map<std::string, miwa::externalFiles::dataBuffer> allData;

miwa::externalFiles::dataBuffer::dataBuffer()
{

}

miwa::externalFiles::dataBuffer::dataBuffer(uint8_t *dataPointer, size_t dataSize)
{
	_dataPointer = dataPointer;
	_dataSize = dataSize;
}

size_t miwa::externalFiles::dataBuffer::getSize() const
{
	return _dataSize;
}

unsigned char* miwa::externalFiles::dataBuffer::getData() const
{
	return _dataPointer;
}
std::map<std::string, miwa::externalFiles::dataBuffer>& miwa::externalFiles::getMap() 
{
	return allData;
}
miwa::externalFiles::dataBuffer miwa::externalFiles::getFileBuffer(std::string pathFind)
{
	const char* f = pathFind.c_str();
	auto dtbuf = allData.find(f);
	if (dtbuf != allData.end())
	{
		return dtbuf->second;
	}
	else {
		std::cout << "not found" << std::endl;
		return miwa::externalFiles::dataBuffer(nullptr, 0);
	}
}

int miwa::externalFiles::getSize()
{
	return allData.size();
}