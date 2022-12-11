#include "TuningTrouble.h"
#include "../AdventUtility/Utilities.h"
#include <set>
#include <iostream>

const size_t MarkerSize = 4;
const size_t PacketSize = 14;

void TuningTrouble::ScanForMarkerPosition(const std::string& filename)
{
	std::string signal = ReadAllText(filename);

	size_t position = FindUniqueMessage(signal, MarkerSize);

	std::cout << position << std::endl;

	position = FindUniqueMessage(signal, PacketSize);

	std::cout << position << std::endl;
}

size_t TuningTrouble::FindUniqueMessage(std::string& s, size_t m)
{
	for (size_t i = m; ; ++i) if (((std::set<char>{s.begin() + i - m, s.begin() + i}).size() == m)) return i;

	throw std::logic_error("oops");
}
