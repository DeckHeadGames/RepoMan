// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FVector;
#ifdef COLOREPO_colorepoCharacter_generated_h
#error "colorepoCharacter.generated.h already included, missing '#pragma once' in colorepoCharacter.h"
#endif
#define COLOREPO_colorepoCharacter_generated_h

#define colorepo_Source_colorepo_colorepoCharacter_h_11_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execUpdateFireDirection) \
	{ \
		P_GET_STRUCT(FVector,Z_Param_FireDirection); \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaSeconds); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->UpdateFireDirection(Z_Param_FireDirection,Z_Param_DeltaSeconds); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execMoveColorepoCharacter) \
	{ \
		P_GET_STRUCT(FVector,Z_Param_Movement); \
		P_GET_STRUCT(FVector,Z_Param_FireDirection); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->MoveColorepoCharacter(Z_Param_Movement,Z_Param_FireDirection); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFireDirection) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FVector*)Z_Param__Result=this->GetFireDirection(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetMoveDirection) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaSeconds); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FVector*)Z_Param__Result=this->GetMoveDirection(Z_Param_DeltaSeconds); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execFireCircle) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->FireCircle(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execFireLightWave) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->FireLightWave(); \
		P_NATIVE_END; \
	}


#define colorepo_Source_colorepo_colorepoCharacter_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execUpdateFireDirection) \
	{ \
		P_GET_STRUCT(FVector,Z_Param_FireDirection); \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaSeconds); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->UpdateFireDirection(Z_Param_FireDirection,Z_Param_DeltaSeconds); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execMoveColorepoCharacter) \
	{ \
		P_GET_STRUCT(FVector,Z_Param_Movement); \
		P_GET_STRUCT(FVector,Z_Param_FireDirection); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->MoveColorepoCharacter(Z_Param_Movement,Z_Param_FireDirection); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFireDirection) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FVector*)Z_Param__Result=this->GetFireDirection(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetMoveDirection) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_DeltaSeconds); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FVector*)Z_Param__Result=this->GetMoveDirection(Z_Param_DeltaSeconds); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execFireCircle) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->FireCircle(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execFireLightWave) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->FireLightWave(); \
		P_NATIVE_END; \
	}


#define colorepo_Source_colorepo_colorepoCharacter_h_11_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAcolorepoCharacter(); \
	friend COLOREPO_API class UClass* Z_Construct_UClass_AcolorepoCharacter(); \
	public: \
	DECLARE_CLASS(AcolorepoCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/colorepo"), NO_API) \
	DECLARE_SERIALIZER(AcolorepoCharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define colorepo_Source_colorepo_colorepoCharacter_h_11_INCLASS \
	private: \
	static void StaticRegisterNativesAcolorepoCharacter(); \
	friend COLOREPO_API class UClass* Z_Construct_UClass_AcolorepoCharacter(); \
	public: \
	DECLARE_CLASS(AcolorepoCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/colorepo"), NO_API) \
	DECLARE_SERIALIZER(AcolorepoCharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define colorepo_Source_colorepo_colorepoCharacter_h_11_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AcolorepoCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AcolorepoCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AcolorepoCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AcolorepoCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AcolorepoCharacter(AcolorepoCharacter&&); \
	NO_API AcolorepoCharacter(const AcolorepoCharacter&); \
public:


#define colorepo_Source_colorepo_colorepoCharacter_h_11_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AcolorepoCharacter(AcolorepoCharacter&&); \
	NO_API AcolorepoCharacter(const AcolorepoCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AcolorepoCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AcolorepoCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AcolorepoCharacter)


#define colorepo_Source_colorepo_colorepoCharacter_h_11_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(AcolorepoCharacter, CameraBoom); } \
	FORCEINLINE static uint32 __PPO__FollowCamera() { return STRUCT_OFFSET(AcolorepoCharacter, FollowCamera); } \
	FORCEINLINE static uint32 __PPO__BoundingBox() { return STRUCT_OFFSET(AcolorepoCharacter, BoundingBox); } \
	FORCEINLINE static uint32 __PPO__RedProjectile() { return STRUCT_OFFSET(AcolorepoCharacter, RedProjectile); } \
	FORCEINLINE static uint32 __PPO__OrangeProjectile() { return STRUCT_OFFSET(AcolorepoCharacter, OrangeProjectile); } \
	FORCEINLINE static uint32 __PPO__YellowProjectile() { return STRUCT_OFFSET(AcolorepoCharacter, YellowProjectile); } \
	FORCEINLINE static uint32 __PPO__GreenProjectile() { return STRUCT_OFFSET(AcolorepoCharacter, GreenProjectile); } \
	FORCEINLINE static uint32 __PPO__BlueProjectile() { return STRUCT_OFFSET(AcolorepoCharacter, BlueProjectile); } \
	FORCEINLINE static uint32 __PPO__IndigoProjectile() { return STRUCT_OFFSET(AcolorepoCharacter, IndigoProjectile); } \
	FORCEINLINE static uint32 __PPO__VioletProjectile() { return STRUCT_OFFSET(AcolorepoCharacter, VioletProjectile); }


#define colorepo_Source_colorepo_colorepoCharacter_h_8_PROLOG
#define colorepo_Source_colorepo_colorepoCharacter_h_11_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	colorepo_Source_colorepo_colorepoCharacter_h_11_PRIVATE_PROPERTY_OFFSET \
	colorepo_Source_colorepo_colorepoCharacter_h_11_RPC_WRAPPERS \
	colorepo_Source_colorepo_colorepoCharacter_h_11_INCLASS \
	colorepo_Source_colorepo_colorepoCharacter_h_11_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define colorepo_Source_colorepo_colorepoCharacter_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	colorepo_Source_colorepo_colorepoCharacter_h_11_PRIVATE_PROPERTY_OFFSET \
	colorepo_Source_colorepo_colorepoCharacter_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	colorepo_Source_colorepo_colorepoCharacter_h_11_INCLASS_NO_PURE_DECLS \
	colorepo_Source_colorepo_colorepoCharacter_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID colorepo_Source_colorepo_colorepoCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
