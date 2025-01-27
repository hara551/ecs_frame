///**
//* @file   SystemMask.h
//* @brief  システムへのビット割り当て.
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
//* @brief 登録システム最大登録数
//*/
//static constexpr uint8_t MAX_SYSTEM = 32;
//
///**
//* @brief システム識別ビット
//*/
//using SystemBits = std::bitset<MAX_SYSTEM>;
//
///**
//* @brief コンポーネントデータにビット割り当て用テンプレート
//* @tparam コンポーネントデータの型
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
