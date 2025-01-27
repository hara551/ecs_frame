#include "Sprite.h"

namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
*/
Sprite::Sprite()
    : texture(nullptr)
    , textureName("nothing")
    , textureSize(100.0f, 100.0f)
    , uvPosition(0.0f, 0.0f)
    , uvScale(1.0f, 1.0f)
    , textureColor(1.0f, 1.0f, 1.0f, 1.0f) {
}

/**
* @brief �R�s�[�R���X�g���N�^
* @param[in] base �R�s�[����Sprite
*/
Sprite::Sprite(ComponentDataBase* base) {
    Sprite* value = dynamic_cast<Sprite*>(base);
    strcpy_s(textureName, value->textureName);
    textureSize = value->textureSize;
    uvPosition = value->uvPosition;
    uvScale = value->uvScale;
    textureColor = value->textureColor;
    texture = nullptr;
}

/**
* @brief Json�f�[�^����l��ݒ肷��
* @param[in] json json�I�u�W�F�N�g
*/
void Sprite::SetDataFromJson(nlohmann::json jsonData) {
    strcpy_s(textureName, std::string(jsonData[SPRITE_TEXTURE_NAME_NAME]).c_str());

    textureSize = DirectX::XMFLOAT2(
        jsonData[SPRITE_TEXTURE_SIZE_NAME][0],
        jsonData[SPRITE_TEXTURE_SIZE_NAME][1]
    );

    uvPosition = DirectX::XMFLOAT2(
        jsonData[SPRITE_UV_POSITION_NAME][0],
        jsonData[SPRITE_UV_POSITION_NAME][1]
    );

    uvScale = DirectX::XMFLOAT2(
        jsonData[SPRITE_UV_SCALE_NAME][0],
        jsonData[SPRITE_UV_SCALE_NAME][1]
    );

    textureColor = DirectX::XMFLOAT4(
        jsonData[SPRITE_TEXTURE_COLOR_NAME][0],
        jsonData[SPRITE_TEXTURE_COLOR_NAME][1],
        jsonData[SPRITE_TEXTURE_COLOR_NAME][2],
        jsonData[SPRITE_TEXTURE_COLOR_NAME][3]
    );
}

#ifdef _DEBUG
/**
* @brief ���݂̒l��Json�f�[�^�ɕϊ�����
*/
nlohmann::json Sprite::WriteDataToJson() {
    nlohmann::json jsonData;

    jsonData[SPRITE_NAME][SPRITE_TEXTURE_NAME_NAME] = std::string(textureName);
    jsonData[SPRITE_NAME][SPRITE_TEXTURE_SIZE_NAME] = { textureSize.x, textureSize.y };
    jsonData[SPRITE_NAME][SPRITE_UV_POSITION_NAME] = { uvPosition.x, uvPosition.y };
    jsonData[SPRITE_NAME][SPRITE_UV_SCALE_NAME] = { uvScale.x, uvScale.y };
    jsonData[SPRITE_NAME][SPRITE_TEXTURE_COLOR_NAME] = {
        textureColor.x, textureColor.y, textureColor.z, textureColor.w
    };

    return jsonData;
}

/**
* @brief �C���X�y�N�^�\�\���쐬
*/
GuiItemBase* Sprite::CreateDetailContent(GuiManager* guiManager) {
    GuiTreeNode* sprite_gui = guiManager->CreateGuiTreeNode(SPRITE_NAME, "id");
    sprite_gui->AddChildren(
        guiManager->CreateGuiInputText(SPRITE_TEXTURE_NAME_NAME, "id", GuiInputBase::Return, textureName),
        guiManager->CreateGuiInputFloat2(SPRITE_TEXTURE_SIZE_NAME, "id", &textureSize),
        guiManager->CreateGuiInputFloat2(SPRITE_UV_POSITION_NAME, "id", &uvPosition),
        guiManager->CreateGuiInputFloat2(SPRITE_UV_SCALE_NAME, "id", &uvScale),
        guiManager->CreateGuiInputColor(SPRITE_TEXTURE_COLOR_NAME, "id", &textureColor)
    );
    return sprite_gui;
}
#endif // _DEBUG

} // namespace HaraProject::Framework
