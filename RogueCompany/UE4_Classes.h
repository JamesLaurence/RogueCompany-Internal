#pragma once
#pragma pack(4)

#include "stdafx.h"
#include "UE4_Core_structs.h"
#include "structs.h"

#define UWORLD_OFFSET 0x6366808

// Class Engine.Actor
// 0x01F8 (FullSize[0x0220] - InheritedSize[0x0028])
class AActor
{
public:
    char                                               pad_0000[0x118];                                          // 0x0 (0x118)
    class APawn*                                       Instigator;                                               // 0x0118(0x0008) (BlueprintVisible, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, ExposeOnSpawn, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
    char                                               pad_0001[0x10];                                           // 0x120 (0x10)
    class USceneComponent*                             RootComponent;                                            // 0x0130(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
};

// Class Engine.Level
// 0x0260 (FullSize[0x0288] - InheritedSize[0x0028])
class ULevel
{
public:
    char                                               pad_0000[0x98];                                           // 0x0000 (0x98)
    TArray<AActor*>                                    Actors;                                                   // 0x0098 (0x10)
    char                                               pad_0001[0x10];                                           // 0x00A8 (0x10)
    class UWorld*                                      OwningWorld;                                              // 0x00B8(0x0008) (ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Class Engine.SceneComponent
// 0x0158 (FullSize[0x0208] - InheritedSize[0x00B0])
class USceneComponent
{
public:
    char                                               pad_0000[0x11c];                                          // 0x0 (0x11c)
    struct FVector                                     RelativeLocation;                                         // 0x011C(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
    struct FRotator                                    RelativeRotation;                                         // 0x0128(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, NativeAccessSpecifierPrivate)
    struct FVector                                     RelativeScale3D;                                          // 0x0134(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
    struct FVector                                     ComponentVelocity;                                        // 0x0140(0x000C) (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0001[0x104];                                          // 0x14c (0x104)
    float                                              LODDistanceFactor;                                        // 0x0250(0x0004) (Edit, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Class Engine.GameInstance
// 0x0170 (FullSize[0x0198] - InheritedSize[0x0028])
class UGameInstance
{
public:
    char                                               pad_0000[0x38];                                           // 0x0 (0x38)
    TArray<class UPlayer*>                             LocalPlayers;                                             // 0x0038(0x0010) (ZeroConstructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
};

// Class Engine.World
// 0x0750 (FullSize[0x0778] - InheritedSize[0x0028])
class UWorld
{
public:
    char                                               pad_0000[0x30];                                           // 0x0 (0x30)
    class ULevel*                                      PersistentLevel;                                          // 0x0030(0x0008) (ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0001[0x110];                                          // 0x38 (0x110)
    TArray<class ULevel*>                              Levels;                                                   // 0x0148(0x0010) (ZeroConstructor, Transient, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
    char                                               pad_0002[0x30];                                           // 0x158 (0x30)
    class UGameInstance*                               OwningGameInstance;                                       // 0x0188(0x0008) (ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)

