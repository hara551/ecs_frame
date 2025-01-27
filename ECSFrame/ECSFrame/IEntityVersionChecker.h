/**
* @file   IEntityVersionChecker.h
* @brief  エンティティ有効判定インターフェース.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _IENTITY_VERSION_CHECKER_H_
#define _IENTITY_VERSION_CHECKER_H_

#include <cstdint>

class IEntityVersionChecker
{
public:
	/**
	* @brief デストラクタ
	*/
	virtual ~IEntityVersionChecker() = default;

	/**
	* @brief 有効なエンティティか
	* @param[in] id エンティティID
	* @param[in] version バージョン
	*/
	virtual bool IsValidEntity(uint32_t id, uint32_t version) = 0;
};

#endif // !_IENTITY_VERSION_CHECKER_H_
