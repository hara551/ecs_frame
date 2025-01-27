/**
* @file   IEntityManager.h
* @brief  エンティティ操作インターフェース.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _IENTITY_OPERATOR_H_
#define _IENTITY_OPERATOR_H_

#include <cstdint>
#include <unordered_map>

#include "ComponentMask.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework
{

/**
* @brief エンティティ操作インターフェース
*/
class IEntityOperator
{
public:
	/**
	* @brief デストラクタ
	*/
	virtual ~IEntityOperator() = default;

	/**
	* @brief 読み込んだエンティティを作成する
	* @param[in] entityValueHandler 値が格納されたエンティティのデータ
	*/
	virtual uint32_t CreateLoadedEntity(std::unordered_map<ComponentBits, ComponentDataBase*> entityValueHandler) = 0;

	/**
	* @brief エンティティを削除する
	* @param[in] id エンティティID
	*/
	virtual void DeleteEntity(uint32_t id) = 0;

	/**
	* @brief エンティティにコンポーネントデータを追加
	* @param[in] id エンティティID
	* @param[in] bit コンポーネント識別ビット
	*/
	virtual void AddComponentData(uint32_t id, ComponentBits bit) = 0;

	/**
	* @brief エンティティからコンポーネントを削除
	* @param[in] id エンティティID
	* @param[in] bit コンポーネント識別ビット
	*/
	virtual void RemoveComponentData(uint32_t id, ComponentBits bit) = 0;

	/**
	* @brief エンティティからコンポーネントを取得
	* @param[in] id エンティティID
	* @param[in] bit コンポーネント識別ビット
	*/
	virtual ComponentDataBase* GetComponentData(uint32_t id, ComponentBits bit) = 0;

	/**
	* @brief エンティティが指定コンポーネントを持っているか確認
	* @param[in] id エンティティID
	* @param[in] bit コンポーネント識別ビット
	*/
	virtual bool HasComponentData(uint32_t id, ComponentBits bit) = 0;

	
#ifdef _DEBUG
	/**
	* @brief 空のエンティティを作成
	*/
	virtual uint32_t CreateEntityEmpty() = 0;
#endif // _DEBUG

};

}// !namespace HaraProject::Framework

#endif // !_IENTITY_OPERATOR_H_