/**
* @file   Circle2DCollisionSystem.h
* @brief  2D�T�[�N���̓����蔻��V�X�e��.
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
	* @brief �o�^�p�V�X�e����
	*/
	static inline const char* CIRCLE_2D_COLLISION_SYSTEM = "Circle2DCollisionSystem";

	/**
	* @brief �R���X�g���N�^
	*/
	Circle2DCollisionSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief �V�X�e���X�V
	*/
	void UpdateSystem(float deltaTime)override;

	/**
	* @brief �~�Փ˔���
	*/
	bool CheckCollisionCircle(CollisionCircle2D* collisionBoxA, Transform* transformA, CollisionCircle2D* collisionBoxB, Transform* transformB);
};

} // namespace HaraProject::Framework

#endif // !_CIRCLE_2D_COLLISION_SYSTEM_H_