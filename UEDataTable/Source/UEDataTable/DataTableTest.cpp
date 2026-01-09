// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataTableTest.h"
#include "Engine/Engine.h"

ADataTableTest::ADataTableTest()
{
	PrimaryActorTick.bCanEverTick = false;

	// 创建DataTable管理器
	DataTableManager = NewObject<UDataTableManager>(this);

	// 设置默认文件路径
	CSVFilePath = TEXT("DataTables/ConfigData.csv");
	JSONFilePath = TEXT("DataTables/ConfigData.json");
}

void ADataTableTest::BeginPlay()
{
	Super::BeginPlay();

	// 自动运行测试
	RunAllTests();
}

void ADataTableTest::RunAllTests()
{
	UE_LOG(LogTemp, Warning, TEXT("========== Starting DataTable Tests =========="));

	TestCSVLoading();
	TestJSONLoading();
	TestFindByID();
	TestFindByName();
	TestGetAllRows();

	UE_LOG(LogTemp, Warning, TEXT("========== DataTable Tests Completed =========="));
}

void ADataTableTest::TestCSVLoading()
{
	UE_LOG(LogTemp, Warning, TEXT("--- Test: CSV Loading ---"));

	CSVDataTable = DataTableManager->LoadDataTableFromCSV(CSVFilePath);

	if (CSVDataTable)
	{
		int32 RowCount = DataTableManager->GetRowCount(CSVDataTable);
		UE_LOG(LogTemp, Warning, TEXT("CSV DataTable loaded successfully! Row count: %d"), RowCount);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load CSV DataTable from: %s"), *CSVFilePath);
	}
}

void ADataTableTest::TestJSONLoading()
{
	UE_LOG(LogTemp, Warning, TEXT("--- Test: JSON Loading ---"));

	JSONDataTable = DataTableManager->LoadDataTableFromJSON(JSONFilePath);

	if (JSONDataTable)
	{
		int32 RowCount = DataTableManager->GetRowCount(JSONDataTable);
		UE_LOG(LogTemp, Warning, TEXT("JSON DataTable loaded successfully! Row count: %d"), RowCount);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load JSON DataTable from: %s"), *JSONFilePath);
	}
}

void ADataTableTest::TestFindByID()
{
	UE_LOG(LogTemp, Warning, TEXT("--- Test: Find By ID ---"));

	if (!CSVDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("CSV DataTable is not loaded. Run TestCSVLoading first."));
		return;
	}

	// 测试查找ID为1的行
	FConfigDataTableRow FoundRow;
	if (DataTableManager->FindRowByID(CSVDataTable, 1, FoundRow))
	{
		UE_LOG(LogTemp, Warning, TEXT("Found row with ID=1: Name=%s, Description=%s"), 
			*FoundRow.Name, *FoundRow.Description);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Row with ID=1 not found"));
	}

	// 测试查找不存在的ID
	if (DataTableManager->FindRowByID(CSVDataTable, 999, FoundRow))
	{
		UE_LOG(LogTemp, Error, TEXT("Unexpectedly found row with ID=999"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Correctly did not find row with ID=999"));
	}
}

void ADataTableTest::TestFindByName()
{
	UE_LOG(LogTemp, Warning, TEXT("--- Test: Find By Name ---"));

	if (!CSVDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("CSV DataTable is not loaded. Run TestCSVLoading first."));
		return;
	}

	// 测试查找Name为"Config1"的行
	FConfigDataTableRow FoundRow;
	if (DataTableManager->FindRowByName(CSVDataTable, TEXT("Config1"), FoundRow))
	{
		UE_LOG(LogTemp, Warning, TEXT("Found row with Name=Config1: ID=%d, Description=%s"), 
			FoundRow.ID, *FoundRow.Description);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Row with Name=Config1 not found"));
	}
}

void ADataTableTest::TestGetAllRows()
{
	UE_LOG(LogTemp, Warning, TEXT("--- Test: Get All Rows ---"));

	if (!CSVDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("CSV DataTable is not loaded. Run TestCSVLoading first."));
		return;
	}

	TArray<FConfigDataTableRow> AllRows;
	DataTableManager->GetAllRows(CSVDataTable, AllRows);

	UE_LOG(LogTemp, Warning, TEXT("Total rows: %d"), AllRows.Num());
	for (const FConfigDataTableRow& Row : AllRows)
	{
		UE_LOG(LogTemp, Warning, TEXT("  ID=%d, Name=%s, Description=%s"), 
			Row.ID, *Row.Name, *Row.Description);
	}
}
