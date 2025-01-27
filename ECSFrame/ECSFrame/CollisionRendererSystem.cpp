#include <DirectXMath.h>

#include "ComponentMask.h"
#include "ComponentDataChunk.h"

#include "CollisionRendererSystem.h"
#include "SystemBase.h"
#include "CameraManagerSystem.h"
#include "CameraSystemBase.h"
#include "DirectX.h"
#include "Geometory.h"

#include "CollisionBox.h"
#include "CollisionBase.h"
#include "Transform.h"
#include "CollisionResult.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
CollisionRendererSystem::CollisionRendererSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: SystemBase(entityOperator, systemDistributor, chunkProvider)
{
}

/**
* @brief システム更新
*/
void CollisionRendererSystem::UpdateSystem(float deltaTime)
{
	std::vector<ComponentDataChunk*> chunks = FindChunks<Transform, CollisionBox, CollisionResult>();
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
		CollisionBox* box = reinterpret_cast<CollisionBox*>(chunk->CalculateComponentDataPointer(ComponentMask<CollisionBox>::bit, 0));
		Transform* transform = reinterpret_cast<Transform*>(chunk->CalculateComponentDataPointer(ComponentMask<Transform>::bit, 0));
		CollisionResult* collision_result = reinterpret_cast<CollisionResult*>(chunk->CalculateComponentDataPointer(ComponentMask<CollisionResult>::bit, 0));

		uint32_t num_entities = chunk->GetNumEntities();
		for (int i = 0; i < num_entities; ++i)
		{
			if (transform->IsAble() && transform != nullptr)
			{
				// ワールド座標変換
				DirectX::XMFLOAT4X4 world{};
				DirectX::XMStoreFloat4x4(&world,
					DirectX::XMMatrixTranspose(
						DirectX::XMMatrixScaling(box->size.x * transform->scale.x, box->size.y * transform->scale.y, box->size.z * transform->scale.z) *
						DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(transform->rotation.x)) *
						DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(transform->rotation.y)) *
						DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(transform->rotation.z)) *
						DirectX::XMMatrixTranslation(
							transform->position.x + box->center.x,
							transform->position.y + box->center.y,
							transform->position.z + box->center.z
						)
					)
				);
				Geometory::SetWorld(world);
				if (collision_result->isCollided)
				{
					Geometory::SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
				}
				else
				{
					Geometory::SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
				}

				if (box->isSelect)
				{
					Geometory::SetColor(DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f));
				}

				RenderTarget* pRTV = GetDefaultRTV();
				DepthStencil* pDSV = GetDefaultDSV();
				SetRenderTargets(1, &pRTV, pDSV);

				SetCullingMode(CULL_NONE);
				SetFillMode(FILL_WIREFRAME);

				Geometory::DrawBox();

				SetFillMode(FILL_SOLID);
				SetCullingMode(CULL_FRONT);

				box->isSelect = false;
			}
			++box;
			++transform;
			++collision_result;
		}
	}
}

} // namespace HaraProject::Framework