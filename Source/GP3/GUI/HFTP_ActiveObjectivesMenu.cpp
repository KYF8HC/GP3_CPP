#include "HFTP_ActiveObjectivesMenu.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GP3/Systems/HFTP_ObjectiveSystem.h"

void UHFTP_ActiveObjectivesMenu::InitializeMenu()
{
	Super::InitializeMenu();
	ObjectiveSystemRef = GetGameInstance()->GetSubsystem<UHFTP_ObjectiveSystem>();
	if (ObjectiveSystemRef)
		ObjectiveSystemRef->OnUpdateObjectiveList.AddUObject(this, &UHFTP_ActiveObjectivesMenu::UpdateMenu);
	else
		UE_LOG(LogTemp, Error, TEXT("UActiveObjectivesMenu: ObjectiveSystemRef is nullptr"));

	UpdateMenu();
}

void UHFTP_ActiveObjectivesMenu::UpdateMenu()
{
	if (ObjectiveSystemRef)
	{
		ObjectiveList->ClearChildren();
		for (const auto& Objective : ObjectiveSystemRef->GetActiveObjectives())
		{
			UTextBlock* TextBlock = NewObject<UTextBlock>(ObjectiveList);
			TextBlock->SetText(Objective.ObjectiveDataAsset->GetObjectiveTitle());

			FSlateFontInfo FontInfo = TextBlock->GetFont();
			FontInfo.Size = 14;
			
			TextBlock->SetFont(FontInfo);
			ObjectiveList->AddChildToVerticalBox(TextBlock);
		}
	}
	else
		UE_LOG(LogTemp, Error, TEXT("UActiveObjectivesMenu: ObjectiveSystemRef is nullptr"));
}
