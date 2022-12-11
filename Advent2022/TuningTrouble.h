#pragma once
#include <string>

namespace TuningTrouble
{
	void ScanForMarkerPosition(const std::string& filename);
	size_t FindUniqueMessage(std::string& signal, size_t messageSize);
}