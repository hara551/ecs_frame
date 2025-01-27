/**
* @file   Transform.h
* @brief  位置、回転、拡縮コンポーネントデータ定義.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <DirectXMath.h>
#include <memory>

#ifdef _DEBUG
#include "GuiManager.h"
#include "GuiItemBase.h"
#include "GuiTreeNode.h"
#include "GuiInputDragFloat3.h"
#endif // _DEBUG

#include "MathUtil.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework {

/**
* @brief 位置、回転、拡縮コンポーネントデータ
*/
class Transform : public ComponentDataBase {
public:
    /**
    * @brief データ名
    */
    static constexpr const char* TRANSFORM_NAME = "Transform";
    static constexpr const char* TRANSFORM_POSITION_NAME = "position";
    static constexpr const char* TRANSFORM_ROTATION_NAME = "rotation";
    static constexpr const char* TRANSFORM_SCALE_NAME = "scale";

    /**
    * @brief 位置座標
    */
    DirectX::XMFLOAT3 position;

    /**
    * @brief 回転
    */
    DirectX::XMFLOAT3 rotation;

    /**
    * @brief 拡縮
    */
    DirectX::XMFLOAT3 scale;

    /**
    * @brief コンストラクタ
    */
    Transform();

    /**
    * @brief コピーコンストラクタ
    * @param[in] base Transformが入った基底クラスポインタ
    */
    Transform(ComponentDataBase* base);

    /**
    * @brief デストラクタ
    */
    ~Transform() = default;

    /**
    * @brief Jsonデータから値を設定する
    * @param[in] json jsonオブジェクト
    */
    void SetDataFromJson(nlohmann::json jsonData) override;

    /**
    * @brief ワールド変換行列を作成
    */
    DirectX::XMFLOAT4X4& CaluculateWorldMatrix();

    /**
    * @brief == オーバーロード
    */
    bool operator==(const Transform& other) const;

    /**
    * @brief != オーバーロード
    */
    bool operator!=(const Transform& other) const;

#ifdef _DEBUG
    /**
    * @brief 現在の値をJsonデータに変換する
    */
    nlohmann::json WriteDataToJson() override;

    /**
    * @brief インスペクタ―表示作成
    */
    GuiItemBase* CreateDetailContent(GuiManager* guiManager) override;
#endif // _DEBUG
};

} // namespace HaraProject::Framework

#endif // !_TRANSFORM_H_
