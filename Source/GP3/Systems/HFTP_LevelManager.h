#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HFTP_LevelManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAllLevelsLoaded);
DECLARE_MULTICAST_DELEGATE(FOnAllLevelsUnloaded);

UCLASS(Abstract)
class AHFTP_LevelManager : public AActor
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void LoadMainMenuLevel();

	UFUNCTION(BlueprintCallable)
	void LoadAllLevels();
	
	UFUNCTION()
	void LoadLevel(TArray<FName> LevelsToLoad);

	UFUNCTION()
	void UnloadCurrentLevel(TArray<FName> LevelsToUnload);

	void SetLevels(const TArray<FName>& LevelsToSet) { Levels = LevelsToSet; }

	FOnAllLevelsLoaded OnAllLevelsLoaded;
	FOnAllLevelsUnloaded OnAllLevelsUnloaded;

private:
	UFUNCTION()
	void OnLevelLoaded();

	UFUNCTION()
	void OnLevelUnloaded();

	UPROPERTY()
	int32 LevelLoadIndex = 0;

	UPROPERTY()
	int32 LevelUnloadIndex = 0;

	UPROPERTY()
	TArray<FName> Levels;
};