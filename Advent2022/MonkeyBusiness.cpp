#include "MonkeyBusiness.h"
#include <regex>
#include <fstream>
#include <iostream>
#include <numeric>

MonkeyBusiness::Monkey::Monkey(std::shared_ptr<std::vector<Monkey>> monkeys, std::istream& iss, size_t worryDivisor)
	: m_monkeys(monkeys)
	, m_inspections(0)
	, m_worryDivisor(worryDivisor)
{
	std::string monkeyName;
	std::getline(iss, monkeyName);

	//Starting items
	std::string startingItems;
	std::getline(iss, startingItems);
	std::regex e(R"(\d+)");
	std::sregex_iterator iter(startingItems.begin(), startingItems.end(), e);
	std::sregex_iterator end;

	while (iter != end)
	{
		m_worryLevels.push_back(std::stoi(iter->str()));
		iter++;
	}

	//Operation
	std::string op_str;
	std::getline(iss, op_str);

	std::regex op_reg(R"(([*+])+)");
	std::regex num_reg(R"(([0-9])+)");
	std::smatch op_match, num_match;
	if (std::regex_search(op_str, op_match, op_reg))
	{
		if (std::regex_search(op_str, num_match, num_reg))
		{
			size_t num = std::stoi(num_match.str());
			if (op_match.str() == "*")
			{
				m_operation = [=](size_t old) -> size_t { return old * num; };
			}
			else
			{
				m_operation = [=](size_t old) -> size_t { return old + num; };
			}
		}
		else
		{
			//power operation
			m_operation = [](size_t old) -> size_t { return old * old; };
		}
	}

	//Test
	std::string test_str, monkey_true_str, monkey_false_str;
	std::smatch monkey_true_match, monkey_false_match;
	std::getline(iss, test_str);
	std::getline(iss, monkey_true_str);
	std::getline(iss, monkey_false_str);

	if (std::regex_search(test_str, num_match, num_reg) 
		&& std::regex_search(monkey_true_str, monkey_true_match, num_reg)
		&& std::regex_search(monkey_false_str, monkey_false_match, num_reg))
	{
		m_testDivisor = std::stoi(num_match.str());
		m_monkey_true_idx = std::stoi(monkey_true_match.str());
		m_monkey_false_idx = std::stoi(monkey_false_match.str());
	}

	std::string gap;
	std::getline(iss, gap);
}

void MonkeyBusiness::Monkey::AddToItems(size_t item)
{
	m_worryLevels.push_back(item);
}

void MonkeyBusiness::Monkey::Action(size_t commonModulo)
{
	for (auto& item : m_worryLevels)
	{
		item = m_operation(item);
		item /= m_worryDivisor;
		item %= commonModulo;
		m_inspections++;

		if (item % m_testDivisor == 0)
		{
			(*m_monkeys)[m_monkey_true_idx].AddToItems(item);
		}
		else
		{
			(*m_monkeys)[m_monkey_false_idx].AddToItems(item);
		}
	}

	m_worryLevels.clear(); //All items thrown to other monkeys (Single-Thread op!)
}

void MonkeyBusiness::Monkey::Report()
{
	for (auto& item : m_worryLevels)
	{
		std::cout << item << ", ";
	}
	std::cout << std::endl;
}

size_t MonkeyBusiness::Monkey::Inspections()
{
	return m_inspections;
}

size_t MonkeyBusiness::Monkey::TestDivisor()
{
	return m_testDivisor;
}

void MonkeyBusiness::PerformOperations(const std::string& filename, int rounds, size_t worryDivisor, size_t numMonkeys)
{
	std::shared_ptr<std::vector<Monkey>> monkeys = std::make_shared<std::vector<Monkey>>();

	std::ifstream is{ filename };

	if (!is)
	{
		return;
	}

	for (int i = 0; i < numMonkeys; ++i)
	{
		monkeys->emplace_back(monkeys, is, worryDivisor);
	}

	//Work out the common modulo to prevent overflows
	size_t commonModulo = std::accumulate(monkeys->begin(), monkeys->end(), (size_t)1, [&](size_t total, auto m)
		{
			return total * m.TestDivisor();
		});

	//For n number rounds, perform actions on monkeys
	for (int round = 0; round < rounds; ++round)
	{
		for (int i = 0; i < numMonkeys; ++i)
		{
			(*monkeys)[i].Action(commonModulo);
		}

		if ((round + 1) % 1000 == 0 || round == 19 || round == 0)
		{
			std::cout << "==After round " << round + 1 << "==\n";
			for (int i = 0; i < numMonkeys; ++i)
			{
				std::cout << "Monkey " << i << " inpsected items " << (*monkeys)[i].Inspections() << " times\n";
			}
		}
	}

	std::sort(monkeys->begin(), monkeys->end(), [&](auto a, auto b)
		{
			return a.Inspections() > b.Inspections();
		});

	std::cout << (*monkeys)[0].Inspections() * (*monkeys)[1].Inspections() << std::endl;
}
