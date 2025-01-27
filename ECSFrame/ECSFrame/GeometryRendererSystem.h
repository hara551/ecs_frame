/**
* @file   GeometryRendererSystem.h
* @brief  立体描画システム.
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
	* @brief 立体の種類
	*/
	enum GeometryType
	{
		Box,
		Sphere
	};

	/**
	* @brief 登録用システム名
	*/
	static inline const char* GEOMETRY_RENDER_SYSTEM = "GeometryRendererSystem";

	/**
	* @brief コンストラクタ
	*/
	GeometryRendererSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief システム更新
	*/
	void UpdateSystem(float deltaTime)override;
};

} // namespace HaraProject::Framework

#endif // !_GEOMETRY_RENDERER_SYSTEM_H_