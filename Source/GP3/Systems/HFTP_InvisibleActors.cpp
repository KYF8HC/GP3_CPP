#include "HFTP_InvisibleActors.h"
#include "HFTP_GameMode.h"
#include "HFTP_Player.h"
#include "Components/DecalComponent.h"
#include "Components/MaterialBillboardComponent.h"

void UHFTP_InvisibleActors::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<AHFTP_GameMode>(GetWorld()->GetAuthGameMode());
	if (GameModeRef)
		PlayerRef = GameModeRef->GetPlayer();
	else
		UE_LOG(LogTemp, Error, TEXT("AHFTP_InvisibleActors: GameModeRef is nullptr in %s"), *GetName());

	PlayerRef->OnCaptureScene.AddUObject(this, &UHFTP_InvisibleActors::SetVisibility);

	SetupRenderReferences();
}

void UHFTP_InvisibleActors::SetupRenderReferences()
{
	switch (ActorType)
	{
	case EActorType::Mesh:
		GetOwner()->GetComponents<UStaticMeshComponent>(MeshesToSet);
		for (auto Mesh : MeshesToSet)
			Mesh->SetVisibility(false);
		break;
	case EActorType::Eyes:
		GetOwner()->GetComponentByClass<UMaterialBillboardComponent>()->SetVisibility(false);
		break;
	case EActorType::BloodSplatter:
		GetOwner()->GetComponentByClass<UDecalComponent>()->SetVisibility(false);
		break;
	default:
		break;
	}
}

void UHFTP_InvisibleActors::SetVisibility(bool bVisible)
{
	switch (ActorType)
	{
	case EActorType::Mesh:
		for (auto Mesh : MeshesToSet)
			Mesh->SetVisibility(bVisible);
		break;
	case EActorType::Eyes:
		GetOwner()->GetComponentByClass<UMaterialBillboardComponent>()->SetVisibility(bVisible);
		break;
	case EActorType::BloodSplatter:
		GetOwner()->GetComponentByClass<UDecalComponent>()->SetVisibility(bVisible);
		break;
	default:
		break;
	}
}
