#pragma once
#include "stdafx.h"
#include "UE4_Basic.h"

// Enum Killstreak.EKSRevealType
enum class EKSRevealType : int
{
	NotRevealed = 0,
	Normal = 1,
	Permanent = 2,
	MAX = 3,

};

// Enum Killstreak.EExtractionTeamType
enum class EExtractionTeamType : int
{
	NotSet = 0,
	Attacker = 1,
	Defender = 2,
	MAX = 3,

};

// Enum Killstreak.EEliminationState
enum class EEliminationState : int
{
	NotInPlay = 0,
	Playing = 1,
	Eliminated = 2,
	MAX = 3,

};

// Enum Engine.EBoneTranslationRetargetingMode
enum class EBoneTranslationRetargetingMode : int
{
	Animation = 0,
	Skeleton = 1,
	AnimationScaled = 2,
	AnimationRelative = 3,
	OrientAndScale = 4,
	MAX = 5,

};

// ScriptStruct Engine.BoneNode
// 0x0010
struct FBoneNode
{
	struct FName                                       Name;                                                      // 0x0000(0x0008) (ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int                                                ParentIndex;                                               // 0x0008(0x0004) (ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	TEnumAsByte<EBoneTranslationRetargetingMode>       TranslationRetargetingMode;                                // 0x000C(0x0004) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};