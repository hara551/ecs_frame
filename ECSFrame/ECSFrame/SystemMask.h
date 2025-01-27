///**
//* @file   SystemMask.h
//* @brief  �V�X�e���ւ̃r�b�g���蓖��.
//* @author Hara Sota.
//* @date   2024/10/14.
//*/
//#ifndef _SYSTEM_MASK_H_
//#define _SYSTEM_MASK_H_
//
//#include <bitset>
//#include <cstdint>
//
////#include "CameraSystemBase.h"
//
//namespace HaraProject::Framework {
//
///**
//* @brief �o�^�V�X�e���ő�o�^��
//*/
//static constexpr uint8_t MAX_SYSTEM = 32;
//
///**
//* @brief �V�X�e�����ʃr�b�g
//*/
//using SystemBits = std::bitset<MAX_SYSTEM>;
//
///**
//* @brief �R���|�[�l���g�f�[�^�Ƀr�b�g���蓖�ėp�e���v���[�g
//* @tparam �R���|�[�l���g�f�[�^�̌^
//*/
//template<typename T> struct SystemMask {
//    static constexpr SystemBits bit = SystemBits(0);
//};
//
//#define DEFINE_SYSTEM_MASK(SYSTEM, BIT) \
//template <>struct SystemMask<SYSTEM> { \
//    static constexpr SystemBits bit = SystemBits(BIT); \
//}; \
//
////DEFINE_SYSTEM_MASK(CameraSystemBase, 1 << 1);
//
//} // namespace HaraProject::Framework
//
//#endif // !_SYSTEM_MASK_H_
