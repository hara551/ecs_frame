/**
* @file   SystemBase.h
* @brief  システム基底クラス定義.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _SYSTEM_BASE_H_
#define _SYSTEM_BASE_H_

#include <vector>

#include "nlohmann/json.hpp"

#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"
#include "ComponentMask.h"
#include "ComponentDataChunk.h"

#ifdef _DEBUG
#include "GuiItemBase.h"
#endif // _DEBUG

namespace HaraProject::Framework {

class ISystemDistributor;

class SystemBase
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] entityManager エンティティマネージャー
	* @param[in] systemDistributor システムマネージャー
	* @param[in] chunkProvider コンポーネントデータマネージャー
	*/
	SystemBase(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: m_entity_operator(entityOperator), m_system_distributor(systemDistributor), m_chunk_provider(chunkProvider)
	{
		InitSystem(); 
	}

	/**
	* @brief デストラクタ
	*/
	virtual ~SystemBase() { UninitSystem(); }

	/**
	* @brief システム更新
	*/
	virtual void UpdateSystem(float deltaTime) = 0;

	/**
	* @brief 指定のコンポーネントデータ全てを含むチャンクを全て取得
	* @tparam コンポーネントデータ型
	*/
	template<typename ... T>
	std::vector<ComponentDataChunk*> FindChunks(){
		ComponentBits mask;
		((mask = mask | ComponentMask<T>::bit), ...);
		return m_chunk_provider->FindChunks(mask);
	}

protected:
	/**
	* @brief 初期化処理
	*/
	virtual void InitSystem() {};

	/**
	* @brief 終了処理
	*/
	virtual void UninitSystem() {};

	/**
	* @brief エンティティ操作用
	*/
	IEntityOperator* m_entity_operator;

	/**
	* @brief システム取得用
	*/
	ISystemDistributor* m_system_distributor;

	/**
	* @brief チャンク取得用
	*/
	IChunkProvider* m_chunk_provider;
};

} // namespace HaraProject::Framework

#endif // !_SYSTEM_BASE_H_
