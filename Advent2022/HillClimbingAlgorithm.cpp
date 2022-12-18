#include "HillClimbingAlgorithm.h"
#include "../AdventUtility/Utilities.h"
#include "../AdventUtility/Timer.h"

#include <iostream>
#include <deque>

HillClimbingAlgorithm::HeatMap HillClimbingAlgorithm::ParseFile(const std::string& filename)
{
    //Load the heatmap
    HeatMap heatmap;
    auto allLines = SplitString(ReadAllText(filename), "\n");

    for (int row = 0; row < allLines.size(); ++row)
    {
        int nCols = static_cast<int>(allLines[row].size());
        for (int col = 0; col < nCols; ++col)
        {
            char elevation = allLines[row][col];
            if (elevation == 'S')
            {
                heatmap.start = { col, row };
                elevation = 'a';
            }
            else if (elevation == 'E')
            {
                heatmap.end = { col, row };
                elevation = 'z';
            }

            heatmap.points.insert(std::make_pair( Point{ col, row }, elevation));
        }
    }

    return heatmap;
}

void HillClimbingAlgorithm::Part1(HeatMap& heatmap)
{
    Timer t;

    auto distanceGraph = GenerateDistanceGraph(heatmap);
    //Get route graph for end, and then find shortest route for the start
    std::map<Point, int> routeGraph = Dijkstra_FindEndWithShortestRoute(heatmap.end, heatmap, distanceGraph);

    std::cout << routeGraph[heatmap.start] << std::endl;
}

void HillClimbingAlgorithm::Part2(HeatMap& heatmap)
{
    Timer t;

    std::vector<Point> possibleStarts;
    std::vector<int> possibleRoutes;
    auto distanceGraph = GenerateDistanceGraph(heatmap);

    for (auto& kvp : heatmap.points)
    {
        if (kvp.second == 'a')
        {
            possibleStarts.push_back(kvp.first);
        }
    }

    //Get route graph for end, and then find shortest route for the start elevations
    std::map<Point, int> routeGraph = Dijkstra_FindEndWithShortestRoute(heatmap.end, heatmap, distanceGraph);

    for (size_t i = 0; i < possibleStarts.size(); ++i)
    {
        Point p = possibleStarts[i];
        if (routeGraph[p] > 0)  //Ignore missing elements
        {
            possibleRoutes.push_back(routeGraph[p]);
        }
    }

    auto smallestPossibleRoute = (*std::min_element(possibleRoutes.begin(), possibleRoutes.end()));

    std::cout << smallestPossibleRoute << std::endl;

}

std::map<Line, int> HillClimbingAlgorithm::GenerateDistanceGraph(HeatMap& heatmap)
{
    std::map<Line, int> distances;
    for (auto& kvp : heatmap.points)
    {
        auto point = kvp.first;
        auto currentElevation = kvp.second;
        std::vector<Point> exits = {
            { point.x, point.y - 1}, //North
            { point.x - 1, point.y},  //West
            { point.x + 1, point.y }, //East
            { point.x, point.y + 1 } //South
        };

        for (auto& exit : exits)
        {
            auto exitPoint = heatmap.points.find(exit);
            if (exitPoint == heatmap.points.end())
            {
                continue;
            }

            auto targetElevation = heatmap.points[exit];
            auto height = targetElevation - currentElevation;
            if (height >= -1)
            {
                distances.emplace(Line{ point, exit }, 1);
            }
        }
    }

    return distances;
}

std::map<Point, int> HillClimbingAlgorithm::Dijkstra_FindEndWithShortestRoute(
    Point startPosition,
    HeatMap& heatmap, 
    const std::map<Line, int>& distanceGraph)
{
    std::vector<Point> visitHistory;
    std::map<Point, int> routeGraph;
    routeGraph[startPosition] = 0;
    std::deque<Point> pointsToVisit;
    pointsToVisit.push_back(startPosition);

    do
    {
        Point currentPos = pointsToVisit.front();
        pointsToVisit.pop_front();

        std::vector<Point> exits = {
            { currentPos.x, currentPos.y - 1}, //North
            { currentPos.x - 1, currentPos.y},  //West
            { currentPos.x + 1, currentPos.y }, //East
            { currentPos.x, currentPos.y + 1} //South
        };

        auto routeDistanceSoFar = routeGraph.find(currentPos);

        //Assign route distance to all exits
        for (auto& exit : exits)
        {
            //Find the distance to this vertex
            Line vertex = { currentPos, exit };
            auto kvp = distanceGraph.find(vertex);
            if (kvp == distanceGraph.cend())
            {
                continue;
            }

            //get the current distance from start at this point
            auto routeDistance = routeGraph.find(exit);
            auto distanceToRouteFromExit = routeDistanceSoFar->second + kvp->second;

            if (routeDistance == routeGraph.end())
            {
                //Doesn't exist yet, so just enter the distance from a to b
                routeGraph.emplace(exit, routeDistanceSoFar->second + kvp->second);
            }
            else if (distanceToRouteFromExit < routeDistance->second)
            {
                //New distance is less than existing distance, so update
                routeGraph[exit] = distanceToRouteFromExit;
            }

            //If this is a valid exit, visit it next
            auto visited = std::find(visitHistory.begin(), visitHistory.end(), exit);
            auto aboutToBeVisited = std::find(pointsToVisit.begin(), pointsToVisit.end(), exit);
            if (visited == visitHistory.end() && aboutToBeVisited == pointsToVisit.end())
            {
                pointsToVisit.push_back(exit);
            }
        }

        visitHistory.push_back(currentPos);

    } while (!pointsToVisit.empty());

    return routeGraph;
}

