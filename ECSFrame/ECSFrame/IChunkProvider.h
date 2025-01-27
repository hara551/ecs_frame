/**
* @file   IChunkProvider.h
* @brief  チャンク取得操作インターフェース.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _ICHUNK_PROVIDER_H_
#define _ICHUNK_PROVIDER_H_

#include <cstdint>
#include <vector>

#include "ComponentMask.h"
#include "ComponentDataChunk.h"

namespace HaraProject::Framework
{

/**
* @brief　コンポーネントデータ操作インターフェース
*/
class IChunkProvider
{
public:
	/**
	* @brief デストラクタ
	*/
	virtual ~IChunkProvider() = default;

	/**
	* @brief 指定の組のコンポーネントデータを取り扱うチャンクを取得
	*/
	virtual std::vector<ComponentDataChunk*> FindChunks(ComponentBits mask) = 0;
};

}// !namespace HaraProject::Framework

#endif // !_ICHUNK_PROVIDER_H_