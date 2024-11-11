#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HFTP_PhotoWidget.generated.h"

UCLASS(Abstract)
class GP3_API UHFTP_PhotoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Photo")
	TObjectPtr<UTextureRenderTarget2D> PhotoTexture{};
};
