// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MYSTINGS_NavComponent_generated_h
#error "NavComponent.generated.h already included, missing '#pragma once' in NavComponent.h"
#endif
#define MYSTINGS_NavComponent_generated_h

#define itp380_group_project_Source_Mystings_NavComponent_h_14_RPC_WRAPPERS
#define itp380_group_project_Source_Mystings_NavComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define itp380_group_project_Source_Mystings_NavComponent_h_14_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesUNavComponent(); \
	friend MYSTINGS_API class UClass* Z_Construct_UClass_UNavComponent(); \
	public: \
	DECLARE_CLASS(UNavComponent, UActorComponent, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Mystings"), NO_API) \
	DECLARE_SERIALIZER(UNavComponent) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define itp380_group_project_Source_Mystings_NavComponent_h_14_INCLASS \
	private: \
	static void StaticRegisterNativesUNavComponent(); \
	friend MYSTINGS_API class UClass* Z_Construct_UClass_UNavComponent(); \
	public: \
	DECLARE_CLASS(UNavComponent, UActorComponent, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Mystings"), NO_API) \
	DECLARE_SERIALIZER(UNavComponent) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define itp380_group_project_Source_Mystings_NavComponent_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNavComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNavComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNavComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNavComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNavComponent(UNavComponent&&); \
	NO_API UNavComponent(const UNavComponent&); \
public:


#define itp380_group_project_Source_Mystings_NavComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNavComponent(UNavComponent&&); \
	NO_API UNavComponent(const UNavComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNavComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNavComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNavComponent)


#define itp380_group_project_Source_Mystings_NavComponent_h_11_PROLOG
#define itp380_group_project_Source_Mystings_NavComponent_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	itp380_group_project_Source_Mystings_NavComponent_h_14_RPC_WRAPPERS \
	itp380_group_project_Source_Mystings_NavComponent_h_14_INCLASS \
	itp380_group_project_Source_Mystings_NavComponent_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define itp380_group_project_Source_Mystings_NavComponent_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	itp380_group_project_Source_Mystings_NavComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	itp380_group_project_Source_Mystings_NavComponent_h_14_INCLASS_NO_PURE_DECLS \
	itp380_group_project_Source_Mystings_NavComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID itp380_group_project_Source_Mystings_NavComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
