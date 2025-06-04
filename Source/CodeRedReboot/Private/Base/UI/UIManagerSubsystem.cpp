#include "Base/UI/UIManagerSubsystem.h"
#include "CommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
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

UCommonActivatableWidget* UUIManagerSubsystem::PushWidgetToStack(TSubclassOf<UCommonActivatableWidget> WidgetClass, UCommonActivatableWidgetStack* Stack)
{
    // Use the provided stack or fall back to the main stack
    UCommonActivatableWidgetStack* TargetStack = Stack ? Stack : MainStack;
    
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
    
    return TargetStack->AddWidget(WidgetClass);
}

void UUIManagerSubsystem::PopWidgetFromStack(UCommonActivatableWidgetStack* Stack)
{
    // Use the provided stack or fall back to the main stack
    UCommonActivatableWidgetStack* TargetStack = Stack ? Stack : MainStack;
    
    if (!TargetStack)
    {
        UE_LOG(LogBaseUI, Warning, TEXT("Attempted to pop widget from null stack"));
        return;
    }
    
    // Pop the top widget
    TargetStack->RemoveWidget(*TargetStack->GetActiveWidget());
}

void UUIManagerSubsystem::ClearWidgetStack(UCommonActivatableWidgetStack* Stack)
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

void UUIManagerSubsystem::SetMainStack(UCommonActivatableWidgetStack* Stack)
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

void UUIManagerSubsystem::RegisterWidgetStack(FName StackName, UCommonActivatableWidgetStack* Stack)
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

UCommonActivatableWidgetStack* UUIManagerSubsystem::GetWidgetStack(FName StackName) const
{
    if (!StackName.IsNone())
    {
        if (UCommonActivatableWidgetStack* const* FoundStack = RegisteredStacks.Find(StackName))
        {
            return *FoundStack;
        }
    }
    
    return nullptr;
}