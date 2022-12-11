#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>

namespace DirectorySearch
{
	//Node for our directory tree
	//Contains type, name, filesize, a cached size of children (for directories) and a list of leaves
	
	struct TreeNode
	{
		public:
		std::shared_ptr<TreeNode> parent;
		size_t index;
		bool isDirectory;
		std::string filePath;
		std::string fileName;
		size_t fileSize;
		std::vector<std::shared_ptr<TreeNode>> children;

		TreeNode(std::shared_ptr<TreeNode> _parent,
		size_t _index,
		bool _isDirectory,
		std::string _path,
		std::string _name,
		size_t _fileSize)
			: parent(_parent)
			, index(_index)
			, isDirectory(_isDirectory)
			, filePath(_path)
			, fileName(_name)
			, fileSize(_fileSize)
			, children({})
		{

		}
	};

	void SanityCheck(std::shared_ptr<TreeNode> tree, std::map<std::string, size_t> directorySizes);

	std::shared_ptr<TreeNode> LoadDirectoryStructure(const std::string& filename);

	void Recursive_DirectorySizes(std::shared_ptr<TreeNode> tree, std::map<std::string, size_t>& directorySizes);

	void Part1(std::shared_ptr<TreeNode> tree);

	void Part2(std::shared_ptr<TreeNode> tree);
}