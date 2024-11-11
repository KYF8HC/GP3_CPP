#include "HFTP_LevelManager.h"
#include "Kismet/GameplayStatics.h"

void AHFTP_LevelManager::LoadAllLevels()
{
	LoadLevel(Levels);
}

void AHFTP_LevelManager::LoadLevel(TArray<FName> LevelsToLoad)
{
	LevelLoadIndex = 0;
	for (int32 i = 0; i < LevelsToLoad.Num(); ++i)
	{
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.UUID = i;
		LatentInfo.ExecutionFunction = FName("OnLevelLoaded");
		LatentInfo.Linkage = i;
		
		UGameplayStatics::LoadStreamLevel(this, LevelsToLoad[i], true, true, LatentInfo);
		UE_LOG(LogTemp, Log, TEXT("%s Level loading started"), *LevelsToLoad[i].ToString());
	}
}

void AHFTP_LevelManager::UnloadCurrentLevel(TArray<FName> LevelsToUnload)
{
	LevelUnloadIndex = 0;
	for (int32 i = 0; i < LevelsToUnload.Num(); ++i)
	{
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.UUID = i;
		LatentInfo.ExecutionFunction = FName("OnLevelUnloaded");
		LatentInfo.Linkage = 0;
		
		UGameplayStatics::UnloadStreamLevel(this, LevelsToUnload[i], LatentInfo, true);
		UE_LOG(LogTemp, Log, TEXT("%s Level unloading started"), *LevelsToUnload[i].ToString());
	}
}

void AHFTP_LevelManager::OnLevelLoaded()
{
	LevelLoadIndex++;
	if (LevelLoadIndex == Levels.Num())
	{
		UE_LOG(LogTemp, Log, TEXT("All levels loaded"));
		OnAllLevelsLoaded.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s Level loaded"), *Levels[LevelLoadIndex - 1].ToString());
	}
}

void AHFTP_LevelManager::OnLevelUnloaded()
{
	LevelUnloadIndex++;
	if (LevelUnloadIndex == Levels.Num())
	{
		UE_LOG(LogTemp, Log, TEXT("All levels unloaded"));
		LoadMainMenuLevel();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s Level unloaded"), *Levels[LevelUnloadIndex - 1].ToString());
	}
}