    UWorld* GetWorld() {
        return (UWorld*)(*(ULONG_PTR*)(this));
    }
};

// Class Engine.Controller
// 0x0078 (FullSize[0x0298] - InheritedSize[0x0220])
class AController : public AActor
{
public:
    char                                               pad_0000[0xF0];                                           // 0x0138 (0xF0)
    class APlayerState*                                PlayerState;                                              // 0x0228(0x0008) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0001[0x18];                                           // 0x230 (0x18)
    struct FName                                       StateName;                                                // 0x0248(0x0008) (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    class APawn*                                       Pawn;                                                     // 0x0250(0x0008) (Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
    char                                               pad_0002[0x30];                                           // 0x258 (0x30)
    struct FRotator                                    ControlRotation;                                          // 0x0288(0x000C) (ZeroConstructor, IsPlainOldData, NoDestructor, Protected, NativeAccessSpecifierProtected)
};

// Class Engine.PlayerController
// 0x02F0 (FullSize[0x0588] - InheritedSize[0x0298])
class APlayerController : public AController
{
public:
    char                                               pad_0000[0x4];                                            // 0x0294 (0x4)
    class UPlayer*                                     Player;                                                   // 0x0298(0x0008) (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    class APawn*                                       AcknowledgedPawn;                                         // 0x02A0(0x0008) (ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0001[0x10];                                           // 0x2a8 (0x10)
    class APlayerCameraManager*                        PlayerCameraManager;                                      // 0x02B8(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0002[0xc];                                            // 0x2c0 (0xc)
    struct FRotator                                    TargetViewRotation;                                       // 0x02CC(0x000C) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
};

// Class Engine.Player
// 0x0020 (FullSize[0x0048] - InheritedSize[0x0028])
class UPlayer
{
public:
    char                                               pad_0000[0x30];                                           // 0x0 (0x30)
    class APlayerController*                           PlayerController;                                         // 0x0030(0x0008) (ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Class Engine.Pawn
// 0x0060 (FullSize[0x0280] - InheritedSize[0x0220])
class APawn : public AActor
{
public:
    char                                               pad_0099[0xF4];                                           // 0x0138 (0xF4)
    float                                              BaseEyeHeight;                                            // 0x022C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0000[0x10];                                           // 0x230 (0x10)
    class APlayerState*                                PlayerState;                                              // 0x0240(0x0008) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
    char                                               pad_0001[0x10];                                           // 0x248 (0x10)
    class AController*                                 Controller;                                               // 0x0258(0x0008) (Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0002[0x20];                                           // 0x260 (0x20)
    class USkeletalMeshComponent*                      Mesh;                                                     // 0x0280(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
    char                                               pad_0003[0x1268];                                         // 0x288 (0x1268)
    float                                              SkyDiveMaxPitch;                                          // 0x14F0(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                              SkyDiveMinPitch;                                          // 0x14F4(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                              SkyDiveExitDistance;                                      // 0x14F8(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                              SkyDiveExitThreshold;                                     // 0x14FC(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                              SkyDiveForceExitDistance;                                 // 0x1500(0x0004) (Edit, ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0004[0x5bc];                                          // 0x1504 (0x5bc)
    bool                                               bIsCrosshairHidden;                                       // 0x1AC0(0x0001) (ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0005[0x937];                                          // 0x1ac1 (0x937)
    float                                              Health;                                                   // 0x23F8(0x0004) (Edit, Net, ZeroConstructor, Config, DisableEditOnInstance, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0006[0x4];                                            // 0x23fc (0x4)
    float                                              DownedHealth;                                             // 0x2400(0x0004) (Edit, ZeroConstructor, Config, DisableEditOnInstance, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    float                                              RevivedHealth;                                            // 0x2404(0x0004) (Edit, ZeroConstructor, Config, DisableEditOnInstance, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                ArmorHelmetLevel;                                         // 0x2408(0x0004) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                ArmorVestLevel;                                           // 0x240C(0x0004) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    float                                              ArmorDurabilityPercent;                                   // 0x2410(0x0004) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    float                                              CurrentArmorDurability;                                   // 0x2414(0x0004) (Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    float                                              MaxHealthBonus;                                           // 0x2418(0x0004) (Net, ZeroConstructor, Transient, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    float                                              MaxMaxHealthBonus;                                        // 0x241C(0x0004) (Edit, ZeroConstructor, Config, DisableEditOnInstance, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    float                                              LocalMaxHealthBonus;                                      // 0x2420(0x0004) (ZeroConstructor, Transient, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0007[0x14];                                           // 0x2424 (0x14)
    bool                                               bDowned;                                                  // 0x2438(0x0001) (Edit, Net, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0008[0x760];                                          // 0x2439 (0x760)
    EKSRevealType                                      RevealedStatus;                                           // 0x2B99(0x0004) (Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    bool                                               bRevealedToLocalPlayer;                                   // 0x2B9A(0x0001) (Edit, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0009[0x3a1];                                          // 0x2b9b (0x3a1)
    struct FName                                       BotName;                                                  // 0x2F3C(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    float                                              BotADSAccuracy;                                           // 0x2F44(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    bool                                               bRandomBotName;                                           // 0x2F48(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    bool                                               bBot;                                                     // 0x2F49(0x0001) (Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
};

// Class Engine.PlayerState
// 0x0100 (FullSize[0x0320] - InheritedSize[0x0220])
class APlayerState
{
public:
    char                                               pad_0000[0x220];                                          // 0x0 (0x220)
    float                                              Score;                                                    // 0x0220(0x0004) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    int                                                PlayerId;                                                 // 0x0224(0x0004) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    unsigned char                                      Ping;                                                     // 0x0228(0x0001) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0001[0x3];                                            // 0x229 (0x3)
    int                                                StartTime;                                                // 0x022C(0x0004) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0002[0x50];                                           // 0x230 (0x50)
    class APawn*                                       PawnPrivate;                                              // 0x0280(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
    char                                               pad_0003[0x78];                                           // 0x288 (0x78)
    struct FString                                     PlayerNamePrivate;                                        // 0x0300(0x0010) (Net, ZeroConstructor, RepNotify, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
};

// Class Killstreak.KSTeamState
// 0x0208 (FullSize[0x0428] - InheritedSize[0x0220])
class AKSTeamState
{
public:
    char                                               pad_0000[0x220];                                          // 0x0 (0x220)
    int                                                r_TeamNum;                                                // 0x0220(0x0004) (Edit, Net, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    bool                                               bTeamEliminated;                                          // 0x0224(0x0001) (Edit, Net, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    bool                                               bTeamEliminatedOrDowned;                                  // 0x0225(0x0001) (Edit, Net, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0001[0x5a];                                           // 0x226 (0x5a)
    TArray<class AKSPlayerState*>                      AllMembers;                                               // 0x0280(0x0010) (Edit, ZeroConstructor, DisableEditOnTemplate, EditConst, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    TArray<class AKSPlayerState*>                      PlayerMembers;                                            // 0x0290(0x0010) (Edit, ZeroConstructor, DisableEditOnTemplate, EditConst, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0002[0x44];                                           // 0x2a0 (0x44)
    int                                                Respawns;                                                 // 0x02E4(0x0004) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0003[0x10];                                           // 0x2e8 (0x10)
    int                                                Score;                                                    // 0x02F8(0x0004) (Edit, BlueprintVisible, Net, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    int                                                RoundWins;                                                // 0x02FC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    int                                                RoundLosses;                                              // 0x0300(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0004[0x14];                                           // 0x304 (0x14)
    EExtractionTeamType                                TeamType;                                                 // 0x0318(0x0004) (Edit, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0005[0x9c];                                           // 0x31c (0x9c)
    int                                                TotalKills;                                               // 0x03B8(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                TotalDeaths;                                              // 0x03BC(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                TotalAssists;                                             // 0x03C0(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                SideNum;                                                  // 0x03C4(0x0004) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
};

// Class Killstreak.KSPlayerState
// 0x06A8 (FullSize[0x09C8] - InheritedSize[0x0320])
class AKSPlayerState : public APlayerState
{
public:
    char                                               pad_0000[0x88];                                           // 0x0310 (0x88)
    class AKSTeamState*                                r_Team;                                                   // 0x0398(0x0008) (BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0001[0x8];                                            // 0x3a0 (0x8)
    int                                                BackupTeamNum;                                            // 0x03A8(0x0004) (ZeroConstructor, Transient, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0002[0x94];                                           // 0x3ac (0x94)
    int                                                EliminatedState;                                          // 0x0440(0x0004) (Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0003[0x3c];                                           // 0x444 (0x3c)
    struct FVector                                     LastKnownLocation;                                        // 0x0480(0x000C) (ZeroConstructor, Transient, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0004[0x34];                                           // 0x48c (0x34)
    int                                                RespawnTickets;                                           // 0x04C0(0x0004) (Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                               pad_0005[0x98];                                           // 0x4c4 (0x98)
    int                                                Kills;                                                    // 0x055C(0x0004) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                deaths;                                                   // 0x0560(0x0004) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                Assists;                                                  // 0x0564(0x0004) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                downs;                                                    // 0x0568(0x0004) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                DownSpree;                                                // 0x056C(0x0004) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                Revives;                                                  // 0x0570(0x0004) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                Eliminations;                                             // 0x0574(0x0004) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                Hacks;                                                    // 0x0578(0x0004) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    int                                                Dehacks;                                                  // 0x057C(0x0004) (Net, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
};

// Class Engine.PlayerCameraManager
// 0x2520 (FullSize[0x2740] - InheritedSize[0x0220])
class APlayerCameraManager : public AActor
{
public:
    char                                               pad_0000[0x100];                                          // 0x0138 (0x100)
    float                                              DefaultFOV;                                               // 0x0238(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0001[0x24d8];                                         // 0x23c (0x24d8)
    float                                              ViewPitchMin;                                             // 0x2714(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                              ViewPitchMax;                                             // 0x2718(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                              ViewYawMin;                                               // 0x271C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                              ViewYawMax;                                               // 0x2720(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                              ViewRollMin;                                              // 0x2724(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                              ViewRollMax;                                              // 0x2728(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                               pad_0002[0x4];                                            // 0x272c (0x4)
    float                                              ServerUpdateCameraTimeout;                                // 0x2730(0x0004) (ZeroConstructor, Config, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
};

// Class Engine.SkeletalMeshSocket
// 0x0038 (FullSize[0x0060] - InheritedSize[0x0028])
class USkeletalMeshSocket
{
public:
    char                                               pad_0000[0x28];                                           // 0x0 (0x28)
    struct FName                                       SocketName;                                               // 0x0028(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    struct FName                                       BoneName;                                                 // 0x0030(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    struct FVector                                     RelativeLocation;                                         // 0x0038(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    struct FRotator                                    RelativeRotation;                                         // 0x0044(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
    struct FVector                                     RelativeScale;                                            // 0x0050(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Class Engine.Skeleton
// 0x0340 (FullSize[0x0368] - InheritedSize[0x0028])
class USkeleton
{
public:
    char                                               pad_0000[0x38];                                           // 0x0 (0x38)
    TArray<struct FBoneNode>                           BoneTree;                                                 // 0x0038(0x0010) (Edit, ZeroConstructor, EditConst, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    TArray<struct FTransform>                          RefLocalPoses;                                            // 0x0048(0x0010) (ZeroConstructor, Deprecated, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    unsigned char                                      UnknownData_K5CY[0x118];                                  // 0x0058(0x0118) MISSED OFFSET (FIX SPACE BETWEEN PREVIOUS PROPERTY)
    struct FGuid                                       VirtualBoneGuid;                                          // 0x0170(0x0010) (ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    TArray<struct FVirtualBone>                        VirtualBones;                                             // 0x0180(0x0010) (ZeroConstructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    TArray<class USkeletalMeshSocket*>                 Sockets;                                                  // 0x0190(0x0010) (ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Class Engine.SkeletalMesh
// 0x0348 (FullSize[0x0388] - InheritedSize[0x0040])
class USkeletalMesh
{
public:
    char                                               pad_0000[0x60];                                           // 0x0 (0x60)
    class USkeleton*                                   Skeleton;                                                 // 0x0060(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData, NoDestructor, AssetRegistrySearchable, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Class Engine.SkinnedMeshComponent
// 0x0220 (FullSize[0x0670] - InheritedSize[0x0450])
class USkeletalMeshComponent
{
public:
    char                                               pad_0000[0x450];                                          // 0x0 (0x450)
    class USkeletalMesh*                               SkeletalMesh;                                             // 0x0450(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};