#pragma once
#include "stdafx.h"
#include <unordered_set>

#define PI (3.14159265358979323846264338327950288419716939937510)

class APlayerController;

struct FVector2D {
	float X;
	float Y;

	inline BOOL IsValid() {
		return X != NULL && Y != NULL;
	}

	inline float distance() {
		return sqrtf(this->X * this->X + this->Y * this->Y);
	}
};

struct FVector {
	float X;
	float Y;
	float Z;

	FVector operator-(FVector buffer) {

		return FVector
		(
			{ this->X - buffer.X, this->Y - buffer.Y, this->Z - buffer.Z }
		);
	}

	FVector operator+(FVector buffer) {

		return FVector
		(
			{ this->X + buffer.X, this->Y + buffer.Y, this->Z + buffer.Z }
		);
	}

	inline float distance() {
		return sqrtf(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
	}

	FVector2D ToScreen(APlayerController* Controller);
};

struct FRotator {

	float Pitch;
	float Yaw;
	float Roll;

	FRotator ClampAngles() {

		if (this->Yaw < -180.0f)
			this->Yaw += 360.0f;

		if (this->Yaw > 180.0f)
			this->Yaw -= 360.0f;

		if (this->Pitch < -74.0f)
			this->Pitch = -74.0f;

		if (this->Pitch > 74.0f)
			this->Pitch = 74.0f;

		return *this;
	}

	static FRotator CalcAngle(FVector cameraLocation, FVector boneLocation) {

		FRotator result;

		auto delta = boneLocation - cameraLocation;
		auto distance = delta.distance();

		result.Yaw = atan2f(delta.Y, delta.X) * (180.0f / PI);
		result.Pitch = (-((acosf((delta.Z / distance)) * 180.0f / PI) - 90.0f));
		result.Roll = NULL;

		return result;
	}

};

struct FMatrix {
	float M[4][4];
};

struct FBoxSphereBounds {
	FVector Origin;
	FVector BoxExtent;
	float SphereRadius;
};

struct FBox {
	FVector Min;
	FVector Max;

	FBox() {

		Min.X = NULL;
		Min.Y = NULL;
		Min.Z = NULL;

		Max.X = NULL;
		Max.Y = NULL;
		Max.Z = NULL;
	}
};

template<class T>
struct TArray
{
	friend struct FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}

	inline void Add(T InputData)
	{
		Data = (T*)realloc(Data, sizeof(T) * (Count + 1));
		Data[Count++] = InputData;
		Max = Count;
	};

	inline void Clear()
	{
		free(Data);
		Count = Max = 0;
	};

private:
	T* Data;
	int32_t Count;
	int32_t Max;
};

template<class TEnum>
class TEnumAsByte
{
public:
	inline TEnumAsByte()
	{
	}

	inline TEnumAsByte(TEnum _value)
		: value(static_cast<uint8_t>(_value))
	{
	}

	explicit inline TEnumAsByte(int32_t _value)
		: value(static_cast<uint8_t>(_value))
	{
	}

	explicit inline TEnumAsByte(uint8_t _value)
		: value(_value)
	{
	}

	inline operator TEnum() const
	{
		return (TEnum)value;
	}

	inline TEnum GetValue() const
	{
		return (TEnum)value;
	}

private:
	uint8_t value;
};


struct FString : private TArray<wchar_t>
{
	inline FString()
	{
	};
	
	inline int Count() {
		return Num();
	}

	inline bool IsValid() {
		return Data != NULL;
	}

	inline const wchar_t* data() const {
		return Data;
	}

	inline const char* c_str() const {
		return std::string(Data, &Data[wcslen(Data)]).c_str();
	}
	std::string ToString() const
	{
		auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

class FNameEntry
{
	static const auto NAME_WIDE_MASK = 0x1;
	static const auto NAME_INDEX_SHIFT = 1;

public:
	uint64_t Flags;
	uint32_t Index;
	FNameEntry* HashNext;
	union
	{
		char AnsiName[1024];
		wchar_t WideName[1024];
	};

	inline const int32_t GetIndex() const
	{
		return Index >> NAME_INDEX_SHIFT;
	}

	inline bool IsWide() const
	{
		return Index & NAME_WIDE_MASK;
	}

	inline const char* GetAnsiName() const
	{
		return AnsiName;
	}

	inline const wchar_t* GetWideName() const
	{
		return WideName;
	}

	std::string GetName() const
	{
		if (IsWide())
		{
			const auto length = std::wcslen(WideName);

			std::string str(length, '\0');

			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(WideName, WideName + length, '?', &str[0]);

			return str;
		}
		else
		{
			return AnsiName;
		}
	}
};

struct FName
{
	int32_t Index;
	int32_t Number;

	inline FName()
		: Index(0),
		Number(0)
	{
	};

	inline FName(int32_t i)
		: Index(i),
		Number(0)
	{
	};

	FName(const char* nameToFind)
		: Index(0),
		Number(0)
	{
		static std::unordered_set<size_t> cache;

		for (auto i : cache)
		{
			if (GetGlobalNames()[i]->GetName() == nameToFind)
			{
				Index = i;

				return;
			}
		}

		for (auto i = 0u; i < GetGlobalNames().Num(); ++i)
		{
			if (GetGlobalNames()[i] != nullptr)
			{
				if (GetGlobalNames()[i]->GetName() == nameToFind)
				{
					cache.insert(i);

					Index = i;

					return;
				}
			}
		}
	};

	static TArray<FNameEntry*>* GNames;
	static inline TArray<FNameEntry*>& GetGlobalNames()
	{
		return *GNames;
	};

	inline std::string GetName() const
	{
		return GetGlobalNames()[Index]->GetName();
	};

	inline bool operator==(const FName& other) const
	{
		return Index == other.Index;
	};
};