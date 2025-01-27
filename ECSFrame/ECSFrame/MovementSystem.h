/**
* @file   MovementSystem.h
* @brief  �g�����X�t�H�[���X�V�V�X�e��.
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
	* @brief �o�^�p�V�X�e����
	*/
	static inline const char* MOVEMENT_SYSTEM = "MovementSystem";

	/**
	* @brief �R���X�g���N�^
	*/
	MovementSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief �V�X�e���X�V
	*/
	void UpdateSystem(float deltaTime)override;
};

} // namespace HaraProject::Framework

#endif // !_MOVEMENT_SYSTEM_H_