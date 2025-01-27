/**
* @file   SpriteRendererSystem.h
* @brief  �X�v���C�g�`��V�X�e��.
* @author Hara Sota.
* @date   //
*/
#ifndef _SPRITE_RENDERER_SYSTEM_H_
#define _SPRITE_RENDERER_SYSTEM_H_

#include "SystemBase.h"

#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"

namespace HaraProject::Framework {

class SpriteRenderSystem : public SystemBase
{
public:
	/**
	* @brief �o�^�p�V�X�e����
	*/
	static inline const char* SPRITE_RENDERER_SYSTEM = "SpriteRendererSystem";

	/**
	* @brief �R���X�g���N�^
	*/
	SpriteRenderSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
		:SystemBase(entityOperator, systemDistributor, chunkProvider){}

	/**
	* @brief �V�X�e���X�V
	*/
	void UpdateSystem(float deltaTime)override;
};

} // namespace HaraProject::Framework

#endif // !_SPRITE_RENDERER_SYSTEM_H_