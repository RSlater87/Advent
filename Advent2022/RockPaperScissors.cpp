#include "RockPaperScissors.h"
#include "../AdventUtility/Utilities.h"
#include <stdexcept>
#include <iterator>
#include <numeric>
#include <iostream>

std::vector<RockPaperScissors::Match> RockPaperScissors::ParseMatches(const std::string& filename)
{
	std::vector<RockPaperScissors::Match> inputs;

	auto allLines = ReadAllText(filename);

	auto splitLines = SplitString(allLines, "\n");

	for (const auto& line : splitLines)
	{
		if (line.empty())
			continue;

		inputs.push_back(ParseMatch(line));
	}

	return inputs;
}

std::vector<RockPaperScissors::RightStrategy> RockPaperScissors::ParseStrategies(const std::string& filename)
{
	std::vector<RockPaperScissors::RightStrategy> inputs;

	auto allLines = ReadAllText(filename);

	auto splitLines = SplitString(allLines, "\n");

	for (const auto& line : splitLines)
	{
		if (line.empty())
			continue;

		inputs.push_back(ParseStrategy(line));
	}

	return inputs;
}

RockPaperScissors::RightStrategy RockPaperScissors::ParseStrategy(const std::string& line)
{
	auto parts = SplitString(line, " ");
	RightStrategy result{};

	if (parts[0] == "A")
	{
		result.opponent = Choice::Rock;
	}
	else if (parts[0] == "B")
	{
		result.opponent = Choice::Paper;
	}
	else if (parts[0] == "C")
	{
		result.opponent = Choice::Scissors;
	}

	if (parts[1] == "X")
	{
		result.aim = Result::Lose;
	}
	else if (parts[1] == "Y")
	{
		result.aim = Result::Draw;
	}
	else if (parts[1] == "Z")
	{
		result.aim = Result::Win;
	}

	return result;
}

RockPaperScissors::Match RockPaperScissors::ParseMatch(const std::string& line)
{
	auto parts = SplitString(line, " ");
	Match result{};

	if (parts[0] == "A")
	{
		result.opponent = Choice::Rock;
	}
	else if (parts[0] == "B")
	{
		result.opponent = Choice::Paper;
	}
	else if (parts[0] == "C")
	{
		result.opponent = Choice::Scissors;
	}

	if (parts[1] == "X")
	{
		result.player = Choice::Rock;
	}
	else if (parts[1] == "Y")
	{
		result.player = Choice::Paper;
	}
	else if (parts[1] == "Z")
	{
		result.player = Choice::Scissors;
	}

	return result;
}

int RockPaperScissors::GetScore(Choice choice)
{
	switch (choice)
	{
	case RockPaperScissors::Choice::Rock:
		return 1;
	case RockPaperScissors::Choice::Paper:
		return 2;
	case RockPaperScissors::Choice::Scissors:
		return 3;
	default:
		//Shouldn't reach here
		throw std::logic_error("Oops");
	}
}

int RockPaperScissors::CalculateScoreForMatch(Match strat)
{
	//Ties
	if (strat.player == strat.opponent)
	{
		return GetScore(strat.player) + 3;
	}

	//Wins
	if ((strat.player == Choice::Rock && strat.opponent == Choice::Scissors)
		|| (strat.player == Choice::Scissors && strat.opponent == Choice::Paper)
		|| (strat.player == Choice::Paper && strat.opponent == Choice::Rock))
	{
		return GetScore(strat.player) + 6;
	}

	//Loses
	if ((strat.player == Choice::Rock && strat.opponent == Choice::Paper)
		|| (strat.player == Choice::Scissors && strat.opponent == Choice::Rock)
		|| (strat.player == Choice::Paper && strat.opponent == Choice::Scissors))
	{
		return GetScore(strat.player);
	}

	//Shouldn't reach here
	throw std::logic_error("Oops");
}

int RockPaperScissors::CalculateScoreForRightStrategy(RightStrategy strat)
{
	//Ties
	if (strat.aim == Result::Draw)
	{
		return CalculateScoreForMatch(Match{ strat.opponent, strat.opponent });
	}

	//Wins
	if (strat.aim == Result::Win)
	{
		switch (strat.opponent)
		{
			case Choice::Rock:
				return CalculateScoreForMatch(Match{ Choice::Paper, strat.opponent });

			case Choice::Paper:
				return CalculateScoreForMatch(Match{ Choice::Scissors, strat.opponent });

			case Choice::Scissors:
				return CalculateScoreForMatch(Match{ Choice::Rock, strat.opponent });
		default:
			break;

		}
	}

	//lose
	if (strat.aim == Result::Lose)
	{
		switch (strat.opponent)
		{
		case Choice::Rock:
			return CalculateScoreForMatch(Match{ Choice::Scissors, strat.opponent });

		case Choice::Paper:
			return CalculateScoreForMatch(Match{ Choice::Rock, strat.opponent });

		case Choice::Scissors:
			return CalculateScoreForMatch(Match{ Choice::Paper, strat.opponent });
		default:
			break;

		}
	}

	return 0;
}

int RockPaperScissors::CalculateTotalScore_Part1(const std::vector<Match>& strategies)
{
	std::vector<int> scores;
	std::transform(strategies.cbegin(), strategies.cend(), std::back_inserter(scores), CalculateScoreForMatch);

	return std::accumulate(scores.cbegin(), scores.cend(), 0);
}

int RockPaperScissors::CalculateTotalScore_Part2(const std::vector<RightStrategy>& strategies)
{
	std::vector<int> scores;
	std::transform(strategies.cbegin(), strategies.cend(), std::back_inserter(scores), CalculateScoreForRightStrategy);

	return std::accumulate(scores.cbegin(), scores.cend(), 0);
}

void RockPaperScissors::Part1(const std::vector<Match>& strategies)
{
	std::cout << CalculateTotalScore_Part1(strategies) << std::endl;
}

void RockPaperScissors::Part2(const std::vector<RightStrategy>& strategies)
{
	std::cout << CalculateTotalScore_Part2(strategies) << std::endl;
}
