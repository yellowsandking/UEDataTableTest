# DataTableTest 测试用例类文档

## 概述

`ADataTableTest` 是一个用于测试 DataTable 功能的 Actor 类，提供了完整的测试用例来验证 CSV 和 JSON 文件的读取、数据查询等功能。

## 类信息

- **类名**: `ADataTableTest`
- **继承**: `AActor`
- **头文件**: `Source/UEDataTable/DataTableTest.h`
- **实现文件**: `Source/UEDataTable/DataTableTest.cpp`

## 功能特性

- ✅ CSV 文件加载测试
- ✅ JSON 文件加载测试
- ✅ 根据 ID 查找数据测试
- ✅ 根据 Name 查找数据测试
- ✅ 获取所有行数据测试
- ✅ 自动运行所有测试用例
- ✅ 详细的日志输出

## 成员变量

### 受保护成员

| 变量名 | 类型 | 说明 |
|--------|------|------|
| `DataTableManager` | `UDataTableManager*` | DataTable 管理器实例 |
| `CSVDataTable` | `UDataTable*` | CSV 格式的 DataTable |
| `JSONDataTable` | `UDataTable*` | JSON 格式的 DataTable |
| `CSVFilePath` | `FString` | CSV 文件路径（可在编辑器中编辑） |
| `JSONFilePath` | `FString` | JSON 文件路径（可在编辑器中编辑） |

### 默认文件路径

- **CSV 文件**: `DataTables/ConfigData.csv`
- **JSON 文件**: `DataTables/ConfigData.json`

## 测试用例方法

### 1. RunAllTests()

运行所有测试用例的入口函数。

**功能**:
- 依次执行所有测试用例
- 输出测试开始和结束的日志

**调用方式**:
```cpp
// C++ 代码中
TestActor->RunAllTests();

// 蓝图中
调用 "Run All Tests" 节点
```

**输出示例**:
```
========== Starting DataTable Tests ==========
--- Test: CSV Loading ---
--- Test: JSON Loading ---
--- Test: Find By ID ---
--- Test: Find By Name ---
--- Test: Get All Rows ---
========== DataTable Tests Completed ==========
```

---

### 2. TestCSVLoading()

测试 CSV 文件加载功能。

**功能**:
- 从指定路径加载 CSV 文件
- 验证加载是否成功
- 输出加载的行数

**测试内容**:
- ✅ 文件路径有效性
- ✅ CSV 文件解析
- ✅ DataTable 创建
- ✅ 行数统计

**输出示例**:
```
--- Test: CSV Loading ---
CSV DataTable loaded successfully! Row count: 5
```

**失败输出**:
```
--- Test: CSV Loading ---
Failed to load CSV DataTable from: DataTables/ConfigData.csv
```

---

### 3. TestJSONLoading()

测试 JSON 文件加载功能。

**功能**:
- 从指定路径加载 JSON 文件
- 验证加载是否成功
- 输出加载的行数

**测试内容**:
- ✅ 文件路径有效性
- ✅ JSON 文件解析
- ✅ DataTable 创建
- ✅ 行数统计

**输出示例**:
```
--- Test: JSON Loading ---
JSON DataTable loaded successfully! Row count: 5
```

**失败输出**:
```
--- Test: JSON Loading ---
Failed to load JSON DataTable from: DataTables/ConfigData.json
```

---

### 4. TestFindByID()

测试根据 ID 查找数据的功能。

**功能**:
- 测试查找存在的 ID（ID=1）
- 测试查找不存在的 ID（ID=999）
- 验证查找结果的正确性

**前置条件**:
- 需要先运行 `TestCSVLoading()` 加载数据

**测试内容**:
- ✅ 查找存在的 ID
- ✅ 查找不存在的 ID
- ✅ 返回数据的完整性

**输出示例**:
```
--- Test: Find By ID ---
Found row with ID=1: Name=Config1, Description=这是第一个配置项
Correctly did not find row with ID=999
```

**失败输出**:
```
--- Test: Find By ID ---
CSV DataTable is not loaded. Run TestCSVLoading first.
```

---

### 5. TestFindByName()

测试根据 Name 查找数据的功能。

**功能**:
- 测试根据名称查找数据
- 验证查找结果的正确性

**前置条件**:
- 需要先运行 `TestCSVLoading()` 加载数据

**测试内容**:
- ✅ 根据名称查找数据
- ✅ 返回数据的完整性

**输出示例**:
```
--- Test: Find By Name ---
Found row with Name=Config1: ID=1, Description=这是第一个配置项
```

**失败输出**:
```
--- Test: Find By Name ---
CSV DataTable is not loaded. Run TestCSVLoading first.
Row with Name=Config1 not found
```

---

### 6. TestGetAllRows()

测试获取所有行数据的功能。

**功能**:
- 获取 DataTable 中的所有行
- 遍历并输出每一行的详细信息

**前置条件**:
- 需要先运行 `TestCSVLoading()` 加载数据

**测试内容**:
- ✅ 获取所有行
- ✅ 行数统计
- ✅ 数据完整性

**输出示例**:
```
--- Test: Get All Rows ---
Total rows: 5
  ID=1, Name=Config1, Description=这是第一个配置项
  ID=2, Name=Config2, Description=这是第二个配置项
  ID=3, Name=Config3, Description=这是第三个配置项
  ID=4, Name=Config4, Description=这是第四个配置项
  ID=5, Name=Config5, Description=这是第五个配置项
```

**失败输出**:
```
--- Test: Get All Rows ---
CSV DataTable is not loaded. Run TestCSVLoading first.
```

## 使用方法

### 方法一：在编辑器中放置 Actor

