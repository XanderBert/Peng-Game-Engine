#pragma once
#include <string>
#include <functional>
#include <glm/fwd.hpp>

class Minigin
{
public:
	explicit Minigin(const std::string& dataPath, const glm::vec<2, glm::uint> windowSize);
	~Minigin();
	void Run(const std::function<void()>& load);

	Minigin(const Minigin& other) = delete;
	Minigin(Minigin&& other) = delete;
	Minigin& operator=(const Minigin& other) = delete;
	Minigin& operator=(Minigin&& other) = delete;
private:
	const float fixedTimeStep{};

};
