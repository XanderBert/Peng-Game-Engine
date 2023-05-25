#pragma once
#include "Observer.h"
#include "GameObject.h"
#include <string>

class Achievement : public Observer
{
public:
	virtual void Notify(GameObject*, GameEvent) override;

private:
	enum class EAchievements
	{
		ACH_WIN_ONE_GAME,
		ACH_WIN_100_GAMES,
		ACH_TRAVEL_FAR_ACCUM,
		ACH_TRAVEL_FAR_SINGLE,
	};

	const std::pair<EAchievements, std::string> achievemtPair[4] =
	{
		{EAchievements::ACH_WIN_ONE_GAME, "ACH_WIN_ONE_GAME"},
		{EAchievements::ACH_WIN_100_GAMES, "ACH_WIN_100_GAMES"},
		{EAchievements::ACH_TRAVEL_FAR_ACCUM, "ACH_TRAVEL_FAR_ACCUM"},
		{EAchievements::ACH_TRAVEL_FAR_SINGLE, "ACH_TRAVEL_FAR_SINGLE"}
	};

	std::string AchievementToString(EAchievements achievements)
	{
		for (const auto& pair : achievemtPair)
		{
			if (pair.first == achievements)
			{
				return pair.second;
			}
		}
		return "UNKNOWN";
	}


	void Unlock(EAchievements /*achievement*/)
	{
		/*steamUserStats->RequestCurrentStats();
		steamUserStats->SetAchievement(AchievementToString(achievement).c_str());
		steamUserStats->StoreStats();*/
	}
};