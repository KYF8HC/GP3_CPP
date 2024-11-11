#include "HFTP_SketchesMenuRightPage.h"
#include "Components/TextBlock.h"
#include "GP3/Systems/HFTP_ObjectiveSystem.h"

void UHFTP_SketchesMenuRightPage::Init(ABookMenuActor* InBookMenuActor, int32 InPageSectionIndex, int32 InPageIndex)
{
	SketchTitle->SetVisibility(ESlateVisibility::Hidden);
	SketchDesc->SetVisibility(ESlateVisibility::Hidden);

	ObjectiveSystemRef = GetGameInstance()->GetSubsystem<UHFTP_ObjectiveSystem>();
	ObjectiveSystemRef->OnSuccessfullyCompletedObjective.AddDynamic(this, &UHFTP_SketchesMenuRightPage::OnObjectiveCompleted);
	ObjectiveSystemRef->OnRestartGame.AddDynamic(this, &UHFTP_SketchesMenuRightPage::OnRestartGame);
	Super::Init(InBookMenuActor, InPageSectionIndex, InPageIndex);
}

void UHFTP_SketchesMenuRightPage::OnObjectiveCompleted(const FHFTP_ObjectiveData& ObjectiveData)
{
	if(ObjectiveRef == ObjectiveData.ObjectiveDataAsset)
	{
		SketchTitle->SetVisibility(ESlateVisibility::Visible);
		SketchDesc->SetVisibility(ESlateVisibility::Visible);
	}
}

void UHFTP_SketchesMenuRightPage::OnRestartGame()
{
	SketchTitle->SetVisibility(ESlateVisibility::Hidden);
	SketchDesc->SetVisibility(ESlateVisibility::Hidden);
}
