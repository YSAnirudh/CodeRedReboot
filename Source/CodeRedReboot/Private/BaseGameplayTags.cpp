#include "BaseGameplayTags.h"

namespace BaseGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Gameplay_AbilityInputBlocked, "Gameplay.AbilityInputBlocked", "Tag used to Block Ability Input");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Move, "Input.Move", "Input for movement (2D Axis)");

	FGameplayTag FindTagByString(const FString& GameplayTagString, bool bMatchPartialTag)
	{
		// Get the Gameplay Tags Manager
		const UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();

		// Request the tag using the string
		FGameplayTag GameplayTag = TagsManager.RequestGameplayTag(FName(GameplayTagString));

		return GameplayTag;
	}
}