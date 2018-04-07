#pragma once

#include <string>

class File
{
public:
	static std::string Read(const std::string& filePath);
	static bool Write(const std::string& filePath, const std::string& content);
	static bool Exists(const std::string& filePath);
	static std::string GetExtension(const std::string& filePath);
};