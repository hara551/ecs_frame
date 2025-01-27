/**
* @file   CollisionCircle2D.h
* @brief�@2D�����蔻��p�T�[�N��
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COLLISION_CIRCLE_2D_H_
#define _COLLISION_CIRCLE_2D_H_

#include <DirectXMath.h>

#include <memory>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat3.h"
#endif // _DEBUG

#include "ComponentDataBase.h"

namespace HaraProject::Framework
{

class CollisionCircle2D : public ComponentDataBase
{
public:
	/**
	* @brief �f�[�^��
	*/
	static constexpr const char* COLLISION_CIRCLE_2D_NAME = "CollisionCircle2D";
	static constexpr const char* COLLISION_CIRCLE_2D_CENTER_NAME = "center";
	static constexpr const char* COLLISION_CIRCLE_2D_RADIUS_NAME = "radius";

	/**
	* @brief �f�t�H���g�R���X�g���N�^
	*/
	CollisionCircle2D() = default;

	/**
	* @brief �R�s�[�R���X�g���N�^
	* @param[in] base Transform�����������N���X�|�C���^
	*/
	CollisionCircle2D(ComponentDataBase* base)
	{
		CollisionCircle2D* value = dynamic_cast<CollisionCircle2D*>(base);
		center = value->center;
		radius = value->radius;
	}

	/**
	* @brief Json�f�[�^����l��ݒ肷��
	* @param[in] json json�I�u�W�F�N�g
	*/
	void SetDataFromJson(nlohmann::json jsonData)override
	{
		center = DirectX::XMFLOAT2(
			jsonData[COLLISION_CIRCLE_2D_CENTER_NAME][0],
			jsonData[COLLISION_CIRCLE_2D_CENTER_NAME][1]
		);
		radius = jsonData[COLLISION_CIRCLE_2D_RADIUS_NAME];
	}

#ifdef _DEBUG
	/**
	* @brief ���݂̒l��Json�f�[�^�ɕϊ�����
	*/
	nlohmann::json WriteDataToJson()override
	{
		nlohmann::json jsonData;

		jsonData[COLLISION_CIRCLE_2D_NAME][COLLISION_CIRCLE_2D_CENTER_NAME] = { center.x,center.y };
		jsonData[COLLISION_CIRCLE_2D_NAME][COLLISION_CIRCLE_2D_RADIUS_NAME] = radius;

		return jsonData;
	}

	/**
	* @brief �C���X�y�N�^�\�\���쐬
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override
	{
		GuiTreeNode* transform_gui = guiManager->CreateGuiTreeNode(COLLISION_CIRCLE_2D_NAME, "id");
		transform_gui->AddChildren(
			guiManager->CreateGuiInputFloat2(COLLISION_CIRCLE_2D_CENTER_NAME, "id", &center, 0.1f),
			guiManager->CreateGuiInputDragFloat(COLLISION_CIRCLE_2D_RADIUS_NAME, "id", &radius, 0.1f,0.1f,2000.0f)
		);
		return transform_gui;
	};
#endif // _DEBUG

	/**
	* @brief ���[�J����Ԃł̒����ʒu
	*/
	DirectX::XMFLOAT2 center;

	/**
	* @brief ���a
	*/
	float radius;
};

}// !namespace HaraProject::Framework

#endif // !_COLLISION_CIRCLE_2D_H_