#include "DirectorySearch.h"
#include "../AdventUtility/Utilities.h"
#include <map>
#include <numeric>
#include <iostream>

void DirectorySearch::SanityCheck(std::shared_ptr<TreeNode> tree, std::map<std::string, size_t> directorySizes)
{
	for (auto child : tree->children)
	{
		std::cout
			<< child->filePath << " "
			<< (child->isDirectory ? "dir " : "file ")
			<< (child->isDirectory ? directorySizes[child->filePath] : child->fileSize) << std::endl;
		SanityCheck(child, directorySizes);
	}
}

std::shared_ptr<DirectorySearch::TreeNode> DirectorySearch::LoadDirectoryStructure(const std::string& filename)
{
	std::string allText = ReadAllText(filename);

	auto allLines = SplitString(allText, "\n");

	std::shared_ptr<DirectorySearch::TreeNode> root, current;

	size_t directories = 0, files = 0;

	for (auto& line : allLines)
	{
		if (line == "$ cd /")
		{
			//Special case - initialise root
			root = std::make_shared<TreeNode>(nullptr, 0, true, "\\", "\\", 0);
			directories++;
			current = root;
		}
		else if (line == "$ cd ..")
		{
			//Special case - go up one
			current = current->parent;
		}
		else if (line.substr(0, 4) == "$ cd")
		{
			//Go down to the child folder with this name
			for (auto& child : current->children)
			{
				if (child->fileName == line.substr(5))
				{
					current = child;
					break;
				}
			}
		}
		else if (line == "$ ls")
		{
			//do nothing
		}
		else if(line.substr(0, 3) == "dir")
		{
			//Create a new child directory
			std::string fullPath = current->filePath + "\\" + line.substr(4);
			std::shared_ptr<TreeNode> baby = std::make_shared<TreeNode>(current, directories, true, fullPath, line.substr(4), 0);
			current->children.push_back(baby);
			directories++;
		}
		else
		{
			//Create a new child file
			auto parts = SplitString(line, " ");
			size_t fileSize = std::stoi(parts[0]);
			std::string fileName = parts[1];
			std::string fullPath = current->filePath + "\\" + fileName;
			std::shared_ptr<TreeNode> baby = std::make_shared<TreeNode>(current, files, false, fullPath, fileName, fileSize);
			current->children.push_back(baby);
			files++;
		}
	}

	std::cout << directories << ", " << files << std::endl;

	return root;
}

void DirectorySearch::Recursive_DirectorySizes(std::shared_ptr<DirectorySearch::TreeNode> tree, std::map<std::string, size_t>& directorySizes)
{
	//Do a depth-first search of the tree to get filesizes
	for (auto child : tree->children)
	{
		if (child->isDirectory)
		{
			Recursive_DirectorySizes(child, directorySizes);
			directorySizes[tree->filePath] += directorySizes[child->filePath];
		}
		else
		{
			directorySizes[tree->filePath] += child->fileSize;
		}
	}
}

void DirectorySearch::Part1(std::shared_ptr<TreeNode> tree)
{
	//Do a depth-first search of the tree to get filesizes
	std::map<std::string, size_t> directorySizes;
	Recursive_DirectorySizes(tree, directorySizes);

	//Then scan through the map to get all directories < 100,000
	std::vector<std::pair<std::string, size_t>> smallDirectories;
	std::copy_if(directorySizes.cbegin(), directorySizes.cend(), std::back_inserter(smallDirectories), [&](auto& kvp)
		{
			return kvp.second <= 100000;
		});

	size_t answer = std::accumulate(smallDirectories.begin(), smallDirectories.end(), (size_t)0, [&](size_t total, auto& kvp)
		{
			return total + kvp.second;
		});

	SanityCheck(tree, directorySizes);

	std::cout << answer << std::endl;
}

void DirectorySearch::Part2(std::shared_ptr<TreeNode> tree)
{
	//Do a depth-first search of the tree to get filesizes
	std::map<std::string, size_t> directorySizes;
	Recursive_DirectorySizes(tree, directorySizes);

	auto total = directorySizes["\\"];
	auto unused = 70000000 - total;
	auto toDelete = 30000000 - unused;

	//Then scan through the map to get all directories > toDelete
	std::vector<std::pair<std::string, size_t>> deleteCandidates;
	std::copy_if(directorySizes.cbegin(), directorySizes.cend(), std::back_inserter(deleteCandidates), [&](auto& kvp)
		{
			return kvp.second >= toDelete;
		});

	//Get smallest candidate
	auto answer = (std::min_element(deleteCandidates.cbegin(), deleteCandidates.cend(), [&](auto& a, auto& b)
		{
			return a.second < b.second;
		}));

	std::cout << answer->second << std::endl;
}
