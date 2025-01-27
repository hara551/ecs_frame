/**
* @file   ModelRendererSystem.h
* @brief  スプライト描画システム.
* @author Hara Sota.
* @date   //
*/
#ifndef _MODEL_RENDERER_SYSTEM_H_
#define _MODEL_RENDERER_SYSTEM_H_

#include <memory>

#include "SystemBase.h"
#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"
#include "Shader.h"

namespace HaraProject::Framework {

class ModelRendererSystem : public SystemBase
{
public:
	/**
	* @brief 登録用システム名
	*/
	static inline const char* MODEL_RENDERER_SYSTEM = "ModelRendererSystem";

	/**
	* @brief コンストラクタ
	*/
	ModelRendererSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief システム更新
	*/
	void UpdateSystem(float deltaTime)override;

private:
	std::shared_ptr<VertexShader> m_default_vertex_shader;
	std::shared_ptr <PixelShader> m_default_pixel_shader;

	VertexShader* m_current_vertex_shader;
	PixelShader* m_current_pixel_shader;
};

} // namespace HaraProject::Framework

#endif // !_MODEL_RENDERER_SYSTEM_H_