/**
* @file   BoxCollisionSystem.h
* @brief  ボックスの当たり判定システム.
* @author Hara Sota.
* @date   //
*/
#ifndef _BOX_COLLISION_SYSTEM_H_
#define _BOX_COLLISION_SYSTEM_H_

#include "SystemBase.h"

#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"

#include "CollisionBox.h"
#include "CollisionResult.h"
#include "Transform.h"

namespace HaraProject::Framework {

class BoxCollisionSystem : public SystemBase
{
public:
	/**
	* @brief 登録用システム名
	*/
	static inline const char* BOX_COLLISION_SYSTEM = "BoxCollisionSystem";

	/**
	* @brief コンストラクタ
	*/
	BoxCollisionSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief システム更新
	*/
	void UpdateSystem(float deltaTime)override;

	/**
	* @brief AABB衝突判定
	*/
	bool CheckCollisionAABB(CollisionBox* collisionBoxA, Transform* transformA, CollisionBox* collisionBoxB, Transform* transformB);

	/**
	* @brief OBB衝突判定
	*/
	bool CheckcollisionOBB(CollisionBox* collisionBoxA, Transform* transformA, CollisionBox* collisionBoxB, Transform* transformB);
};

} // namespace HaraProject::Framework

#endif // !_BOX_COLLISION_SYSTEM_H_