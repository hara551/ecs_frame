///**
//* @file   SystemDifinitions.h
//* @brief  コンポーネントを登録
//* @author Hara Sota.
//* @date   2024/10/14.
//*/
//#ifndef _SYSTEM_DEFINITIONS_H_
//#define _SYSTEM_DEFINITIONS_H_
//#include <memory>
//
//#include "SystemMask.h"
//#include "SystemRegistry.h"
//#include "SystemBase.h"
//
//namespace HaraProject::Framework {
///**
//* @brief システムの登録マクロ
//*/
//#define REGISTER_SYSTEM(SYSTEM, BIT, NAME) \
//template<> struct SystemMask<SYSTEM> { \
//    static constexpr SystemBits bit = SystemBits(BIT); \
//}; \
//namespace { \
//    struct SYSTEM##_Registrar { \
//        SYSTEM##_Registrar() { \
//            SystemRegistry::RegisterName(NAME, SystemMask<SYSTEM>::bit); \
//            SystemRegistry::RegisterUniqueConstructor(SystemMask<SYSTEM>::bit, \
//                []()-> std::unique_ptr<SystemBase> \
//                { \
//                   return std::make_unique<SYSTEM>();\
//                }); \
//            SystemRegistry::RegisterSharedConstructor(SystemMask<SYSTEM>::bit, \
//                []()-> std::shared_ptr<SystemBase> \
//                { \
//                   return std::make_shared<SYSTEM>();\
//                }); \
//        } \
//    }; \
//    static SYSTEM##_Registrar SYSTEM##_registrar_instance; \
//}
//
//// -----------------------------------------------------------------------------
//
//REGISTER_SYSTEM(SystemBase, 1 << 0, "Transform::TRANSFORM_NAME");
////REGISTER_COMPONENT(EntityName, 1 << 1, EntityName::ENTITY_NAME_NAME);
//
//// -----------------------------------------------------------------------------
//
//} // namespace HaraProject::Framework
//
//#endif // !_SYSTEM_DEFINITIONS_H_
