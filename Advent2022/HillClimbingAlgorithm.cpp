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
    std::map<Point, int> routeGraph = Dijkstra_FindEndWithShortestRoute(heatmap.start, heatmap, distanceGraph);

    std::cout << routeGraph[heatmap.end] << std::endl;
}

void HillClimbingAlgorithm::Part2(HeatMap& heatmap)
{
    Timer t;

    std::vector<std::pair<Point, char>> possibleStarts;
    std::vector<int> possibleRoutes;
    auto distanceGraph = GenerateDistanceGraph(heatmap);

    std::copy_if(heatmap.points.begin(), heatmap.points.end(), std::back_inserter(possibleStarts), [&](auto& kvp)
        {
            return kvp.second == 'a';
        });

    for (size_t i = 0; i < possibleStarts.size(); ++i)
    {
        Point p = possibleStarts[i].first;

        std::map<Point, int> routeGraph = Dijkstra_FindEndWithShortestRoute(p, heatmap, distanceGraph);
        if (routeGraph[heatmap.end] > 0)
        {
            possibleRoutes.push_back(routeGraph[heatmap.end]);
        }
    }

    auto smallestPossibleRoute = (*std::min_element(possibleRoutes.begin(), possibleRoutes.end()));

    std::cout << smallestPossibleRoute << std::endl;

}

std::map<Vertex, int> HillClimbingAlgorithm::GenerateDistanceGraph(HeatMap& heatmap)
{
    std::map<Vertex, int> distances;
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
            if (height <= 1)
            {
                distances.emplace(Vertex{ point, exit }, 1);
            }
        }
    }

    return distances;
}

std::map<Point, int> HillClimbingAlgorithm::Dijkstra_FindEndWithShortestRoute(
    Point startPosition,
    HeatMap& heatmap, 
    const std::map<Vertex, int>& distanceGraph)
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
            Vertex vertex = { currentPos, exit };
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

