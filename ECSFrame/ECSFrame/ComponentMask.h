/**
* @file   ComponentMask.h
* @brief  �R���|�[�l���g�ւ̃r�b�g���蓖��.
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
* @brief �R���|�[�l���g�f�[�^�ő�o�^��
*/
static constexpr uint8_t MAX_COMPONENT_DATA = 32;

/**
* @brief �R���|�[�l���g���ʃr�b�g
*/
using ComponentBits = std::bitset<MAX_COMPONENT_DATA>;

/**
* @brief �R���|�[�l���g�f�[�^�Ƀr�b�g���蓖�ėp�e���v���[�g
* @tparam �R���|�[�l���g�f�[�^�̌^
*/
template<typename T> struct ComponentMask {
    static constexpr ComponentBits bit = ComponentBits(0);
};

/**
* @brief �r�b�g���蓖�Ă̓��ꉻ�}�N��
* @param[in] COMPONENT �R���|�[�l���g�f�[�^�^
* @param[in] BIT �r�b�g
*/
#define DEFINE_COMPONENT_MASK(COMPONENT, BIT) \
template<> struct ComponentMask<COMPONENT> { \
static constexpr ComponentBits bit = ComponentBits(BIT); \
}; \

// ----------------------------------------------------------------
// �R���|�[�l���g�f�[�^�ǉ���
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
* @brief �R���|�[�l���g�f�[�^�̑g�݂ɉ����������}�X�N�擾�p�e���v���[�g
* @tparam Args �R���|�[�l���g�f�[�^�̌^���X�g
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
