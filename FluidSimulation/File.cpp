#include "File.h"

std::string File::Read(const std::string& filePath)
{
	std::ifstream file;
	file.open(filePath);

	std::string fileContents;
	std::string lineContents;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, lineContents);
			fileContents.append(lineContents + "\n");
		}

		return fileContents;
	}
	else
	{
		std::cout << "File::Read: Could not open file: " + filePath + "!\n";
		return fileContents;
	}
}

bool File::Write(const std::string& filePath, const std::string& content)
{
	std::ofstream file;
	file.open(filePath);

	if (file.is_open())
	{
		file << content;
		return true;
	}
	else
	{
		std::cout << "File::Write: Could not open file: " + filePath + "!\n";
		return false;
	}
}

bool File::Exists(const std::string& filePath)
{
	std::ofstream file;
	file.open(filePath);

	return file.is_open();
}

std::string File::GetExtension(const std::string& filePath)
{
	if (filePath.find_last_of(".") != std::string::npos)
	{
		return filePath.substr(filePath.find_last_of(".") + 1);
	}

	return "";
}