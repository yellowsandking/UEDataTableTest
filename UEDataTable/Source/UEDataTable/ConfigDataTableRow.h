// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ConfigDataTableRow.generated.h"

/**
 * 配置表行数据结构
 * 包含ID、Name、Description三个字段
 */
USTRUCT(BlueprintType)
struct UEDATATABLE_API FConfigDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	/** 配置ID */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	int32 ID;

	/** 配置名称 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FString Name;

	/** 配置描述 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FString Description;

	FConfigDataTableRow()
		: ID(0)
		, Name(TEXT(""))
		, Description(TEXT(""))
	{
	}
};
