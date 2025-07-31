#pragma once

#include <string>

void savejson(const std::string &jsonstring, const std::string &filename);

std::string json2csv(std::string &jsonstring);