#pragma once
#include "../AdventUtility/Point.h"
#include <vector>
#include <string>
#include <set>

namespace BeaconDetection
{
	struct SensorDetails
	{
		Point sensor;
		Point beacon;
		PositionType manhattenDistance;

		Line leftBottom;
		Line leftTop;
		Line rightBottom;
		Line rightTop;

		SensorDetails(Point _sensor, Point _beacon);
	};

	std::vector<SensorDetails> ParseFile(const std::string& filename);

	void Part1(const std::vector<SensorDetails>& sensorDetails, int row);

	void Part2(const std::vector<SensorDetails>& sensorDetails, int searchSpace);

	bool ManhattenLineIntersection(Line line0, Line line1, Point* intersect);
	std::vector<Line> FindExcludedLines(const std::vector<SensorDetails>& sensorDetails, int row);
	std::set<Point> BeaconsOnRow(const std::vector<SensorDetails>& sensorDetails, int row);
	Line CalculateBeam(const std::vector<SensorDetails>& sensorDetails, int row);
}