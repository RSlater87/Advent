#pragma once

#include <vector>
#include <memory>
#include <sstream>
#include <functional>

namespace MonkeyBusiness
{
	typedef std::function<size_t(size_t)> Operation;

	class Monkey
	{
	public:
		Monkey(std::shared_ptr<std::vector<Monkey>> monkeys, std::istream& iss, size_t worryDivisor);

		void AddToItems(size_t item);

		void Action(size_t commonModulo);
		void Report();

		size_t Inspections();
		size_t TestDivisor();

	private:

		std::shared_ptr<std::vector<Monkey>> m_monkeys;	//The global list of monkeys, passing items to each other

		std::vector<size_t> m_worryLevels;
		Operation m_operation;

		int m_testDivisor;
		int m_monkey_true_idx;
		int m_monkey_false_idx;
		size_t m_worryDivisor;
		size_t m_inspections;
	};

	void PerformOperations(const std::string& filename, int rounds, size_t worryDivisor, size_t numMonkeys);
}