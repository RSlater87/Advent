#include "BeaconDetection.h"
#include "../AdventUtility/Utilities.h"
#include <regex>
#include <set>
#include <iostream>
#include <numeric>
#include "../AdventUtility/Timer.h"

BeaconDetection::SensorDetails::SensorDetails(Point _sensor, Point _beacon)
	: sensor(_sensor)
	, beacon(_beacon)
{
	manhattenDistance = ManhattenDistance(sensor, beacon);
	leftTop = Line{ Point{ sensor.x - manhattenDistance, sensor.y }, Point{ sensor.x, sensor.y - manhattenDistance} };
	leftBottom = Line{ Point{ sensor.x - manhattenDistance, sensor.y }, Point{ sensor.x, sensor.y + manhattenDistance} };
	rightTop = Line{ Point{ sensor.x + manhattenDistance, sensor.y }, Point{ sensor.x, sensor.y - manhattenDistance} };
	rightBottom = Line{ Point{ sensor.x + manhattenDistance, sensor.y }, Point{ sensor.x, sensor.y + manhattenDistance} };
}

std::vector<BeaconDetection::SensorDetails> BeaconDetection::ParseFile(const std::string& filename)
{
	auto allLines = SplitString(ReadAllText(filename), "\n");

	std::vector<BeaconDetection::SensorDetails> sensorDetails;
	for (auto& line : allLines)
	{
		std::regex numMatch(R"(-?\d+)");
		std::sregex_iterator iter(line.begin(), line.end(), numMatch);
		std::sregex_iterator end;

		Point sensor, beacon;
		sensor.x = std::stoi(iter++->str());
		sensor.y = std::stoi(iter++->str());
		beacon.x = std::stoi(iter++->str());
		beacon.y = std::stoi(iter++->str());
		sensorDetails.emplace_back(sensor, beacon);
	}
	
	return sensorDetails;
}

/// <summary>
/// The number of excluded points, minus the number of beacons on this row
/// </summary>
/// <param name="sensorDetails">Sensor Details</param>
/// <param name="row">Row to scan</param>
void BeaconDetection::Part1(const std::vector<SensorDetails>& sensorDetails, int row)
{
	Timer t;
	Line beam = CalculateBeam(sensorDetails, row);
	auto beaconsOnRow = BeaconsOnRow(sensorDetails, row);
	auto excludedLines = FindExcludedLines(sensorDetails, row,  beam);
	auto excludedPoints = std::accumulate(excludedLines.cbegin(), excludedLines.cend(), double{ 0 }, [&](double total, const Line& l)
		{
			return total + l.b.x - l.a.x;
		});
	
	std::cout << "No. of Excluded Points: "
		<< std::fixed << excludedPoints << " - " << beaconsOnRow.size() << " = " << excludedPoints - beaconsOnRow.size()
		<< std::endl;
}

/// <summary>
/// Go over eaach row until we hit one with a gap between the two excluded lines, and then calculate the tuning frequency
/// </summary>
/// <param name="sensorDetails">Sensor Details</param>
/// <param name="searchSpace">Search Space</param>
void BeaconDetection::Part2(const std::vector<SensorDetails>& sensorDetails, int searchSpace)
{
	Timer t;

	//Find the min and max of the sensor map. This is sensor.x +-/- manhatten distance
	Line beam = CalculateBeam(sensorDetails, 0);

	for (int i = 0; i <= searchSpace; ++i)
	{
		beam.a.y = beam.b.y = i;

		auto excludedLines = FindExcludedLines(sensorDetails, i, beam);

		if (excludedLines.size() > 1)
		{
			for (auto& line : excludedLines)
			{
				std::cout << std::fixed << "(" << line.a.y << ", " << line.a.x << ")"
					<< " -> (" << line.b.y << " , " << line.b.x << ")" << std::endl;
				std::cout << std::fixed << "Tuning Frequency: " << (line.b.x * 4000000) + line.b.y << std::endl;
			}
			break;
		}
	}
}

/// <summary>
/// Use the LeMothe calculation from StackOverflow to work out the intersection point
/// cf. https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
/// NB: because we're going from int-space to double-dpace, remember to round properly :)
/// </summary>
/// <param name="line0">Line 0</param>
/// <param name="line1">Line 1</param>
/// <param name="intersect">Intersection Point</param>
/// <returns>Whether there's an intersection point or not</returns>
bool BeaconDetection::ManhattenLineIntersection(Line line0, Line line1, Point* intersect)
{
	const double s0_x = static_cast<double>(line0.b.x - line0.a.x);
	const double s0_y = static_cast<double>(line0.b.y - line0.a.y);
	const double s1_x = static_cast<double>(line1.b.x - line1.a.x);
	const double s1_y = static_cast<double>(line1.b.y - line1.a.y);
	const double s = (-s0_y * (line0.a.x - line1.a.x) + s0_x * (line0.a.y - line1.a.y)) / (-s1_x * s0_y + s0_x * s1_y);
	const double t = ( s1_x * (line0.a.y - line1.a.y) - s1_y * (line0.a.x - line1.a.x)) / (-s1_x * s0_y + s0_x * s1_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		intersect->x = line0.a.x + std::lround(t * s0_x);
		intersect->y = line0.a.y + std::lround(t * s0_y);
		return true;
	}

	return false;
}

