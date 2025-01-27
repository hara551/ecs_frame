/**
* @file   BoxCollisionSystem.h
* @brief  �{�b�N�X�̓����蔻��V�X�e��.
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
	* @brief �o�^�p�V�X�e����
	*/
	static inline const char* BOX_COLLISION_SYSTEM = "BoxCollisionSystem";

	/**
	* @brief �R���X�g���N�^
	*/
	BoxCollisionSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief �V�X�e���X�V
	*/
	void UpdateSystem(float deltaTime)override;

	/**
	* @brief AABB�Փ˔���
	*/
	bool CheckCollisionAABB(CollisionBox* collisionBoxA, Transform* transformA, CollisionBox* collisionBoxB, Transform* transformB);

	/**
	* @brief OBB�Փ˔���
	*/
	bool CheckcollisionOBB(CollisionBox* collisionBoxA, Transform* transformA, CollisionBox* collisionBoxB, Transform* transformB);
};

} // namespace HaraProject::Framework

#endif // !_BOX_COLLISION_SYSTEM_H_