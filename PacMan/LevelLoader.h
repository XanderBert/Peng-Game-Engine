#pragma once
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


	static void LoadInterSections(Scene& scene);
	static void LoadWalls(Scene& scene);
	static void LoadPowerUps(Scene& scene);
	static void LoadGhosts(Scene& scene);
	static void LoadHud(Scene& scene);
	static void LoadPacDot(Scene& scene);
	static void LoadPacMan(Scene& scene, int amount);

	static void SaveHighScore();

	inline static std::vector<GameObject*> m_pGhosts{};
	inline static int m_LevelId{};
	inline static int m_AmountOfLevels{ 3 };
	inline static GameMode m_GameMode{ GameMode::SinglePlayer };
	inline static std::vector<int> m_NewHighScores{};
	inline static std::vector<int> m_AllHighScores{};
};