/// <summary>
/// For each sensor, find if the beam on this row intersects the polygon described by the Sensor -> Beacon space.
/// Then simplify these lines down to the overall exclusion zone for this row.
/// </summary>
/// <param name="sensorDetails">Sensor Details</param>
/// <param name="row">Row to scan</param>
/// <returns>List of excluded lines.</returns>
std::vector<Line> BeaconDetection::FindExcludedLines(const std::vector<SensorDetails>& sensorDetails, int row, Line beam)
{
	//For each sensor, find the intersect on the left (top or bottom) and right
	std::vector<Line> intersectingLines;
	Point intersectLeft, intersectRight;
	for (auto& sensorDetail : sensorDetails)
	{
		if (ManhattenLineIntersection(beam, sensorDetail.leftBottom, &intersectLeft)
			|| ManhattenLineIntersection(beam, sensorDetail.leftTop, &intersectLeft))
		{
			//Distance from left-intercept to right-intercept is (2 * distance) + 1 from left-intercept to the sensor
			auto width = sensorDetail.sensor.x - intersectLeft.x;
			intersectRight.x = intersectLeft.x + (width * 2) + 1;
			intersectRight.y = intersectLeft.y;
			intersectingLines.emplace_back(Line{ intersectLeft, intersectRight });
		}
	}

	//Loop over the intersecting lines and filter this into the non-overlapping lines
	std::vector<Line> lines = intersectingLines;
	bool foundOverlap = false;
	do
	{
		lines.clear();
		foundOverlap = false;
		for (auto& intersect : intersectingLines)
		{
			auto found = std::find_if(lines.begin(), lines.end(), [&](Line& line)
				{
					return InRange(intersect.a.x, line.a.x, line.b.x)
						|| InRange(intersect.b.x, line.a.x, line.b.x)
						|| InRange(line.a.x, intersect.a.x, intersect.b.x)
						|| InRange(line.b.x, intersect.a.x, intersect.b.x);
				});
			//Current line overlaps an existing line, update existing line to encompass both
			if (found != lines.end())
			{
				found->a.x = std::min(found->a.x, intersect.a.x);
				found->b.x = std::max(found->b.x, intersect.b.x);
				foundOverlap = true;
			}
			else
			{
				//Insert non-overlapping line
				lines.push_back(intersect);
			}
		}

		intersectingLines = lines;
	} while (foundOverlap);

	return lines;
}

/// <summary>
/// Scan the sensors for any beacons on this row.
/// </summary>
/// <param name="sensorDetails">Sensor details</param>
/// <param name="row">Row</param>
/// <returns>Unique list of beacons on this row</returns>
std::set<Point> BeaconDetection::BeaconsOnRow(const std::vector<SensorDetails>& sensorDetails, int row)
{
	//Find how many beacons are on this row  - these are always present as possible Beacon locations
	std::vector<Point> beacons;
	std::transform(sensorDetails.cbegin(), sensorDetails.cend(), std::back_inserter(beacons), [&](auto& sd)
		{
			return sd.beacon;
		});

	std::set<Point> beaconsOnRow;
	std::copy_if(beacons.cbegin(), beacons.cend(), std::inserter(beaconsOnRow, beaconsOnRow.begin()), [&](auto& b)
		{
			return b.y == row;
		});
	return beaconsOnRow;
}

/// <summary>
/// Work out the size of the beam based on the maximum possible space from the sensor polygons
/// </summary>
/// <param name="sensorDetails">Sensor Details</param>
/// <param name="row">Row</param>
/// <returns>Beam line</returns>
Line BeaconDetection::CalculateBeam(const std::vector<SensorDetails>& sensorDetails, int row)
{
	std::vector<PositionType> minXs, maxXs;
	std::transform(sensorDetails.cbegin(), sensorDetails.cend(), std::back_inserter(minXs), [&](auto& sd)
		{
			return sd.sensor.x - sd.manhattenDistance;
		});
	std::transform(sensorDetails.cbegin(), sensorDetails.cend(), std::back_inserter(maxXs), [&](auto& sd)
		{
			return sd.sensor.x + sd.manhattenDistance;
		});
	auto minX = *std::min_element(minXs.cbegin(), minXs.cend());
	auto maxX = *std::max_element(maxXs.cbegin(), maxXs.cend());
	Line beam = { { minX, row }, { maxX, row } };
	return beam;
}