1. **编译项目**
   - 确保项目已成功编译

2. **放置测试 Actor**
   - 在 UE5 编辑器中，打开内容浏览器
   - 搜索 `DataTableTest`
   - 将 `DataTableTest` Actor 拖拽到场景中

3. **配置文件路径（可选）**
   - 选中场景中的 `DataTableTest` Actor
   - 在细节面板中找到 "Test Settings" 分类
   - 修改 `CSV File Path` 和 `JSON File Path`（如果需要）

4. **运行游戏**
   - 点击播放按钮
   - 测试会在 `BeginPlay()` 时自动执行
   - 查看输出日志窗口查看测试结果

### 方法二：在蓝图中使用

1. **创建蓝图**
   - 创建基于 `ADataTableTest` 的蓝图类

2. **调用测试函数**
   - 在蓝图中可以调用以下节点：
     - `Run All Tests` - 运行所有测试
     - `Test CSV Loading` - 测试 CSV 加载
     - `Test JSON Loading` - 测试 JSON 加载
     - `Test Find By ID` - 测试 ID 查找
     - `Test Find By Name` - 测试 Name 查找
     - `Test Get All Rows` - 测试获取所有行

3. **示例蓝图节点**
   ```
   Event BeginPlay
   └─> Run All Tests
   ```

### 方法三：在 C++ 代码中使用

```cpp
// 在游戏模式或其他类中
void AMyGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    // 创建测试 Actor
    ADataTableTest* TestActor = GetWorld()->SpawnActor<ADataTableTest>();
    
    // 设置文件路径（可选）
    TestActor->CSVFilePath = TEXT("DataTables/MyConfig.csv");
    TestActor->JSONFilePath = TEXT("DataTables/MyConfig.json");
    
    // 运行所有测试
    TestActor->RunAllTests();
    
    // 或者单独运行某个测试
    TestActor->TestCSVLoading();
    TestActor->TestFindByID();
}
```

## 查看测试结果

### 输出日志窗口

1. **打开输出日志**
   - 在 UE5 编辑器中，点击 `Window` → `Developer Tools` → `Output Log`

2. **过滤日志**
   - 使用过滤器搜索 "Test" 或 "DataTable"
   - 日志级别：
     - `Warning` - 测试信息和成功消息
     - `Error` - 测试失败和错误信息
     - `Log` - 详细信息

### 日志级别说明

- **Warning (黄色)**: 测试执行信息、成功消息
- **Error (红色)**: 测试失败、错误信息
- **Log (白色)**: 详细信息、调试信息

## 测试数据格式

### CSV 文件格式

CSV 文件应位于 `Content/DataTables/` 目录下，格式如下：

```csv
---,ID,Name,Description
1,1,Config1,这是第一个配置项
2,2,Config2,这是第二个配置项
3,3,Config3,这是第三个配置项
```

**注意**:
- 第一列必须是行名（通常使用数字）
- 第一行是列头，必须包含 `ID`, `Name`, `Description`
- 文件编码建议使用 UTF-8

### JSON 文件格式

JSON 文件应位于 `Content/DataTables/` 目录下，格式如下：

```json
{
	"Rows": [
		{
			"ID": 1,
			"Name": "Config1",
			"Description": "这是第一个配置项"
		},
		{
			"ID": 2,
			"Name": "Config2",
			"Description": "这是第二个配置项"
		}
	]
}
```

**注意**:
- 必须包含 `Rows` 数组
- 每个对象必须包含 `ID`, `Name`, `Description` 字段
- 文件编码建议使用 UTF-8

## 常见问题

### Q1: 测试失败，提示文件未找到

**原因**: 文件路径不正确或文件不存在

**解决方法**:
1. 检查文件是否存在于 `Content/DataTables/` 目录
2. 确认文件路径设置正确（相对于 Content 目录）
3. 检查文件扩展名是否正确（.csv 或 .json）

### Q2: CSV 解析失败

**原因**: CSV 格式不正确

**解决方法**:
1. 检查 CSV 文件格式是否符合要求
2. 确保第一列是行名
3. 确保列头包含所有必需字段
4. 检查文件编码是否为 UTF-8

### Q3: JSON 解析失败

**原因**: JSON 格式不正确

**解决方法**:
1. 检查 JSON 语法是否正确
2. 确保包含 `Rows` 数组
3. 验证每个对象包含所有必需字段
4. 使用 JSON 验证工具检查格式

### Q4: 查找测试失败

**原因**: 数据未加载或查找条件不正确

**解决方法**:
1. 确保先运行 `TestCSVLoading()` 或 `TestJSONLoading()`
2. 检查测试数据中是否包含要查找的 ID 或 Name
3. 确认数据格式正确

## 扩展测试

### 添加自定义测试用例

可以在 `DataTableTest.cpp` 中添加自定义测试方法：

```cpp
void ADataTableTest::TestCustomFunction()
{
    UE_LOG(LogTemp, Warning, TEXT("--- Test: Custom Function ---"));
    
    if (!CSVDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("CSV DataTable is not loaded."));
        return;
    }
    
    // 添加你的测试逻辑
    // ...
}
```

然后在头文件中声明：

```cpp
UFUNCTION(BlueprintCallable, Category = "Test")
void TestCustomFunction();
```

## 相关类

- **UDataTableManager**: DataTable 管理器类，提供数据加载和查询功能
- **FConfigDataTableRow**: 配置表行数据结构，包含 ID、Name、Description 字段

## 版本信息

- **创建日期**: 2025-01-09
- **适用引擎版本**: Unreal Engine 5.x
- **最后更新**: 2025-01-09

## 许可证

Copyright Epic Games, Inc. All Rights Reserved.
