#pragma once
#include <functional>
#include <vector>
#include "GameObject.h"
#include "Singleton.h"

enum class GameMode
{
	SinglePlayer,
	CoOp,
	Versus
};

class LevelManager final : public Singleton<LevelManager>
{
public:
	~LevelManager() = default;

	LevelManager(const LevelManager& other) = delete;
	LevelManager(LevelManager&& other) noexcept = delete;
	LevelManager& operator=(const LevelManager& other) = delete;
	LevelManager& operator=(LevelManager&& other) noexcept = delete;

	void SetGameMode(GameMode gameMode) { m_GameMode = gameMode; }
	GameMode GetGameMode() { return m_GameMode; }

	void AddScore(int score);
	void ResetHud();

	void AddStartScreen();
	void LoadNextLevel();
	void LoadLevel(int level);

	void SetAmountOfPlayers(int amountOfPlayers);
	int GetAmountOfPlayers() const { return m_AmountOfPlayers; }

	void SetAmountOfSnowBees(int amountOfSnowBees) { m_AmountOfSnowBees = amountOfSnowBees; }
	int GetAmountOfSnowBees() const { return m_AmountOfSnowBees; }
	void IncrementAmountOfSnowBees() { ++m_AmountOfSnowBees; }

	void PlayerDied();
	void SnowBeeDied();


private:
	LevelManager();
	friend class Singleton<LevelManager>;

	void AddObjectsToActiveScene();
	void ResetLevel();
	void ResetSnowbees() { m_AmountOfSnowBees = 0; }
	void ResetLives() { m_amountOfLives = 3; }

	GameObject* m_pScoreObject{};
	GameObject* m_pHighScore{};
	GameObject* m_pLives{};
	GameObject* m_Fps{};
	GameObject* m_pLevelSelection{};




	int m_Score{};
	int m_HighScore{};
	int m_AmountOfPlayers{};
	int m_amountOfLives{};
	int m_AmountOfSnowBees{};

	GameMode m_GameMode{ GameMode::SinglePlayer };


	void ImGuiRenderFunction();

};
