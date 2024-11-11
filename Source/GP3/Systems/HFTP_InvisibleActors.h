#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HFTP_InvisibleActors.generated.h"

class UStaticMeshComponent;
class AHFTP_GameMode;
class AHFTP_Player;

UENUM()
enum class EActorType
{
	Mesh,
	Eyes,
	BloodSplatter,
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP3_API UHFTP_InvisibleActors : public UActorComponent
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

private:
	
	TObjectPtr<AHFTP_GameMode> GameModeRef{};
	TObjectPtr<AHFTP_Player> PlayerRef{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Invisible Actors", meta = (AllowPrivateAccess = "true"))
	EActorType ActorType = EActorType::Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Invisible Actors", meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> MeshesToSet{};

	//FUNCTIONS
	void SetupRenderReferences();
	void SetVisibility(bool bVisible);
};
