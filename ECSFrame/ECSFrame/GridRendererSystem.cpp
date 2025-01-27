#include <DirectXMath.h>

#include "GridRendererSystem.h"
#include "SystemBase.h"
#include "CameraManagerSystem.h"
#include "CameraSystemBase.h"
#include "DirectX.h"
#include "Geometory.h"

namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
GridRendererSystem::GridRendererSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: SystemBase(entityOperator,systemDistributor, chunkProvider)
	, m_is_draw_grid(true)
	, m_grid_margin(1.0f)
	, m_grid_size(50.0f)
	, m_grid_color(0.9f, 0.9f, 0.9f, 1.0f)
	, m_is_draw_axis(true)
{
}

/**
* @brief システム更新
*/
void GridRendererSystem::UpdateSystem(float deltaTime)
{
	if (!m_is_draw_grid)return;

	// 現在のメインカメラ取得
	CameraManagerSystem* camera_manager = reinterpret_cast<CameraManagerSystem*>(
		m_system_distributor->FindSystem(CameraManagerSystem::CAMERA_MANAGER_SYSTEM)
		);
	CameraSystemBase* main_camera = camera_manager->GetCamera(CameraManagerSystem::MainCamera);
	if (main_camera == nullptr)return;

	DirectX::XMFLOAT4X4 matrix[MAX_MATRIX];

	Geometory::SetView(main_camera->GetViewMatrix());
	Geometory::SetProjection(main_camera->GetProjectionMatrix());

	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixIdentity());
	Geometory::SetWorld(world);

	Geometory::SetColor(m_grid_color);
	float d = m_grid_margin;
	float s = m_grid_size;
	while (s >= m_grid_margin && m_grid_margin > 0.0f)
	{
		Geometory::AddLine(DirectX::XMFLOAT3(d, 0.0f, -m_grid_size), DirectX::XMFLOAT3(d, 0.0f, m_grid_size));
		Geometory::AddLine(DirectX::XMFLOAT3(-d, 0.0f, -m_grid_size), DirectX::XMFLOAT3(-d, 0.0f, m_grid_size));
		Geometory::AddLine(DirectX::XMFLOAT3(-m_grid_size, 0.0f, d), DirectX::XMFLOAT3(m_grid_size, 0.0f, d));
		Geometory::AddLine(DirectX::XMFLOAT3(-m_grid_size, 0.0f, -d), DirectX::XMFLOAT3(m_grid_size, 0.0f, -d));
		d += m_grid_margin;
		s -= m_grid_margin;
	}

	if (m_is_draw_axis)
	{
		Geometory::SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
		Geometory::AddLine(DirectX::XMFLOAT3(-m_grid_size, 0.0f, 0.0f), DirectX::XMFLOAT3(m_grid_size, 0.0f, 0.0f));
		Geometory::SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
		Geometory::AddLine(DirectX::XMFLOAT3(0.0f, -m_grid_size, 0.0f), DirectX::XMFLOAT3(0.0f, m_grid_size, 0.0f));
		Geometory::SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
		Geometory::AddLine(DirectX::XMFLOAT3(0.0f, 0.0f, -m_grid_size), DirectX::XMFLOAT3(0.0f, 0.0f, m_grid_size));
	}
	else
	{
		Geometory::AddLine(DirectX::XMFLOAT3(-m_grid_size, 0.0f, 0.0f), DirectX::XMFLOAT3(m_grid_size, 0.0f, 0.0f));
		Geometory::AddLine(DirectX::XMFLOAT3(0.0f, 0.0f, -m_grid_size), DirectX::XMFLOAT3(0.0f, 0.0f, m_grid_size));
	}
	Geometory::DrawLines();
}

}//!namespace HaraProject::Framework