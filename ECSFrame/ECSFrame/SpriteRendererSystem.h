/**
* @file   SpriteRendererSystem.h
* @brief  スプライト描画システム.
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
	* @brief 登録用システム名
	*/
	static inline const char* SPRITE_RENDERER_SYSTEM = "SpriteRendererSystem";

	/**
	* @brief コンストラクタ
	*/
	SpriteRenderSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
		:SystemBase(entityOperator, systemDistributor, chunkProvider){}

	/**
	* @brief システム更新
	*/
	void UpdateSystem(float deltaTime)override;
};

} // namespace HaraProject::Framework

#endif // !_SPRITE_RENDERER_SYSTEM_H_