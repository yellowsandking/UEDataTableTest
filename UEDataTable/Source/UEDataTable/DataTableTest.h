// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTableManager.h"
#include "DataTableTest.generated.h"

/**
 * DataTable测试类
 * 用于测试CSV和JSON文件的读取功能
 */
UCLASS()
class UEDATATABLE_API ADataTableTest : public AActor
{
	GENERATED_BODY()
	
public:	
	ADataTableTest(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

	/** DataTable管理器实例 */
	UPROPERTY()
	UDataTableManager* DataTableManager;

	/** CSV格式的DataTable */
	UPROPERTY()
	UDataTable* CSVDataTable;

	/** JSON格式的DataTable */
	UPROPERTY()
	UDataTable* JSONDataTable;

	/** CSV文件路径 */
	UPROPERTY(EditAnywhere, Category = "Test Settings")
	FString CSVFilePath;

	/** JSON文件路径 */
	UPROPERTY(EditAnywhere, Category = "Test Settings")
	FString JSONFilePath;

public:
	/**
	 * 运行所有测试用例
	 */
	UFUNCTION(BlueprintCallable, Category = "Test")
	void RunAllTests();

	/**
	 * 测试CSV文件加载
	 */
	UFUNCTION(BlueprintCallable, Category = "Test")
	void TestCSVLoading();

	/**
	 * 测试JSON文件加载
	 */
	UFUNCTION(BlueprintCallable, Category = "Test")
	void TestJSONLoading();

	/**
	 * 测试根据ID查找
	 */
	UFUNCTION(BlueprintCallable, Category = "Test")
	void TestFindByID();

	/**
	 * 测试根据Name查找
	 */
	UFUNCTION(BlueprintCallable, Category = "Test")
	void TestFindByName();

	/**
	 * 测试获取所有行
	 */
	UFUNCTION(BlueprintCallable, Category = "Test")
	void TestGetAllRows();
};
