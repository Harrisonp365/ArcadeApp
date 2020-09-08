#include "FileCommandLoader.h"
#include <fstream>
#include <iostream>
#include "Color.h"
#include "Vec2D.h"

void FileCommandLoader::AddCommand(const Command& command)
{
	mCommands.push_back(command);
}

void FileCommandLoader::LoadFile(const std::string& filePath)
{

}

Color FileCommandLoader::ReadColor(const ParseFuncParams& params)
{
	size_t nextSpacePos = params.line.find_first_of(" ", params.dilimitPos + 1);
	int r = std::stoi(params.line.substr(params.dilimitPos, (nextSpacePos - params.dilimitPos)));

	size_t lastSpacePos = nextSpacePos;
	nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);
	int g = std::stoi(params.line.substr(lastSpacePos + 1, nextSpacePos - lastSpacePos));

	nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);
	int b = std::stoi(params.line.substr(lastSpacePos + 1, nextSpacePos - lastSpacePos));
	int a = std::stoi(params.line.substr(nextSpacePos + 1));

	return Color(r, g, b, a);
}

Vec2D FileCommandLoader::ReadSize(const ParseFuncParams& params)
{
	size_t nextSpacePos = params.line.find_first_of(" ", params.dilimitPos + 1);
	int width = std::stoi(params.line.substr(params.dilimitPos, nextSpacePos - params.dilimitPos));

	size_t lastSpacePos = nextSpacePos;
	nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);
	int height = std::stoi(params.line.substr(lastSpacePos + 1, nextSpacePos - lastSpacePos));

	return Vec2D(width, height);
}

int FileCommandLoader::ReadInt(const ParseFuncParams& params)
{
	std::string intStr = params.line.substr(params.dilimitPos + 1);
	return std::stoi(intStr);
}

std::string FileCommandLoader::ReadString(const ParseFuncParams& params)
{
	return params.line.substr(params.dilimitPos + 1);
}

char FileCommandLoader::ReadChar(const ParseFuncParams& params)
{
	return params.line.substr(params.dilimitPos + 1)[0];
}