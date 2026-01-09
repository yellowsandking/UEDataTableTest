// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataTableManager.h"
#include "Engine/Engine.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "UObject/UObjectGlobals.h"

UDataTableManager::UDataTableManager()
{
}

UDataTable* UDataTableManager::LoadDataTableFromCSV(const FString& CSVFilePath)
{
	FString FullPath = FPaths::ProjectContentDir() + CSVFilePath;
	
	// 尝试直接加载资源
	// 构建资源路径：/Game/Path/AssetName.AssetName
	FString AssetPath = TEXT("/Game/") + CSVFilePath;
	AssetPath = FPaths::ChangeExtension(AssetPath, TEXT(""));
	
	// 提取资源名称（文件名，不含扩展名）
	FString AssetName = FPaths::GetBaseFilename(AssetPath);
	// 构建完整的对象路径：PackagePath.AssetName
	FString FullAssetPath = AssetPath + TEXT(".") + AssetName;
	
	// 使用 StaticLoadObject 并设置 LOAD_NoWarn 标志以抑制警告
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *FullAssetPath, nullptr, LOAD_NoWarn));
	
	if (DataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("Successfully loaded DataTable from: %s"), *FullAssetPath);
		return DataTable;
	}

	// 如果资源不存在，尝试从文件系统读取并创建
	FString CSVContent;
	if (FFileHelper::LoadFileToString(CSVContent, *FullPath))
	{
		// 创建临时DataTable
		UDataTable* NewDataTable = NewObject<UDataTable>(GetTransientPackage(), UDataTable::StaticClass());
		NewDataTable->RowStruct = FConfigDataTableRow::StaticStruct();
		
		// 解析CSV内容
		TArray<FString> ImportErrors = NewDataTable->CreateTableFromCSVString(CSVContent);
		
		// 检查导入错误
		if (ImportErrors.Num() > 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to parse CSV file: %s"), *FullPath);
			for (const FString& Error : ImportErrors)
			{
				UE_LOG(LogTemp, Error, TEXT("  Import error: %s"), *Error);
			}
			return nullptr;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Successfully created DataTable from CSV file: %s"), *FullPath);
			return NewDataTable;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load CSV file: %s"), *FullPath);
	}

	return nullptr;
}

UDataTable* UDataTableManager::LoadDataTableFromJSON(const FString& JSONFilePath)
{
	FString FullPath = FPaths::ProjectContentDir() + JSONFilePath;
	
	// 尝试直接加载资源
	// 构建资源路径：/Game/Path/AssetName.AssetName
	FString AssetPath = TEXT("/Game/") + JSONFilePath;
	AssetPath = FPaths::ChangeExtension(AssetPath, TEXT(""));
	
	// 提取资源名称（文件名，不含扩展名）
	FString AssetName = FPaths::GetBaseFilename(AssetPath);
	// 构建完整的对象路径：PackagePath.AssetName
	FString FullAssetPath = AssetPath + TEXT(".") + AssetName;
	
	// 使用 StaticLoadObject 并设置 LOAD_NoWarn 标志以抑制警告
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *FullAssetPath, nullptr, LOAD_NoWarn));
	
	if (DataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("Successfully loaded DataTable from: %s"), *FullAssetPath);
		return DataTable;
	}

	// 如果资源不存在，尝试从文件系统读取JSON并创建
	FString JSONContent;
	if (FFileHelper::LoadFileToString(JSONContent, *FullPath))
	{
		return CreateDataTableFromJSONString(JSONContent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load JSON file: %s"), *FullPath);
	}

	return nullptr;
}

UDataTable* UDataTableManager::CreateDataTableFromJSONString(const FString& JSONString)
{
	UDataTable* NewDataTable = NewObject<UDataTable>(GetTransientPackage(), UDataTable::StaticClass());
	NewDataTable->RowStruct = FConfigDataTableRow::StaticStruct();

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JSONString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON string"));
		return nullptr;
	}

	// 检查是否有"Rows"数组
	const TArray<TSharedPtr<FJsonValue>>* RowsArray;
	if (!JsonObject->TryGetArrayField(TEXT("Rows"), RowsArray))
	{
		UE_LOG(LogTemp, Error, TEXT("JSON does not contain 'Rows' array"));
		return nullptr;
	}

	// 解析每一行
	for (const TSharedPtr<FJsonValue>& RowValue : *RowsArray)
	{
		const TSharedPtr<FJsonObject>* RowObject;
		if (!RowValue->TryGetObject(RowObject) || !RowObject->IsValid())
		{
			continue;
		}

		FConfigDataTableRow RowData;
		
		// 读取ID
		int32 ID;
		if ((*RowObject)->TryGetNumberField(TEXT("ID"), ID))
		{
			RowData.ID = ID;
		}

		// 读取Name
		FString Name;
		if ((*RowObject)->TryGetStringField(TEXT("Name"), Name))
		{
			RowData.Name = Name;
		}

		// 读取Description
		FString Description;
		if ((*RowObject)->TryGetStringField(TEXT("Description"), Description))
		{
			RowData.Description = Description;
		}

		// 使用ID作为行名
		FName RowName = FName(*FString::Printf(TEXT("%d"), RowData.ID));
		NewDataTable->AddRow(RowName, RowData);
	}

	UE_LOG(LogTemp, Log, TEXT("Successfully created DataTable from JSON with %d rows"), NewDataTable->GetRowMap().Num());
	return NewDataTable;
}

bool UDataTableManager::FindRowByID(UDataTable* DataTable, int32 ID, FConfigDataTableRow& OutRow)
{
	if (!DataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable is null"));
		return false;
	}

	FName RowName = FName(*FString::Printf(TEXT("%d"), ID));
	FConfigDataTableRow* FoundRow = DataTable->FindRow<FConfigDataTableRow>(RowName, TEXT("FindRowByID"));

	if (FoundRow)
	{
		OutRow = *FoundRow;
		return true;
	}

	return false;
}

bool UDataTableManager::FindRowByName(UDataTable* DataTable, const FString& Name, FConfigDataTableRow& OutRow)
{
	if (!DataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable is null"));
		return false;
	}

	// 遍历所有行查找匹配的Name
	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
	for (const auto& Pair : RowMap)
	{
		FConfigDataTableRow* Row = (FConfigDataTableRow*)Pair.Value;
		if (Row && Row->Name == Name)
		{
			OutRow = *Row;
			return true;
		}
	}

	return false;
}

void UDataTableManager::GetAllRows(UDataTable* DataTable, TArray<FConfigDataTableRow>& OutRows)
{
	OutRows.Empty();

	if (!DataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable is null"));
		return;
	}

	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
	for (const auto& Pair : RowMap)
	{
		FConfigDataTableRow* Row = (FConfigDataTableRow*)Pair.Value;
		if (Row)
		{
			OutRows.Add(*Row);
		}
	}
}

int32 UDataTableManager::GetRowCount(UDataTable* DataTable)
{
	if (!DataTable)
	{
		return 0;
	}

	return DataTable->GetRowMap().Num();
}
