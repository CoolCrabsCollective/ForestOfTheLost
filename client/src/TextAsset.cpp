//
// Created by Winter on 02/10/2022.
//

#include <fstream>
#include "TextAsset.h"

TextAsset::TextAsset(std::string path) : path(path) {}

void* TextAsset::load() const {

#ifdef OS_SWITCH
	std::ifstream stream("romfs:/" + path);
#else
	std::ifstream stream("res/" + path);
#endif

	if(!stream.is_open())
		throw std::runtime_error("Count not open text file " + path);

	std::stringstream buffer;
	buffer << stream.rdbuf();

	return new std::string(buffer.str());
}

const std::string& TextAsset::getName() const {
	return path;
}
