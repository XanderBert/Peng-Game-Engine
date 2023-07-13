#pragma once
#include <functional>
#include <string>
#include <glm/vec2.hpp>


class Minigin
{
public:
	explicit Minigin(const std::string& dataPath, const glm::vec2 windowSize, const std::string& windowName);
	~Minigin();
	void Run(const std::function<void()>& load);

	Minigin(const Minigin& other) = delete;
	Minigin(Minigin&& other) = delete;
	Minigin& operator=(const Minigin& other) = delete;
	Minigin& operator=(Minigin&& other) = delete;
private:
	const float fixedTimeMStep{};

};
