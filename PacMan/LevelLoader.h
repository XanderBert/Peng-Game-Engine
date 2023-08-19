#pragma once
#include <rapidxml.hpp>

#include "Observer.h"
#include "Scene.h"
#include "Singleton.h"
enum class GameMode
{
	SinglePlayer,
	Vs,
	CoOp
};


class LevelLoader final : public Singleton<LevelLoader>
{
public:
	static Scene* LoadLevel(const int levelId, GameMode gameMode);
	static Scene* LoadLevel(const int levelId);
	static Scene* LoadNextLevel();

	static void LoadStartScene();
	static Scene* LoadEndingScreen();

	static int GetLevelId() { return m_LevelId; }

	static GameMode GetGameMode() { return m_GameMode; }

private:
	friend class Singleton<LevelLoader>;
	LevelLoader() = default;


	static void LoadGhosts(Scene& scene);
	static void LoadHud(Scene& scene);
	static void LoadPacMan(Scene& scene, int amount);

	static void SaveHighScore();
	static std::vector<int> LoadExistingHighScores();

	static void LoadLevelData(Scene& scene);
	static void LoadWallsFromFile(Scene& scene, const rapidxml::xml_node<>* rootNode);
	static void LoadIntersectionsFromFile(Scene& scene, const rapidxml::xml_node<>* rootNode);
	static void LoadPowerPalletsFromFile(Scene& scene, const rapidxml::xml_node<>* rootNode);
	static void LoadPacDotsFromFile(Scene& scene, const rapidxml::xml_node<>* rootNode);


	inline static std::vector<GameObject*> m_pGhosts{};
	inline static int m_LevelId{};
	inline static int m_AmountOfLevels{ 3 };
	inline static GameMode m_GameMode{ GameMode::SinglePlayer };
	inline static std::vector<int> m_NewHighScores{};
	inline static std::vector<int> m_AllHighScores{};
	inline static std::vector<std::unique_ptr<Observer>> m_Observers;
};