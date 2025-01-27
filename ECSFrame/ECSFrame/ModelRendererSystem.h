/**
* @file   ModelRendererSystem.h
* @brief  �X�v���C�g�`��V�X�e��.
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
	* @brief �o�^�p�V�X�e����
	*/
	static inline const char* MODEL_RENDERER_SYSTEM = "ModelRendererSystem";

	/**
	* @brief �R���X�g���N�^
	*/
	ModelRendererSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief �V�X�e���X�V
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