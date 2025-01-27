/**
* @file   MovementSystem.h
* @brief  トランスフォーム更新システム.
* @author Hara Sota.
* @date   //
*/
#ifndef _MOVEMENT_SYSTEM_H_
#define _MOVEMENT_SYSTEM_H_

#include "SystemBase.h"

#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"

namespace HaraProject::Framework {

class MovementSystem : public SystemBase
{
public:
	/**
	* @brief 登録用システム名
	*/
	static inline const char* MOVEMENT_SYSTEM = "MovementSystem";

	/**
	* @brief コンストラクタ
	*/
	MovementSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief システム更新
	*/
	void UpdateSystem(float deltaTime)override;
};

} // namespace HaraProject::Framework

#endif // !_MOVEMENT_SYSTEM_H_