#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HFTP_FireflyPath.generated.h"

struct FHFTP_ObjectiveData;
class UHFTP_ObjectiveDataAsset;
class UNiagaraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP3_API UHFTP_FireflyPath : public UActorComponent
{
	GENERATED_BODY()

	UFUNCTION()
	void ActivatePath(const FHFTP_ObjectiveData& ObjectiveData);

protected:
	virtual void BeginPlay() override;
private:

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComponentRef{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Firefly Path", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHFTP_ObjectiveDataAsset> ObjectiveDataAsset{};
};