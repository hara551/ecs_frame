/**
* @file   GeometrySolid.h
* @brief  �􉽗��̃R���|�[�l���g�f�[�^.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _GEOMETRY_SOLID_H_
#define _GEOMETRY_SOLID_H_

#include <DirectXMath.h>

#include <memory>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat3.h"
#endif // _DEBUG

#include "MathUtil.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework {

class GeometrySolid : public ComponentDataBase
{
public:
	/**
	* @brief �f�[�^��
	*/
	static constexpr const char* GEOMETRY_SOLID_NAME = "GeometrySolid";
	static constexpr const char* GEOMETRY_SOLID_GEOMETRY_NUM = "geometryNum";
	static constexpr const char* GEOMETRY_SOLID_COLOR_NAME = "color";

	/**
	* @brief �R���X�g���N�^
	*/
	GeometrySolid();

	/**
	* @brief �R�s�[�R���X�g���N�^
	* @param[in] base GeometrySolid�����������N���X�|�C���^
	*/
	GeometrySolid(ComponentDataBase* base);

	/**
	* @brief �f�X�g���N�^
	*/
	~GeometrySolid() = default;

	/**
	* @brief Json�f�[�^����l��ݒ肷��
	* @param[in] json json�I�u�W�F�N�g
	*/
	void SetDataFromJson(nlohmann::json jsonData)override;

	/**
	* @brief ���̔ԍ�
	*/
	int geometryNum;

	/**
	* @breif �`��F
	*/
	DirectX::XMFLOAT4 color;

#ifdef _DEBUG
	/**
	* @brief ���݂̒l��Json�f�[�^�ɕϊ�����
	*/
	nlohmann::json WriteDataToJson()override
	{
		nlohmann::json jsonData;

		jsonData[GEOMETRY_SOLID_NAME][GEOMETRY_SOLID_GEOMETRY_NUM] = geometryNum;
		jsonData[GEOMETRY_SOLID_NAME][GEOMETRY_SOLID_COLOR_NAME] = { color.x,color.y,color.z,color.w };

		return jsonData;
	}

	/**
	* @brief �C���X�y�N�^�\�\���쐬
	*/
	GuiItemBase* CreateDetailContent(GuiManager* guiManager)override
	{
		GuiTreeNode* gui = guiManager->CreateGuiTreeNode(GEOMETRY_SOLID_NAME, "id");
		gui->AddChildren(
			guiManager->CreateGuiInputInt(GEOMETRY_SOLID_GEOMETRY_NUM, "id", &geometryNum),
			guiManager->CreateGuiInputColor(GEOMETRY_SOLID_COLOR_NAME, "id", &color)
		);
		return gui;
	};
#endif // _DEBUG
};

}// !namespace HaraProject::Framework

#endif // !_GEOMETRY_SOLID_H_