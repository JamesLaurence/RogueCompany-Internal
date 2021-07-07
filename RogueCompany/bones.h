enum e_bones
{
    Root = 0,
    C_Pelvis = 1,
    C_Hip = 2,
    R_Thigh = 3,
    R_Calf = 4,
    R_Foot = 5,
    R_Toe = 6,
    R_Calf_Twist01 = 7,
    R_Calf_Twist02 = 8,
    R_Knee = 9,
    R_Attach_LegLower01 = 10,
    R_Thigh_Twist01 = 11,
    R_Thigh_Twist02 = 12,
    R_Attach_Hip01 = 13,
    R_Attach_LegUpper01 = 14,
    L_Thigh = 15,
    L_Calf = 16,
    L_Foot = 17,
    L_Toe = 18,
    L_Calf_Twist01 = 19,
    L_Calf_Twist02 = 20,
    L_Knee = 21,
    L_Attach_LegLower01 = 22,
    L_Thigh_Twist01 = 23,
    L_Thigh_Twist02 = 24,
    L_Attach_Hip01 = 25,
    L_Attach_LegUpper01 = 26,
    C_Attach_Hip01 = 27,
    L_ButtTech = 28,
    L_Hip = 29,
    R_ButtTech = 30,
    R_Hip = 31,
    C_Spine01 = 32,
    C_Spine02 = 33,
    C_Spine03 = 34,
    C_Spine04 = 35,
    L_Clavicle = 36,
    L_UpperArm = 37,
    L_Forearm = 38,
    L_Hand = 39,
    L_Prop = 40,
    L_RightAlign = 41,
    L_IndexFinger_00 = 42,
    L_IndexFinger_01 = 43,
    L_IndexFinger_02 = 44,
    L_IndexFinger_03 = 45,
    L_MiddleFinger_00 = 46,
    L_MiddleFinger_01 = 47,
    L_MiddleFinger_02 = 48,
    L_MiddleFinger_03 = 49,
    L_RingFinger_00 = 50,
    L_RingFinger_01 = 51,
    L_RingFinger_02 = 52,
    L_RingFinger_03 = 53,
    L_PinkyFinger_00 = 54,
    L_PinkyFinger_01 = 55,
    L_PinkyFinger_02 = 56,
    L_PinkyFinger_03 = 57,
    L_Thumb_01 = 58,
    L_Thumb_02 = 59,
    L_Thumb_03 = 60,
    L_Prop_Gadget = 61,
    L_Forearm_Twist01 = 62,
    L_Forearm_Twist02 = 63,
    L_Elbow = 64,
    L_UpperArm_Twist01 = 65,
    L_UpperArm_Twist02 = 66,
    L_Bicep = 67,
    L_Attach_ArmUpper01 = 68,
    L_ShoulderPadLarge_FlapTop01 = 69,
    L_ShoulderPadLarge_FlapBot01 = 70,
    L_ShoulderPadMedium_Flap01 = 71,
    R_Clavicle = 72,
    R_UpperArm = 73,
    R_Forearm = 74,
    R_Hand = 75,
    R_Prop = 76,
    R_LeftAlign = 77,
    R_IndexFinger_00 = 78,
    R_IndexFinger_01 = 79,
    R_IndexFinger_02 = 80,
    R_IndexFinger_03 = 81,
    R_MiddleFinger_00 = 82,
    R_MiddleFinger_01 = 83,
    R_MiddleFinger_02 = 84,
    R_MiddleFinger_03 = 85,
    R_RingFinger_00 = 86,
    R_RingFinger_01 = 87,
    R_RingFinger_02 = 88,
    R_RingFinger_03 = 89,
    R_PinkyFinger_00 = 90,
    R_PinkyFinger_01 = 91,
    R_PinkyFinger_02 = 92,
    R_PinkyFinger_03 = 93,
    R_Thumb_01 = 94,
    R_Thumb_02 = 95,
    R_Thumb_03 = 96,
    R_Prop_Gadget = 97,
    R_Forearm_Twist01 = 98,
    R_Forearm_Twist02 = 99,
    R_Elbow = 100,
    R_UpperArm_Twist01 = 101,
    R_UpperArm_Twist02 = 102,
    R_Bicep = 103,
    R_Attach_ArmUpper01 = 104,
    R_ShoulderPadLarge_FlapTop01 = 105,
    R_ShoulderPadLarge_FlapBot01 = 106,
    R_ShoulderPadMedium_Flap01 = 107,
    C_Neck01 = 108,
    C_Neck02 = 109,
    C_Head = 110,
    C_Camera = 111,
    C_FaceBones_Root = 112,
    R_Cheek_02 = 113,
    L_MouthCorner_01 = 114,
    L_Lip_Upper_02 = 115,
    L_Lip_Lower_02 = 116,
    R_Lid_Lower_02 = 117,
    R_Lid_Lower_03 = 118,
    R_Lid_Lower_01 = 119,
    C_Jaw_01 = 120,
    C_Lip_Lower_01 = 121,
    R_Lip_Lower_01 = 122,
    L_Lip_Lower_01 = 123,
    C_Chin_01 = 124,
    L_NasalPinch_01 = 125,
    L_EyeBall_01 = 126,
    L_Cheek_02 = 127,
    L_Forehead_01 = 128,
    L_Cheek_03 = 129,
    L_Brow_01 = 130,
    L_Brow_03 = 131,
    L_Brow_02 = 132,
    R_Forehead_01 = 133,
    R_NasalPinch_01 = 134,
    R_Brow_01 = 135,
    R_Brow_03 = 136,
    R_Brow_02 = 137,
    R_LaughLine_01 = 138,
    R_Lid_Upper_02 = 139,
    R_Lid_Upper_03 = 140,
    R_Lid_Upper_01 = 141,
    R_MouthCorner_01 = 142,
    R_Lip_Upper_02 = 143,
    R_Lip_Lower_02 = 144,
    L_LaughLine_01 = 145,
    C_Brow_01 = 146,
    C_Lip_Upper_01 = 147,
    L_Lip_Upper_01 = 148,
    R_Lip_Upper_01 = 149,
    C_JawTeeth_01 = 150,
    L_Lid_Upper_02 = 151,
    L_Lid_Upper_03 = 152,
    L_Lid_Upper_01 = 153,
    C_Forehead_01 = 154,
    R_EyeBall_01 = 155,
    L_Lid_Lower_02 = 156,
    L_Lid_Lower_01 = 157,
    L_Lid_Lower_03 = 158,
    L_Cheek_01 = 159,
    R_Cheek_04 = 160,
    L_Cheek_04 = 161,
    C_HeadTeeth_01 = 162,
    C_Nose_01 = 163,
    L_Nostril_01 = 164,
    R_Nostril_01 = 165,
    R_Cheek_01 = 166,
    R_Cheek_03 = 167,
    C_Tongue_01 = 168,
    C_Tongue_02 = 169,
    C_Tongue_03 = 170,
    R_Attach_Back01 = 171,
    L_Attach_Back01 = 172,
    C_Attach_BackUpper01 = 173,
    C_Attach_BackLower01 = 174,
    L_Prop_SSC = 175,
    R_Prop_SSC = 176,
    L_Attach_Chest01 = 177,
    R_Attach_Chest01 = 178,
    R_Breast = 179,
    L_Breast = 180,
    L_Attach_Torso01 = 181,
    R_Attach_Torso01 = 182,
    L_Prop_SC = 183,
    R_Prop_SC = 184,
    C_FloorPlane01 = 185,
    GrenadeDeAttach = 186,
    Foot_IK_Root = 187,
    Root_Root_L_Foot = 188,
    Root_Root_R_Foot = 189,
    R_Prop_L_Hand = 190,
    Foot_IK_Root_C_Pelvis = 191,
    L_Hand_L_Prop = 192,
    C_Spine04_R_Hand = 193,
    L_Hand_L_Prop_Gadget = 194,
    R_Hand_R_Prop_Gadget = 195,
    R_Hand_R_Prop = 196,
    L_Prop_R_Hand = 197,
    C_Spine04_L_Hand = 198
};