#pragma once

#include <map>
#include <string>
#include <vector>

#include "../AdventUtility/Point.h"

namespace HillClimbingAlgorithm
{
	struct HeatMap
	{
		Point start;
		Point end;
		std::map<Point, char> points;
	};

	HeatMap ParseFile(const std::string& filename);

	void Part1(HeatMap& heatmap);

	void Part2(HeatMap& heatmap);

	std::map<Line, int> GenerateDistanceGraph(HeatMap& heatmap);

	std::map<Point, int> Dijkstra_FindEndWithShortestRoute(
		Point startPosition,
		HeatMap& heatmap,
		const std::map<Line, int>& distanceGraph);
}