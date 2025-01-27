#include <DirectXMath.h>

#include "Transform.h"

namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
*/
Transform::Transform()
    : position(0.0f, 0.0f, 0.0f)
    , rotation(0.0f, 0.0f, 0.0f)
    , scale(1.0f, 1.0f, 1.0f) {
}

/**
* @brief �R�s�[�R���X�g���N�^
* @param[in] base Transform�����������N���X�|�C���^
*/
Transform::Transform(ComponentDataBase* base) {
    Transform* value = dynamic_cast<Transform*>(base);
    position = value->position;
    rotation = value->rotation;
    scale = value->scale;
}

/**
* @brief Json�f�[�^����l��ݒ肷��
* @param[in] json json�I�u�W�F�N�g
*/
void Transform::SetDataFromJson(nlohmann::json jsonData) {
    position = DirectX::XMFLOAT3(
        jsonData[TRANSFORM_POSITION_NAME][0],
        jsonData[TRANSFORM_POSITION_NAME][1],
        jsonData[TRANSFORM_POSITION_NAME][2]);
    rotation = DirectX::XMFLOAT3(
        jsonData[TRANSFORM_ROTATION_NAME][0],
        jsonData[TRANSFORM_ROTATION_NAME][1],
        jsonData[TRANSFORM_ROTATION_NAME][2]);
    scale = DirectX::XMFLOAT3(
        jsonData[TRANSFORM_SCALE_NAME][0],
        jsonData[TRANSFORM_SCALE_NAME][1],
        jsonData[TRANSFORM_SCALE_NAME][2]);
}

/**
* @brief ���[���h�ϊ��s����쐬
*/
DirectX::XMFLOAT4X4& Transform::CaluculateWorldMatrix() {
    DirectX::XMFLOAT4X4 world{};
    DirectX::XMStoreFloat4x4(&world,
        DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
        DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(rotation.x)) *
        DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(rotation.y)) *
        DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(rotation.z)) *
        DirectX::XMMatrixTranslation(position.x, position.y, position.z));
    return world;
}

/**
* @brief == �I�[�o�[���[�h
*/
bool Transform::operator==(const Transform& other) const {
    return MathUtil::Float3Equals(position, other.position) &&
        MathUtil::Float3Equals(rotation, other.rotation) &&
        MathUtil::Float3Equals(scale, other.scale);
}

/**
* @brief != �I�[�o�[���[�h
*/
bool Transform::operator!=(const Transform& other) const {
    return !(*this == other);
}

#ifdef _DEBUG
/**
* @brief ���݂̒l��Json�f�[�^�ɕϊ�����
*/
nlohmann::json Transform::WriteDataToJson() {
    nlohmann::json jsonData;

    jsonData[TRANSFORM_NAME][TRANSFORM_POSITION_NAME] = { position.x, position.y, position.z };
    jsonData[TRANSFORM_NAME][TRANSFORM_ROTATION_NAME] = { rotation.x, rotation.y, rotation.z };
    jsonData[TRANSFORM_NAME][TRANSFORM_SCALE_NAME] = { scale.x, scale.y, scale.z };

    return jsonData;
}

/**
* @brief �C���X�y�N�^�\�\���쐬
*/
GuiItemBase* Transform::CreateDetailContent(GuiManager* guiManager) {
    GuiTreeNode* transform_gui = guiManager->CreateGuiTreeNode(TRANSFORM_NAME, "id");
    transform_gui->AddChildren(
        guiManager->CreateGuiInputDragFloat3(TRANSFORM_POSITION_NAME, "id", &position, 0.1f),
        guiManager->CreateGuiInputDragFloat3(TRANSFORM_ROTATION_NAME, "id", &rotation, 0.1f),
        guiManager->CreateGuiInputDragFloat3(TRANSFORM_SCALE_NAME, "id", &scale, 0.1f));
    return transform_gui;
}
#endif // _DEBUG

} // namespace HaraProject::Framework
