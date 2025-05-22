#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManagerSubsystem.generated.h"

class UCommonActivatableWidget;
class UCommonActivatableWidgetContainerBase;

/**
 * Subsystem to manage UI navigation and widget stacks using CommonUI
 * Provides centralized control for UI flow and transitions
 */
UCLASS()
class CODEREDREBOOT_API UUIManagerSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
    
public:
    // Initialize and shutdown
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    
    /**
     * Push a widget onto a stack
     * @param WidgetClass The widget class to create and push
     * @param Stack Optional stack to push to (uses main stack if null)
     * @return The newly created widget, or nullptr if creation failed
     */
    UFUNCTION(BlueprintCallable, Category = "UI", meta = (DisplayName = "Push Widget To Stack"))
    UCommonActivatableWidget* PushWidgetToStack(TSubclassOf<UCommonActivatableWidget> WidgetClass, UCommonActivatableWidgetContainerBase* Stack = nullptr);
    
    /**
     * Pop the top widget from a stack
     * @param Stack Optional stack to pop from (uses main stack if null)
     */
    UFUNCTION(BlueprintCallable, Category = "UI", meta = (DisplayName = "Pop Widget From Stack"))
    void PopWidgetFromStack(UCommonActivatableWidgetContainerBase* Stack = nullptr);
    
    /**
     * Clear all widgets from a stack
     * @param Stack Optional stack to clear (uses main stack if null)
     */
    UFUNCTION(BlueprintCallable, Category = "UI", meta = (DisplayName = "Clear Widget Stack"))
    void ClearWidgetStack(UCommonActivatableWidgetContainerBase* Stack = nullptr);
    
    /**
     * Get the main widget stack
     * @return The main widget stack
     */
    UFUNCTION(BlueprintCallable, Category = "UI", meta = (DisplayName = "Get Main Stack"))
    UCommonActivatableWidgetContainerBase* GetMainStack() const { return MainStack; }
    
    /**
     * Set the main widget stack
     * @param Stack The stack to set as main
     */
    UFUNCTION(BlueprintCallable, Category = "UI", meta = (DisplayName = "Set Main Stack"))
    void SetMainStack(UCommonActivatableWidgetContainerBase* Stack);
    
    /**
     * Register a widget stack with the manager
     * @param StackName Name to identify the stack
     * @param Stack The stack to register
     */
    UFUNCTION(BlueprintCallable, Category = "UI", meta = (DisplayName = "Register Widget Stack"))
    void RegisterWidgetStack(FName StackName, UCommonActivatableWidgetContainerBase* Stack);
    
    /**
     * Get a registered widget stack by name
     * @param StackName Name of the stack to retrieve
     * @return The requested stack, or nullptr if not found
     */
    UFUNCTION(BlueprintCallable, Category = "UI", meta = (DisplayName = "Get Widget Stack"))
    UCommonActivatableWidgetContainerBase* GetWidgetStack(FName StackName) const;
    
private:
    // The main widget stack for the game
    UPROPERTY()
    UCommonActivatableWidgetContainerBase* MainStack = nullptr;
    
    // Map of named widget stacks
    UPROPERTY()
    TMap<FName, UCommonActivatableWidgetContainerBase*> RegisteredStacks;
};