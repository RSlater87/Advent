#pragma once

#include <vector>
#include <string>

namespace RockPaperScissors
{
	enum class Choice
	{
		Rock,
		Paper,
		Scissors,
	};

	enum class Result
	{
		Lose,
		Draw,
		Win
	};

	struct Match
	{
		Choice player;
		Choice opponent;
	};

	struct RightStrategy
	{
		Choice opponent;
		Result aim;
	};

	std::vector<Match> ParseMatches(const std::string& filename);
	std::vector<RightStrategy> ParseStrategies(const std::string& filename);
	Match ParseMatch(const std::string& line);
	RightStrategy ParseStrategy(const std::string& line);

	int GetScore(Choice choice);
	int CalculateScoreForMatch(Match strat);
	int CalculateScoreForRightStrategy(RightStrategy strat);
	int CalculateTotalScore_Part1(const std::vector<Match>& strategies);
	int CalculateTotalScore_Part2(const std::vector<RightStrategy>& strategies);

	void Part1(const std::vector<Match>& strategies);

	void Part2(const std::vector<RightStrategy>& strategies);

}