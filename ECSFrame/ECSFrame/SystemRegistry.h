///**
//* @file   SystemRegistry.h
//* @brief  システムごとの情報登録
//* @author Hara Sota.
//* @date   2024/10/14.
//*/
//#ifndef _SYSTEM_REGISTRY_H_
//#define _SYSTEM_REGISTRY_H_
//
//#include <bitset>
//#include <unordered_map>
//#include <string>
//#include <functional>
//#include <stdexcept>
//#include <memory>
//#include <vector>
//
//#include "SystemMask.h"
//#include "SystemBase.h"
//
//namespace HaraProject::Framework {
//
//namespace SystemRegistry {
//
///**
//* @brief 名前と識別ビットのマップ
//*/
//inline std::unordered_map<std::string, SystemBits> nameToBit;
//
///**
//* @brief 識別ビットとユニークコンストラクタのマップ
//*/
//inline std::unordered_map<SystemBits, std::function<std::unique_ptr<SystemBase>()>> bitToUniqueConstructor;
//
///**
//* @brief 識別ビットとコンストラクタのマップ
//*/
//inline std::unordered_map<SystemBits, std::function<SystemBase*()>> bitToConstructor;
//
///**
//* @brief 名前とビットを登録する
//* @param[in] name システム名
//* @param[in] bit 識別ビット
//*/
//void RegisterName(std::string name, SystemBits bit);
//
///**
//* @brief システム名から識別ビットを取得する
//* @param[in] name システム名
//*/
//SystemBits GetBitByName(std::string name);
//
///**
//* @brief システムのユニークポインタ作成関数を登録
//* @param[in] bit 識別ビット
//* @param[in] uniqueConstructor 作成関数
//*/
//void RegisterUniqueConstructor(SystemBits bit, std::function<std::unique_ptr<SystemBase>()> uniqueConstructor);
//
///**
//* @brief システムのユニークポインタを作成
//* @param[in] bit 識別ビット
//*/
//std::unique_ptr<SystemBase> UniqueConstructor(SystemBits bit);
//
///**
//* @brief システムの動的確保コンストラクタを登録
//* @param[in] bit 識別ビット
//* @param[in] constructor コンストラクタ
//*/
//void RegisterConstructor(SystemBits bit, std::function<SystemBase*()> constructor);
//
///**
//* @brief システムの動的確保コンストラクタ
//* @param[in] bit 識別ビット
//*/
//SystemBase* Constructor(SystemBits bit);
//
//} // namespace ComponentRegistry
//
//} // namespace HaraProject::Framework
//
//#endif // !_SYSTEM_REGISTRY_H_
