#include <DirectXMath.h>

#include <vector>
#include <cstdint>

#include "SpriteRenderer.h"
#include "SpriteRendererSystem.h"
#include "ComponentMask.h"
#include "ComponentDataChunk.h"
#include "DirectX.h"
#include "Texture.h"

#include "Sprite.h"
#include "Transform.h"

using SpriteRenderer = HAL::SasakiRyota::SpriteRenderer;

namespace HaraProject::Framework {

void SpriteRenderSystem::UpdateSystem(float deltaTime)
{
	// スプライト、トランスフォームの複合ビットを作成
	ComponentBits sprite_bit = ComponentMask<Sprite>::bit;
	ComponentBits transform_bit = ComponentMask<Transform>::bit;
	ComponentBits mask = sprite_bit | transform_bit;
	// スプライト、トランスフォームを含むチャンクを全て取得
	std::vector<ComponentDataChunk*> chunks = m_chunk_provider->FindChunks(mask);
	if (chunks.empty())return;

	// レンダーターゲットを設定
	RenderTarget* rtv = GetDefaultRTV();
	DepthStencil* dsv = GetDefaultDSV();
	SetRenderTargets(1, &rtv, nullptr);
	SetCullingMode(CULL_NONE);

	for (const auto& chunk : chunks)
	{
		// チャンク内の先頭の各種コンポーネントデータを取得
		Sprite* sprite = reinterpret_cast<Sprite*>(chunk->CalculateComponentDataPointer(sprite_bit, 0));
		Transform* transform = reinterpret_cast<Transform*>(chunk->CalculateComponentDataPointer(transform_bit, 0));

		uint32_t num_entities = chunk->GetNumEntities();
		for(int i = 0; i < num_entities; ++i)
		{
			if (!sprite->IsAble() || sprite == nullptr ||
				!transform->IsAble() || transform == nullptr)
			{
				++sprite;
				++transform;
				continue;
			}

			DirectX::XMFLOAT4X4 matrix[MAX_MATRIX];

			DirectX::XMMATRIX world =
				DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(transform->rotation.x)) *
				DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(transform->rotation.y)) *
				DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(transform->rotation.z)) *
				DirectX::XMMatrixTranslation(transform->position.x, transform->position.y, 0.0f);
			DirectX::XMStoreFloat4x4(&matrix[WorldMatrix], DirectX::XMMatrixTranspose(world));

			DirectX::XMStoreFloat4x4(&matrix[ViewMatrix], DirectX::XMMatrixIdentity());

			DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
				0, 1280, 720, 0, 1, 100
			);
			DirectX::XMStoreFloat4x4(&matrix[ProjectionMatrix], DirectX::XMMatrixTranspose(proj));

			SpriteRenderer::SetWorld(matrix[WorldMatrix]);
			SpriteRenderer::SetView(matrix[ViewMatrix]);
			SpriteRenderer::SetProjection(matrix[ProjectionMatrix]);
			SpriteRenderer::SetSize(DirectX::XMFLOAT2(sprite->textureSize.x, -sprite->textureSize.y));
			SpriteRenderer::SetUVPos(sprite->uvPosition);
			SpriteRenderer::SetUVScale(sprite->uvScale);
			SpriteRenderer::SetColor(sprite->textureColor);
			SpriteRenderer::SetTexture(sprite->texture);
			SpriteRenderer::Draw();

			++sprite;
			++transform;
		}
	}
}

} // namespace HaraProject::Framework