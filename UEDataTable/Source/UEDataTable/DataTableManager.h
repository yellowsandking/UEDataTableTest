// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ConfigDataTableRow.h"
#include "DataTableManager.generated.h"

/**
 * DataTable管理器类
 * 用于加载和读取CSV和JSON格式的DataTable
 */
UCLASS(BlueprintType, Blueprintable)
class UEDATATABLE_API UDataTableManager : public UObject
{
	GENERATED_BODY()

public:
	UDataTableManager();

	/**
	 * 从CSV文件加载DataTable
	 * @param CSVFilePath CSV文件路径（相对于Content目录）
	 * @return 加载的DataTable对象
	 */
	UFUNCTION(BlueprintCallable, Category = "DataTable")
	UDataTable* LoadDataTableFromCSV(const FString& CSVFilePath);

	/**
	 * 从JSON文件加载DataTable
	 * @param JSONFilePath JSON文件路径（相对于Content目录）
	 * @return 加载的DataTable对象
	 */
	UFUNCTION(BlueprintCallable, Category = "DataTable")
	UDataTable* LoadDataTableFromJSON(const FString& JSONFilePath);

	/**
	 * 根据ID查找配置数据
	 * @param DataTable 要查询的DataTable
	 * @param ID 配置ID
	 * @param OutRow 输出的行数据
	 * @return 是否找到
	 */
	UFUNCTION(BlueprintCallable, Category = "DataTable")
	bool FindRowByID(UDataTable* DataTable, int32 ID, FConfigDataTableRow& OutRow);

	/**
	 * 根据Name查找配置数据
	 * @param DataTable 要查询的DataTable
	 * @param Name 配置名称
	 * @param OutRow 输出的行数据
	 * @return 是否找到
	 */
	UFUNCTION(BlueprintCallable, Category = "DataTable")
	bool FindRowByName(UDataTable* DataTable, const FString& Name, FConfigDataTableRow& OutRow);

	/**
	 * 获取所有行数据
	 * @param DataTable 要查询的DataTable
	 * @param OutRows 输出的所有行数据
	 */
	UFUNCTION(BlueprintCallable, Category = "DataTable")
	void GetAllRows(UDataTable* DataTable, TArray<FConfigDataTableRow>& OutRows);

	/**
	 * 获取DataTable中的行数
	 * @param DataTable 要查询的DataTable
	 * @return 行数
	 */
	UFUNCTION(BlueprintCallable, Category = "DataTable")
	int32 GetRowCount(UDataTable* DataTable);

private:
	/**
	 * 从文件路径加载DataTable资源
	 * @param FilePath 文件路径
	 * @return 加载的DataTable对象
	 */
	UDataTable* LoadDataTableAsset(const FString& FilePath);

	/**
	 * 从JSON字符串创建DataTable
	 * @param JSONString JSON字符串
	 * @return 创建的DataTable对象
	 */
	UDataTable* CreateDataTableFromJSONString(const FString& JSONString);
};
