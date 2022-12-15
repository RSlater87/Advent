#pragma once
#include "../AdventUtility/Point.h"
#include <map>
#include <vector>
#include <string>

namespace SandSimulator
{
	enum class State
	{
		Air = '.',
		Rock = '#',
		Sand = 'O'
	};

	struct CaveMap
	{
		Point sandSource;
		size_t height;
		size_t width;
		std::vector<std::vector<State>> caveMap;	//Order column-first
	};

	CaveMap ParseFile(const std::string& filename);

	bool SpawnSand(CaveMap& cavemap);

	void ExportCaveMap(CaveMap& map, const std::string& filename);

	void Part1(CaveMap cavemap);
	void Part2(CaveMap cavemap);
}