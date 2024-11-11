#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HFTP_PlayerDeathAnimActor.generated.h"

class AHFTP_GameMode;

UCLASS(Abstract)
class GP3_API AHFTP_PlayerDeathAnimActor : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeathAnimation();

	void SetGameModeRef(AHFTP_GameMode* GameMode) noexcept { GameModeRef = GameMode; }
private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Death Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AHFTP_GameMode>	GameModeRef{};
};
