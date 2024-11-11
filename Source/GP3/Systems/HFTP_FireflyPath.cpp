#include "HFTP_FireflyPath.h"

#include "HFTP_ObjectiveData.h"
#include "HFTP_ObjectiveSystem.h"
#include "NiagaraComponent.h"


void UHFTP_FireflyPath::ActivatePath(const FHFTP_ObjectiveData& ObjectiveData)
{
	if(ObjectiveData.ObjectiveDataAsset == ObjectiveDataAsset)
	{
		NiagaraComponentRef->SetVisibility(true);
		return;
	}
	NiagaraComponentRef->SetVisibility(false);
}

void UHFTP_FireflyPath::BeginPlay()
{
	Super::BeginPlay();

	NiagaraComponentRef = GetOwner()->FindComponentByClass<UNiagaraComponent>();
	if (!NiagaraComponentRef)
		UE_LOG(LogTemp, Error, TEXT("Niagara Component not found in %s"), *GetOwner()->GetName());

	if (!ObjectiveDataAsset)
		UE_LOG(LogTemp, Error, TEXT("Objective Data Asset not set in %s"), *GetOwner()->GetName());

	if(!ObjectiveDataAsset->IsFirstObjective())
		NiagaraComponentRef->SetVisibility(false);

	GetOwner()->GetGameInstance()->GetSubsystem<UHFTP_ObjectiveSystem>()->OnSuccessfullyCompletedObjective.AddDynamic(this, &UHFTP_FireflyPath::ActivatePath);
}