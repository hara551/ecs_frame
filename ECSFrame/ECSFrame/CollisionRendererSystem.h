/**
* @file   CollisionRendererSystem.h
* @brief  �R���W�����`��.
* @author Hara Sota.
* @date   //
*/
#ifndef _COLLISION_RENDERER_SYSTEM_H_
#define _COLLISION_RENDERER_SYSTEM_H_

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

class CollisionRendererSystem : public SystemBase
{
public:
	/**
	* @brief �o�^�p�V�X�e����
	*/
	static inline const char* COLLISION_RENDERER_SYSTEM = "CollisionRendererSystem";

	/**
	* @brief �R���X�g���N�^
	*/
	CollisionRendererSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief �V�X�e���X�V
	*/
	void UpdateSystem(float deltaTime)override;

#ifdef _DEBUG
	/**
	* @brief Gui�Ƃ��ĕ\������I�v�V�����̍쐬
	*/
	GuiItemBase* CreateGuiOption(GuiManager* guiManager) {
		GuiItemBase* item = guiManager->CreateGuiTreeNode(COLLISION_RENDERER_SYSTEM, "id");
		//item->AddChildren(
		//	guiManager->CreateGuiCheckBox("Enable", "id", &m_is_draw_grid),
		//	guiManager->CreateGuiCheckBox("Axis", "id", &m_is_draw_axis),
		//	guiManager->CreateGuiInputFloat("Size", "id", &m_grid_size),
		//	guiManager->CreateGuiInputFloat("Margin", "id", &m_grid_margin),
		//	guiManager->CreateGuiInputColor("Color", "id", &m_grid_color)
		//);
		return item;
	}
#endif // _DEBUG

private:
	/**
	* @brief �R���W������`�悷�邩
	*/
	bool m_is_draw_collision;
};

} // namespace HaraProject::Framework

#endif // !_COLLISION_RENDERER_SYSTEM_H_