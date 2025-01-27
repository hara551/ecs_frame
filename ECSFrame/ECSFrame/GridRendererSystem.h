/**
* @file   GridRendererSystem.h
* @brief  グリッド描画.
* @author Hara Sota.
* @date   //
*/
#ifndef _GRID_RENDERER_SYSTEM_H_
#define _GRID_RENDERER_SYSTEM_H_

#include "SystemBase.h"

#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiCheckBox.h"
#include "GuiInputFloat.h"
#include "GuiInputColor.h"
#endif // _DEBUG


namespace HaraProject::Framework {

class GridRendererSystem : public SystemBase
{
public:
	/**
	* @brief 登録用システム名
	*/
	static inline const char* GRID_RENDERER_SYSTEM = "GridRendererSystem";

	/**
	* @brief コンストラクタ
	*/
	GridRendererSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief システム更新
	*/
	void UpdateSystem(float deltaTime)override;

#ifdef _DEBUG
	/**
	* @brief Guiとして表示するオプションの作成
	*/
	GuiItemBase* CreateGuiOption(GuiManager* guiManager) {
		GuiItemBase* item = guiManager->CreateGuiTreeNode(GRID_RENDERER_SYSTEM, "id");
		item->AddChildren(
			guiManager->CreateGuiCheckBox("Enable", "id", &m_is_draw_grid),
			guiManager->CreateGuiCheckBox("Axis", "id", &m_is_draw_axis),
			guiManager->CreateGuiInputFloat("Size", "id", &m_grid_size),
			guiManager->CreateGuiInputFloat("Margin", "id", &m_grid_margin),
			guiManager->CreateGuiInputColor("Color", "id", &m_grid_color)
		);
		return item;
	}
#endif // _DEBUG

private:
	/**
	* @brief グリッドの一辺のマス目数
	*/
	float m_grid_size;

	/**
	* @brief グリッドの単位マスサイズ
	*/
	float m_grid_margin;

	/**
	* @brief グリッドを描画するか
	*/
	bool m_is_draw_grid;

	/**
	* @brief グリッドの色
	*/
	DirectX::XMFLOAT4 m_grid_color;

	/**
	* @brief 軸を描画するか
	*/
	bool m_is_draw_axis;
};

} // namespace HaraProject::Framework

#endif // !_GRID_RENDERER_SYSTEM_H_