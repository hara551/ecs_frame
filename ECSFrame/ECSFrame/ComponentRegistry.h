/**
* @file   ComponentRegistry.h
* @brief  コンポーネントごとの情報登録
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COMPONENT_REGISTRY_H_
#define _COMPONENT_REGISTRY_H_

#include <bitset>
#include <unordered_map>
#include <string>
#include <functional>
#include <stdexcept>
#include <memory>
#include <vector>

#include "ComponentMask.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework {

namespace ComponentRegistry {

/**
* @brief 名前と識別ビットのマップ
*/
inline std::unordered_map<std::string, ComponentBits> nameToBit;

/**
* @brief 識別ビットと配列作成関数のマップ
*/
inline std::unordered_map<ComponentBits, std::function<void(void*, size_t)>> bitToPlacementNewArray;

/**
* @brief 識別ビットとインスタンスコピー関数のマップ
*/
inline std::unordered_map<ComponentBits, std::function<void(void*, ComponentDataBase*)>> bitToAllocateInstance;

/**
* @brief 識別ビットとコンポーネントサイズのマップ
*/
inline std::unordered_map<ComponentBits, size_t> bitToSize;

/**
* @brief 識別ビットと動的確保コンストラクタのマップ
*/
inline std::unordered_map<ComponentBits, std::function<ComponentDataBase* ()>> bitToConstructor;

/**
* @brief 識別ビットとコピーコンストラクタのマップ
*/
inline std::unordered_map<ComponentBits, std::function<ComponentDataBase* (ComponentDataBase*)>> bitToCopyConstructor;

/**
* @brief 名前とビットを登録する
* @param[in] name コンポーネント名
* @param[in] bit 識別ビット
*/
void RegisterName(std::string name, ComponentBits bit);

/**
* @brief コンポーネント名から識別ビットを取得する
* @param[in] name コンポーネント名
*/
ComponentBits GetBitByName(std::string name);

/**
* @brief 複数のコンポーネント名から複合ビットを取得する
* @param[in] names コンポーネント名のリスト
*/
ComponentBits GetConbinedMaskByNames(std::vector<std::string> names);

/**
* @brief 配列作成関数を登録する
* @param[in] bit 識別ビット
* @param[in] placementNewArray 配列作成関数
*/
void RegisterPlacementNewArray(ComponentBits bit, std::function<void(void*, size_t)> placementNewArray);

/**
* @brief 配列作成関数を使用して配列を生成する
* @param[in] bit 識別ビット
* @param[in] buffer 配列を格納するバッファ
* @param[in] size 配列のサイズ
*/
void PlacementNewArray(ComponentBits bit, void* buffer, size_t size);

/**
* @brief インスタンスコピー関数を登録する
* @param[in] bit 識別ビット
* @param[in] allocateInstance コピー関数
*/
void RegisterAllocateInstance(ComponentBits bit, std::function<void(void*, ComponentDataBase*)> allocateInstance);

/**
* @brief コピー関数を使用してインスタンスを生成する
* @param[in] bit 識別ビット
* @param[in] buffer インスタンスを格納するバッファ
* @param[in] component コピー元のコンポーネント
*/
void AllocateInstance(ComponentBits bit, void* buffer, ComponentDataBase* component);

/**
* @brief コンポーネントのサイズを登録
* @param[in] bit 識別ビット
* @param[in] size コンポーネントサイズ
*/
void RegisterSize(ComponentBits bit, size_t size);

/**
* @brief コンポーネントのサイズを取得
* @param[in] bit 識別ビット
*/
size_t GetSize(ComponentBits bit);

/**
* @brief コンストラクタ登録
* @param[in] bit 識別ビット
* @param[in] constructor コンストラクタ
*/
void RegisterConstructor(ComponentBits bit, std::function<ComponentDataBase*()> constructor);

/**
* @brief コンストラクタ実行
* @param[in] bit 識別ビット
*/
ComponentDataBase* Constructor(ComponentBits bit);

/**
* @brief コピーコンストラクタ登録
* @param[in] bit 識別ビット
* @param[in] copyConstructor コピーコンストラクタ
*/
void RegisterCopyConstructor(ComponentBits bit, std::function<ComponentDataBase* (ComponentDataBase*)> copyConstructor);

/**
* @brief コピーコンストラクタ実行
* @param[in] bit 識別ビット
* @param[in] original コピー元データ
*/
ComponentDataBase* CopyConstructor(ComponentBits bit, ComponentDataBase* original);

/**
* @brief 全コンポーネントデータ各種登録処理
*/
void RegisterAllComponentData();

/**
* @brief コンポーネントデータ各種登録処理
* @param[in] name コンポーネントデータ名
*/
template<typename T >void RegisterComponentData(std::string name)
{
	ComponentBits bit = ComponentMask<T>::bit;

	RegisterName(name, bit);
	RegisterSize(bit, sizeof(T));
	RegisterPlacementNewArray(bit,
		[](void* buffer, size_t size)
		{
			new (buffer) T[size];
		});
	RegisterAllocateInstance(bit,
		[](void* buffer, ComponentDataBase* component)
		{
			T* cast_buffer = reinterpret_cast<T*>(buffer);
			* cast_buffer = T(component);
		});
	RegisterConstructor(bit,
		[]()
		{
			return new T();
		});
	RegisterCopyConstructor(bit,
		[](ComponentDataBase* original)
		{
			return new T(original);
		});
}

} // namespace ComponentRegistry

} // namespace HaraProject::Framework

#endif // !_COMPONENT_REGISTRY_H_
