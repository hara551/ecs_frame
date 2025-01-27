#include "Velocity.h"

namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
*/
Velocity::Velocity()
	: linearVelocity(0.0f,0.0f,0.0f)
	, angularVelocity(0.0f,0.0f,0.0f)
{
}

/**
* @brief �R�s�[�R���X�g���N�^
* @param[in] base Velocity�����������N���X�|�C���^
*/
Velocity::Velocity(ComponentDataBase* base)
{
	auto* value = dynamic_cast<Velocity*>(base);
	linearVelocity = value->linearVelocity;
	angularVelocity = value->angularVelocity;
}

/**
* @brief Json�f�[�^����l��ݒ肷��
* @param[in] json json�I�u�W�F�N�g
*/
void Velocity::SetDataFromJson(nlohmann::json jsonData)
{
	linearVelocity = DirectX::XMFLOAT3(
		jsonData[VELOCITY_LINEAR_VELOCITY_NAME][0],
		jsonData[VELOCITY_LINEAR_VELOCITY_NAME][1],
		jsonData[VELOCITY_LINEAR_VELOCITY_NAME][2]
	);
	angularVelocity = DirectX::XMFLOAT3(
		jsonData[VELOCITY_ANGULAR_VELOCITY_NAME][0],
		jsonData[VELOCITY_ANGULAR_VELOCITY_NAME][1],
		jsonData[VELOCITY_ANGULAR_VELOCITY_NAME][2]
	);
}

#ifdef _DEBUG
/**
* @brief ���݂̒l��Json�f�[�^�ɕϊ�����
*/
nlohmann::json Velocity::WriteDataToJson()
{
	nlohmann::json jsonData;

	jsonData[VELOCITY_NAME][VELOCITY_LINEAR_VELOCITY_NAME] = { linearVelocity.x,linearVelocity.y,linearVelocity.z };
	jsonData[VELOCITY_NAME][VELOCITY_ANGULAR_VELOCITY_NAME] = { angularVelocity.x,angularVelocity.y,angularVelocity.z };

	return jsonData;
}

/**
* @brief �C���X�y�N�^�\�\���쐬
*/
GuiItemBase* Velocity::CreateDetailContent(GuiManager* guiManager)
{
	GuiTreeNode* transform_gui = guiManager->CreateGuiTreeNode(VELOCITY_NAME, "id");
	transform_gui->AddChildren(
		guiManager->CreateGuiInputDragFloat3(VELOCITY_LINEAR_VELOCITY_NAME, "id", &linearVelocity, 0.1f),
		guiManager->CreateGuiInputDragFloat3(VELOCITY_ANGULAR_VELOCITY_NAME, "id", &angularVelocity, 0.1f)
	);
	return transform_gui;
};
#endif // _DEBUG

}//!HaraProject::Framework