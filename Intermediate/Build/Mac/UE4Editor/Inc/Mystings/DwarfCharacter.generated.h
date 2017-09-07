// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef MYSTINGS_DwarfCharacter_generated_h
#error "DwarfCharacter.generated.h already included, missing '#pragma once' in DwarfCharacter.h"
#endif
#define MYSTINGS_DwarfCharacter_generated_h

#define itp380_group_project_Source_Mystings_DwarfCharacter_h_11_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execPlayDeathAnim) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->PlayDeathAnim(); \
		P_NATIVE_END; \
	}


#define itp380_group_project_Source_Mystings_DwarfCharacter_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execPlayDeathAnim) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->PlayDeathAnim(); \
		P_NATIVE_END; \
	}


#define itp380_group_project_Source_Mystings_DwarfCharacter_h_11_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesADwarfCharacter(); \
	friend MYSTINGS_API class UClass* Z_Construct_UClass_ADwarfCharacter(); \
	public: \
	DECLARE_CLASS(ADwarfCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Mystings"), NO_API) \
	DECLARE_SERIALIZER(ADwarfCharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define itp380_group_project_Source_Mystings_DwarfCharacter_h_11_INCLASS \
	private: \
	static void StaticRegisterNativesADwarfCharacter(); \
	friend MYSTINGS_API class UClass* Z_Construct_UClass_ADwarfCharacter(); \
	public: \
	DECLARE_CLASS(ADwarfCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Mystings"), NO_API) \
	DECLARE_SERIALIZER(ADwarfCharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define itp380_group_project_Source_Mystings_DwarfCharacter_h_11_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADwarfCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADwarfCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADwarfCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADwarfCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADwarfCharacter(ADwarfCharacter&&); \
	NO_API ADwarfCharacter(const ADwarfCharacter&); \
public:


#define itp380_group_project_Source_Mystings_DwarfCharacter_h_11_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADwarfCharacter(ADwarfCharacter&&); \
	NO_API ADwarfCharacter(const ADwarfCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADwarfCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADwarfCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ADwarfCharacter)


#define itp380_group_project_Source_Mystings_DwarfCharacter_h_8_PROLOG
#define itp380_group_project_Source_Mystings_DwarfCharacter_h_11_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	itp380_group_project_Source_Mystings_DwarfCharacter_h_11_RPC_WRAPPERS \
	itp380_group_project_Source_Mystings_DwarfCharacter_h_11_INCLASS \
	itp380_group_project_Source_Mystings_DwarfCharacter_h_11_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define itp380_group_project_Source_Mystings_DwarfCharacter_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	itp380_group_project_Source_Mystings_DwarfCharacter_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	itp380_group_project_Source_Mystings_DwarfCharacter_h_11_INCLASS_NO_PURE_DECLS \
	itp380_group_project_Source_Mystings_DwarfCharacter_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID itp380_group_project_Source_Mystings_DwarfCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS