#include "LevelManager.h"
#include "FontRenderer.h"
#include "FPSCounter.h"
#include "ImGuiComponent.h"
#include "PengoLevel.h"
#include "PengoLevelLoader.h"
#include "StartScreen.h"
#include "imgui.h"
#include "ServiceLocator.h"
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


	//#ifdef _DEBUG
		//LevelSelection
	m_pLevelSelection = new GameObject();
	const auto imgui = m_pLevelSelection->AddComponent<ImGuiComponent>();
	imgui->SetWindowName("Select Level");
	//Bind a function of a class to the imgui component (a class is this class)
	imgui->SetImGuiRenderFunction([this] {ImGuiRenderFunction(); });
	activeScene->Add(m_pLevelSelection);
	//#endif // DEBUG

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
	m_pHighScore->GetComponent<Transform>()->SetLocalPosition({ 200, 5 });
	activeScene->Add(m_pHighScore);
}

void LevelManager::ResetLevel()
{

	[[maybe_unused]] auto& audioService = ServiceLocator::GetInstance().AudioService.GetService();
#ifndef _DEBUG
	audioService.Stop(1);
#endif //_DEBUG


	auto& sceneManager = SceneManager::GetInstance();
	auto level = sceneManager.GetActiveScene();
	auto levelName = level->GetName();
	level->MarkForDeletion();

	ResetSnowbees();
	ResetLives();

	PengoLevelLoader levelLoader;
	auto& scene = SceneManager::GetInstance().CreateScene(levelName);
	PengoLevel* level01 = levelLoader.LoadLevel(levelName + ".xml");
	level01->AddGameObjectsToScene(&scene);
	sceneManager.SetActiveScene(&scene);

	AddObjectsToActiveScene();
	ResetHud();

#ifndef _DEBUG
	audioService.Play(1);
#endif
}

void LevelManager::ImGuiRenderFunction()
{
	//#ifdef _DEBUG
	ImGui::SetWindowPos({ 0,350 });
	ImGui::SetWindowSize({ 300,200 });

	const auto levelOneButton = ImGui::Button("Level1", { 80,20 });
	ImGui::SameLine();

	const auto levelTwoButton = ImGui::Button("Level2", { 80,20 });
	ImGui::SameLine();

	const auto levelThreeButton = ImGui::Button("Level3", { 80,20 });

	if (levelOneButton) LoadLevel(1);
	if (levelTwoButton) LoadLevel(2);
	if (levelThreeButton) LoadLevel(3);
	//#endif // DEBUG
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

	ServiceLocator::GetInstance().AudioService.GetService().Stop(3);
	ServiceLocator::GetInstance().AudioService.GetService().Stop(1);
	const auto& sceneManager = SceneManager::GetInstance();


	const auto activeScene = sceneManager.GetActiveScene();

	//Get the next level
	auto level = static_cast<int>(activeScene->GetName().back()) - 48;
	++level %= 4;

	LoadLevel(level);
}

void LevelManager::LoadLevel(int level)
{
	//Delete the old scene
	auto& sceneManager = SceneManager::GetInstance();
	const auto oldScene = sceneManager.GetActiveScene();
	oldScene->MarkForDeletion();

	//Reset values
	ResetSnowbees();
	ResetLives();

	//Reset the collision manager
	ServiceLocator::GetInstance().CollisionManager.GetService().Clear();


	//Load the level
	PengoLevelLoader levelLoader;
	//Create a new scene with the next level
	auto& scene = sceneManager.CreateScene("Level" + std::to_string(level));

	//Load the level
	PengoLevel* level01 = levelLoader.LoadLevel("Level" + std::to_string(level) + ".xml");

	//Add the GameObjects to the scene
	level01->AddGameObjectsToScene(&scene);

	//Set the new level as active scene
	sceneManager.SetActiveScene(&scene);

	//Add the elements
	AddObjectsToActiveScene();
	ResetHud();


	[[maybe_unused]] auto& audioService = ServiceLocator::GetInstance().AudioService.GetService();
#ifndef _DEBUG
	audioService.Play(1);
#endif
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
