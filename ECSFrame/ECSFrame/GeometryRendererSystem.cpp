#include <vector>

#include "GeometryRendererSystem.h"
#include "SystemBase.h"
#include "ComponentMask.h"
#include "ComponentDataChunk.h"
#include "DirectX.h"
#include "Transform.h"
#include "GeometrySolid.h"
#include "Geometory.h"
#include "CameraDccSystem.h"
#include "CameraManagerSystem.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
GeometryRendererSystem::GeometryRendererSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: SystemBase(entityOperator,systemDistributor,chunkProvider)
{
}

/**
* @brief システム更新
*/
void GeometryRendererSystem::UpdateSystem(float deltaTime)
{
	// チャンク取得
	std::vector<ComponentDataChunk*> chunks = FindChunks<Transform, GeometrySolid>();
	if (chunks.empty())return;

	// 現在のメインカメラ取得
	CameraManagerSystem* camera_manager = reinterpret_cast<CameraManagerSystem*>(
		m_system_distributor->FindSystem(CameraManagerSystem::CAMERA_MANAGER_SYSTEM)
		);
	CameraSystemBase* main_camera = camera_manager->GetCamera(CameraManagerSystem::MainCamera);
	if (main_camera == nullptr)return;

	// ビューとプロジェクションを取得
	Geometory::SetView(main_camera->GetViewMatrix());
	Geometory::SetProjection(main_camera->GetProjectionMatrix());

	for (auto& chunk : chunks)
	{
		// チャンク内の先頭の各種コンポーネントデータを取得
		Transform* transform = reinterpret_cast<Transform*>(chunk->CalculateComponentDataPointer(ComponentMask<Transform>::bit, 0));
		GeometrySolid* solid = reinterpret_cast<GeometrySolid*>(chunk->CalculateComponentDataPointer(ComponentMask<GeometrySolid>::bit, 0));

		uint32_t num_entities = chunk->GetNumEntities();
		for (int i = 0; i < num_entities; ++i)
		{
			if (transform->IsAble() && transform != nullptr)
			{
				// ワールド座標変換
				DirectX::XMFLOAT4X4 world{};
				DirectX::XMStoreFloat4x4(&world,
					DirectX::XMMatrixTranspose(
						DirectX::XMMatrixScaling(transform->scale.x, transform->scale.y, transform->scale.z) *
						DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(transform->rotation.x)) *
						DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(transform->rotation.y)) *
						DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(transform->rotation.z)) *
						DirectX::XMMatrixTranslation(transform->position.x,	transform->position.y, transform->position.z)
					)
				);
				Geometory::SetWorld(world);
				Geometory::SetColor(solid->color);

				RenderTarget* pRTV = GetDefaultRTV();
				DepthStencil* pDSV = GetDefaultDSV();
				SetRenderTargets(1, &pRTV, pDSV);

				SetCullingMode(CULL_NONE);

				switch (solid->geometryNum)
				{
				case Box: Geometory::DrawBox(); break;
				case Sphere: Geometory::DrawSphere(); break;
				default:
					break;
				}

				SetCullingMode(CULL_FRONT);
			}
			++transform;
			++solid;
		}
	}
}

}//!HaraProject::Framework