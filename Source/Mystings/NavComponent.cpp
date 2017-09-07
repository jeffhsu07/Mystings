// Fill out your copyright notice in the Description page of Project Settings.

#include "Mystings.h"
#include "NavComponent.h"
#include "MystingsPlayerController.h"

// Sets default values for this component's properties
UNavComponent::UNavComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNavComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UNavComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    /*if(CurrNode != nullptr) {
        FVector dist = CurrNode->GetActorLocation() - GetOwner()->GetActorLocation();
        std::cout << "Distance: " << dist.Size() << std::endl;
        if(dist.Size() < 5.0f) {
            FollowPath(CurrNode->parent);
        }
    }
    auto pawn = Cast<APawn>(GetOwner());
    if(pawn) {
    auto controller = Cast<AMystingsPlayerController>(pawn->GetController());
    if(controller) controller->MoveToMouseCursor();
    }*/
}

void UNavComponent::FollowPath(ATile* end) {
    /*CurrNode = end;
    // Rotate towards tile
    Vector3 diff =  end->tile->GetPosition() - GetOwner().GetPosition();
    diff.Normalize();
    
    float EnemyDot = FVector::DotProduct(Vector3::UnitX, diff);
    auto EnemyCross = FVector::CrossProduct(Vector3::UnitX, diff);
    
    float angle = Math::Acos(EnemyDot);
    if (EnemyCross.z < 0.0f) {
        angle *= -1.0f;
    }
    
    GetOwner().SetRotation(angle);
    auto pawn = Cast<APawn>(GetOwner());
    if(pawn) {
        auto controller = Cast<AMystingsPlayerController>(pawn->GetController());
        //if(controller) controller->SetNewMoveDestination(CurrNode->GetActorLocation());
        if(controller) controller->MoveToMouseCursor();
    }*/
}
