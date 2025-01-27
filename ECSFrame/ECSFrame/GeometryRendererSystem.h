/**
* @file   GeometryRendererSystem.h
* @brief  ���̕`��V�X�e��.
* @author Hara Sota.
* @date   //
*/
#ifndef _GEOMETRY_RENDERER_SYSTEM_H_
#define _GEOMETRY_RENDERER_SYSTEM_H_

#include "SystemBase.h"

#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"

namespace HaraProject::Framework {

class GeometryRendererSystem : public SystemBase
{
public:
	/**
	* @brief ���̂̎��
	*/
	enum GeometryType
	{
		Box,
		Sphere
	};

	/**
	* @brief �o�^�p�V�X�e����
	*/
	static inline const char* GEOMETRY_RENDER_SYSTEM = "GeometryRendererSystem";

	/**
	* @brief �R���X�g���N�^
	*/
	GeometryRendererSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief �V�X�e���X�V
	*/
	void UpdateSystem(float deltaTime)override;
};

} // namespace HaraProject::Framework

#endif // !_GEOMETRY_RENDERER_SYSTEM_H_