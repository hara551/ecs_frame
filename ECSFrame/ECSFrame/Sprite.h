/**
* @file   Sprite.h
* @brief  �X�v���C�g�R���|�[�l���g�f�[�^��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <DirectXMath.h>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputFloat2.h"
#include "GuiInputColor.h"
#endif // _DEBUG
#include "GuiInputText.h"

#include "Defines.h"
#include "Texture.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework {

/**
* @brief �X�v���C�g�R���|�[�l���g�f�[�^
*/
class Sprite : public ComponentDataBase {
public:
    /**
    * @brief �f�[�^��
    */
    static constexpr const char* SPRITE_NAME = "Sprite";
    static constexpr const char* SPRITE_TEXTURE_NAME_NAME = "textureName";
    static constexpr const char* SPRITE_TEXTURE_SIZE_NAME = "textureSize";
    static constexpr const char* SPRITE_UV_POSITION_NAME = "uvPosition";
    static constexpr const char* SPRITE_UV_SCALE_NAME = "uvScale";
    static constexpr const char* SPRITE_TEXTURE_COLOR_NAME = "textureColor";

    /**
    * @brief �R���X�g���N�^
    */
    Sprite();

    /**
    * @brief �R�s�[�R���X�g���N�^
    * @param[in] base �R�s�[����Sprite
    */
    Sprite(ComponentDataBase* base);

    /**
    * @brief �f�X�g���N�^
    */
    ~Sprite() = default;

    /**
    * @brief Json�f�[�^����l��ݒ肷��
    * @param[in] json json�I�u�W�F�N�g
    */
    void SetDataFromJson(nlohmann::json jsonData) override;

#ifdef _DEBUG
    /**
    * @brief ���݂̒l��Json�f�[�^�ɕϊ�����
    */
    nlohmann::json WriteDataToJson() override;

    /**
    * @brief �C���X�y�N�^�\�\���쐬
    */
    GuiItemBase* CreateDetailContent(GuiManager* guiManager) override;
#endif // _DEBUG

    /**
    * @brief �e�N�X�`���t�@�C����
    */
    char textureName[GuiInputText::MAX_INPUT_TEXT_LENGTH];

    /**
    * @brief �e�N�X�`���T�C�Y
    */
    DirectX::XMFLOAT2 textureSize;

    /**
    * @brief UV���W
    */
    DirectX::XMFLOAT2 uvPosition;

    /**
    * @brief UV�X�P�[��
    */
    DirectX::XMFLOAT2 uvScale;

    /**
    * @brief �J���[
    */
    DirectX::XMFLOAT4 textureColor;

    /**
    * @brief �e�N�X�`���I�u�W�F�N�g�ւ̃|�C���^
    */
    Texture* texture;
};

} // namespace HaraProject::Framework

#endif // !_SPRITE_H_
