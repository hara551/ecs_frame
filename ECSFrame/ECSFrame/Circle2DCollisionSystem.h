/**
* @file   Circle2DCollisionSystem.h
* @brief  2Dサークルの当たり判定システム.
* @author Hara Sota.
* @date   //
*/
#ifndef _CIRCLE_2D_COLLISION_SYSTEM_H_
#define _CIRCLE_2D_COLLISION_SYSTEM_H_

#include "SystemBase.h"

#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"

#include "CollisionBase.h"
#include "CollisionCircle2D.h"
#include "Transform.h"

namespace HaraProject::Framework {

class Circle2DCollisionSystem : public SystemBase
{
public:
	/**
	* @brief 登録用システム名
	*/
	static inline const char* CIRCLE_2D_COLLISION_SYSTEM = "Circle2DCollisionSystem";

	/**
	* @brief コンストラクタ
	*/
	Circle2DCollisionSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief システム更新
	*/
	void UpdateSystem(float deltaTime)override;

	/**
	* @brief 円衝突判定
	*/
	bool CheckCollisionCircle(CollisionCircle2D* collisionBoxA, Transform* transformA, CollisionCircle2D* collisionBoxB, Transform* transformB);
};

} // namespace HaraProject::Framework

#endif // !_CIRCLE_2D_COLLISION_SYSTEM_H_