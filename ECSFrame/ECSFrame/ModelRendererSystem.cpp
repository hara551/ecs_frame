#include <DirectXMath.h>

#include <vector>
#include <cstdint>

#include "ComponentMask.h"
#include "ComponentDataChunk.h"
#include "DirectX.h"
#include "Model.h"

#include "ModelHandle.h"
#include "Transform.h"

#include "ModelRendererSystem.h"
#include "CameraManagerSystem.h"
#include "CameraSystemBase.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
HaraProject::Framework::ModelRendererSystem::ModelRendererSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	:SystemBase(entityOperator, systemDistributor, chunkProvider) 
{
	m_default_vertex_shader = std::make_shared<VertexShader>();
	m_default_vertex_shader->Load("Assets/Shader/VS_Model.cso");
	m_current_vertex_shader = m_default_vertex_shader.get();

	m_default_pixel_shader = std::make_shared<PixelShader>();
	m_default_pixel_shader->Load("Assets/Shader/PS_TexColor.cso");
	m_current_pixel_shader = m_default_pixel_shader.get();
}

/**
* @brief システム更新
*/
void ModelRendererSystem::UpdateSystem(float deltaTime)
{
	// トランスフォームとモデルハンドルの複合ビットを作成
	ComponentBits transform_bit = ComponentMask<Transform>::bit;
	ComponentBits model_handle_bit = ComponentMask<ModelHandle>::bit;
	ComponentBits mask = transform_bit | model_handle_bit;

	// トランスフォームとモデルハンドルを含むチャンクを全て取得
	std::vector<ComponentDataChunk*> chunks = m_chunk_provider->FindChunks(mask);
	if (chunks.empty())return;

	// 現在のメインカメラ取得
	CameraManagerSystem* camera_manager = reinterpret_cast<CameraManagerSystem*>(
		m_system_distributor->FindSystem(CameraManagerSystem::CAMERA_MANAGER_SYSTEM)
	);
	CameraSystemBase* main_camera = camera_manager->GetCamera(CameraManagerSystem::MainCamera);
	if (main_camera == nullptr)return;


	// ビューとプロジェクションを取得
	DirectX::XMFLOAT4X4 matrix[MAX_MATRIX];
	matrix[ViewMatrix] = main_camera->GetViewMatrix();
	matrix[ProjectionMatrix] = main_camera->GetProjectionMatrix();

	for (auto& chunk : chunks)
	{
		// チャンク内の先頭の各種コンポーネントデータを取得
		ModelHandle* model_handle = reinterpret_cast<ModelHandle*>(chunk->CalculateComponentDataPointer(model_handle_bit, 0));
		Transform* transform = reinterpret_cast<Transform*>(chunk->CalculateComponentDataPointer(transform_bit, 0));

		uint32_t num_entities = chunk->GetNumEntities();
		for (int i = 0; i < num_entities; ++i)
		{
			if (!model_handle->IsAble() || model_handle == nullptr ||
				!transform->IsAble() || transform == nullptr ||
				model_handle->model == nullptr)
			{
				++model_handle;
				++transform;
				continue;
			}

			// ワールド座標変換
			DirectX::XMStoreFloat4x4(&matrix[WorldMatrix],
				DirectX::XMMatrixTranspose(
					DirectX::XMMatrixScaling(transform->scale.x, transform->scale.y, transform->scale.z) *
					DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(transform->rotation.x)) *
					DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(transform->rotation.y)) *
					DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(transform->rotation.z)) *
					DirectX::XMMatrixTranslation(transform->position.x, transform->position.y, transform->position.z))
			);

			if (m_current_vertex_shader == nullptr)
			{
				m_current_vertex_shader = m_default_vertex_shader.get();
			}
			if (m_current_pixel_shader == nullptr)
			{
				m_current_pixel_shader = m_default_pixel_shader.get();
			}

			// 定数バッファ更新
			m_current_vertex_shader->WriteBuffer(0, matrix);
			m_current_vertex_shader->Bind();

			model_handle->model->SetVertexShader(m_current_vertex_shader);
			model_handle->model->SetPixelShader(m_current_pixel_shader);

			RenderTarget* pRTV = GetDefaultRTV();
			DepthStencil* pDSV = GetDefaultDSV();
			SetRenderTargets(1, &pRTV, pDSV);

			model_handle->model->Draw();

			++model_handle;
			++transform;
		}
	}
}

} // namespace HaraProject::Framework