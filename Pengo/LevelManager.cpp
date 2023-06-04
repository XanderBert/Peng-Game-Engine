#include "LevelManager.h"
#include "FontRenderer.h"
#include "FPSCounter.h"
#include "PengoLevel.h"
#include "PengoLevelLoader.h"
#include "StartScreen.h"
#include "TextureRenderer.h"
#include "Transform.h"

class FontRenderer;

LevelManager::LevelManager()
{

}

void LevelManager::AddScore(int score)
{
	m_Score += score;
	m_pScoreObject->GetComponent<FontRenderer>()->SetText("Score: " + std::to_string(m_Score));

	if (m_Score >= m_HighScore)
	{
		m_HighScore = m_Score;
		m_pScoreObject->GetComponent<FontRenderer>()->SetText("High Score: " + std::to_string(m_HighScore));
	}
}

void LevelManager::AddObjectsToActiveScene()
{
	auto* activeScene = SceneManager::GetInstance().GetActiveScene();

	//FPS Counter
	m_Fps = new GameObject();
	const auto fpsCounter{ m_Fps->AddComponent<FPSCounter>() };
	const auto transComponentFPS{ m_Fps->GetComponent<Transform>() };
	transComponentFPS->SetLocalPosition({ 5, 5 });
	const auto fontRendererFPS = m_Fps->AddComponent<FontRenderer>();
	fontRendererFPS->SetFont("Fonts/8BitDragon.ttf", 16);
	activeScene->Add(m_Fps);

	//Score
	m_pScoreObject = new GameObject();
	const auto font = m_pScoreObject->AddComponent<FontRenderer>();
	font->SetFont("Fonts/8BitDragon.ttf", 10);
	font->SetText("Score: 0");
	m_pScoreObject->GetComponent<Transform>()->SetLocalPosition({ 50, 5 });
	activeScene->Add(m_pScoreObject);

	//Highscore
	m_pHighScore = new GameObject();
	const auto font2 = m_pHighScore->AddComponent<FontRenderer>();
	font2->SetFont("Fonts/8BitDragon.ttf", 10);
	font2->SetText("High Score: 0");
	m_pHighScore->GetComponent<Transform>()->SetLocalPosition({ 100, 5 });
	activeScene->Add(m_pHighScore);
}

void LevelManager::ResetLevel()
{
	auto& sceneManager = SceneManager::GetInstance();
	auto level = sceneManager.GetActiveScene();
	auto levelName = level->GetName();

	sceneManager.SetActiveScene(sceneManager.GetSceneByName("Level0"));

	level->MarkForDeletion();

	m_AmountOfSnowBees = 0;
	m_amountOfLives = 3;

	PengoLevelLoader levelLoader;
	auto& scene = SceneManager::GetInstance().CreateScene(levelName);
	PengoLevel* level01 = levelLoader.LoadLevel(levelName + ".xml");
	level01->AddGameObjectsToScene(&scene);
	sceneManager.SetActiveScene(&scene);



	AddObjectsToActiveScene();
	ResetHud();
}

void LevelManager::ResetHud()
{
	m_pScoreObject->GetComponent<FontRenderer>()->SetText("Score: 0");
	m_pHighScore->GetComponent<FontRenderer>()->SetText("High Score: " + std::to_string(m_HighScore));
	m_Score = 0;
}

void LevelManager::AddStartScreen()
{
	auto& Startscene = SceneManager::GetInstance().CreateScene("Level0");
	StartScreen* start = new StartScreen();
	Startscene.Add(start);
	SceneManager::GetInstance().SetActiveScene(&Startscene);
}


void LevelManager::LoadNextLevel()
{
	auto& sceneManager = SceneManager::GetInstance();
	auto level = static_cast<int>(sceneManager.GetActiveScene()->GetName().back()) - 48;
	++level %= 4;

	PengoLevelLoader levelLoader;
	auto& scene = SceneManager::GetInstance().CreateScene("Level" + std::to_string(level));
	PengoLevel* level01 = levelLoader.LoadLevel("Level" + std::to_string(level) + ".xml");

	level01->AddGameObjectsToScene(&scene);


	sceneManager.SetActiveScene(sceneManager.GetSceneByName("Level" + std::to_string(level)));
	AddObjectsToActiveScene();
	ResetHud();
}

void LevelManager::SetAmountOfPlayers(int amountOfPlayers)
{
	m_AmountOfPlayers = amountOfPlayers;
}

void LevelManager::PlayerDied()
{
	--m_AmountOfPlayers;

	if (m_AmountOfPlayers <= 0 && m_GameMode != GameMode::Versus)
	{
		ResetLevel();
	}

	if (m_AmountOfPlayers == 1 && m_GameMode == GameMode::Versus)
	{
		LoadNextLevel();
	}
}

void LevelManager::SnowBeeDied()
{
	--m_AmountOfSnowBees;

	if (m_AmountOfSnowBees <= 0)
	{
		LoadNextLevel();
	}
}
