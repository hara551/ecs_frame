/**
* @file   ComponentMask.h
* @brief  コンポーネントへのビット割り当て.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COMPONENT_MASK_H_
#define _COMPONENT_MASK_H_

#include <bitset>
#include <cstdint>

#include "Transform.h"
#include "EntityName.h"
#include "Sprite.h"
#include "ModelHandle.h"
#include "CollisionBox.h"
#include "Velocity.h"
#include "CollisionResult.h"
#include "GeometrySolid.h"
#include "CollisionCircle2D.h"

namespace HaraProject::Framework {

/**
* @brief コンポーネントデータ最大登録数
*/
static constexpr uint8_t MAX_COMPONENT_DATA = 32;

/**
* @brief コンポーネント識別ビット
*/
using ComponentBits = std::bitset<MAX_COMPONENT_DATA>;

/**
* @brief コンポーネントデータにビット割り当て用テンプレート
* @tparam コンポーネントデータの型
*/
template<typename T> struct ComponentMask {
    static constexpr ComponentBits bit = ComponentBits(0);
};

/**
* @brief ビット割り当ての特殊化マクロ
* @param[in] COMPONENT コンポーネントデータ型
* @param[in] BIT ビット
*/
#define DEFINE_COMPONENT_MASK(COMPONENT, BIT) \
template<> struct ComponentMask<COMPONENT> { \
static constexpr ComponentBits bit = ComponentBits(BIT); \
}; \

// ----------------------------------------------------------------
// コンポーネントデータ追加欄
// ----------------------------------------------------------------
DEFINE_COMPONENT_MASK(Transform, 1 << 1);
DEFINE_COMPONENT_MASK(EntityName, 1 << 2);
DEFINE_COMPONENT_MASK(Sprite, 1 << 3);
DEFINE_COMPONENT_MASK(ModelHandle, 1 << 4);
DEFINE_COMPONENT_MASK(CollisionBox, 1 << 5);
DEFINE_COMPONENT_MASK(Velocity, 1 << 6);
DEFINE_COMPONENT_MASK(CollisionResult, 1 << 7);
DEFINE_COMPONENT_MASK(GeometrySolid, 1 << 8);
DEFINE_COMPONENT_MASK(CollisionCircle2D, 1 << 9);
// ----------------------------------------------------------------

/**
* @brief コンポーネントデータの組みに応じた複合マスク取得用テンプレート
* @tparam Args コンポーネントデータの型リスト
*/
template<typename... Args> struct ComponentsCombinedMask {
    static constexpr ComponentBits mask() {
        ComponentBits mask;
        ((mask |= ComponentMask<Args>::bit), ...);
        return mask;
    }
};

} // namespace HaraProject::Framework

#endif // !_COMPONENT_MASK_H_
