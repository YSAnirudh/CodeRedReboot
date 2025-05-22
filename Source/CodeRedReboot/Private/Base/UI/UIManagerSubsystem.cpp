#include "Base/UI/UIManagerSubsystem.h"
#include "CommonActivatableWidget.h"
#include "CommonActivatableWidgetContainerBase.h"
#include "BaseLogChannels.h"

void UUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogBaseUI, Log, TEXT("UI Manager Subsystem Initialized"));
    
    // Initialize the registered stacks map
    RegisteredStacks.Empty();
}

void UUIManagerSubsystem::Deinitialize()
{
    // Clean up any active UI
    if (MainStack)
    {
        MainStack->ClearWidgets();
    }
    
    // Clear all registered stacks
    for (auto& StackPair : RegisteredStacks)
    {
        if (StackPair.Value && StackPair.Value != MainStack)
        {
            StackPair.Value->ClearWidgets();
        }
    }
    
    RegisteredStacks.Empty();
    MainStack = nullptr;
    
    Super::Deinitialize();
}

UCommonActivatableWidget* UUIManagerSubsystem::PushWidgetToStack(TSubclassOf<UCommonActivatableWidget> WidgetClass, UCommonActivatableWidgetContainerBase* Stack)
{
    // Use the provided stack or fall back to the main stack
    UCommonActivatableWidgetContainerBase* TargetStack = Stack ? Stack : MainStack;
    
    if (!TargetStack)
    {
        UE_LOG(LogBaseUI, Warning, TEXT("Attempted to push widget to null stack"));
        return nullptr;
    }
    
    if (!WidgetClass)
    {
        UE_LOG(LogBaseUI, Warning, TEXT("Attempted to push null widget class to stack"));
        return nullptr;
    }
    
    // Create and push the widget
    UCommonActivatableWidget* NewWidget = CreateWidget<UCommonActivatableWidget>(GetGameInstance(), WidgetClass);
    if (NewWidget)
    {
        TargetStack->AddWidget(NewWidget);
        return NewWidget;
    }
    
    return nullptr;
}

void UUIManagerSubsystem::PopWidgetFromStack(UCommonActivatableWidgetContainerBase* Stack)
{
    // Use the provided stack or fall back to the main stack
    UCommonActivatableWidgetContainerBase* TargetStack = Stack ? Stack : MainStack;
    
    if (!TargetStack)
    {
        UE_LOG(LogBaseUI, Warning, TEXT("Attempted to pop widget from null stack"));
        return;
    }
    
    // Pop the top widget
    TargetStack->DeactivateTopWidget();
}

void UUIManagerSubsystem::ClearWidgetStack(UCommonActivatableWidgetContainerBase* Stack)
{
    // Use the provided stack or fall back to the main stack
    UCommonActivatableWidgetContainerBase* TargetStack = Stack ? Stack : MainStack;
    
    if (!TargetStack)
    {
        UE_LOG(LogBaseUI, Warning, TEXT("Attempted to clear null stack"));
        return;
    }
    
    // Clear all widgets
    TargetStack->ClearWidgets();
}

void UUIManagerSubsystem::SetMainStack(UCommonActivatableWidgetContainerBase* Stack)
{
    if (Stack)
    {
        MainStack = Stack;
        
        // Also register it with a standard name
        RegisterWidgetStack(FName("MainStack"), Stack);
    }
    else
    {
        UE_LOG(LogBaseUI, Warning, TEXT("Attempted to set null main stack"));
    }
}

void UUIManagerSubsystem::RegisterWidgetStack(FName StackName, UCommonActivatableWidgetContainerBase* Stack)
{
    if (!StackName.IsNone() && Stack)
    {
        RegisteredStacks.Add(StackName, Stack);
    }
    else
    {
        UE_LOG(LogBaseUI, Warning, TEXT("Attempted to register invalid stack: %s"), *StackName.ToString());
    }
}

UCommonActivatableWidgetContainerBase* UUIManagerSubsystem::GetWidgetStack(FName StackName) const
{
    if (!StackName.IsNone())
    {
        if (UCommonActivatableWidgetContainerBase* const* FoundStack = RegisteredStacks.Find(StackName))
        {
            return *FoundStack;
        }
    }
    
    return nullptr;
}