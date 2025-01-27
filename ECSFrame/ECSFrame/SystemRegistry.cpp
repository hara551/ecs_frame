//#include <memory>
//
//#include "SystemBase.h"
//#include "SystemMask.h"
//
//#include "SystemRegistry.h"
//
//namespace HaraProject::Framework {
//
//namespace SystemRegistry {
//
///**
//* @brief 名前とビットを登録する
//* @param[in] name システム名
//* @param[in] bit 識別ビット
//*/
//void RegisterName(std::string name, SystemBits bit)
//{
//	if (!nameToBit.contains(name))
//	{
//		nameToBit[name] = bit;
//	}
//}
//
///**
//* @brief システム名から識別ビットを取得する
//* @param[in] name システム名
//*/
//SystemBits GetBitByName(std::string name)
//{
//	if (nameToBit.contains(name))
//	{
//		return nameToBit[name];
//	}
//	return SystemBits();
//}
//
///**
//* @brief システムのユニークポインタ作成関数を登録
//* @param[in] bit 識別ビット
//* @param[in] uniqueConstructor 作成関数
//*/
//void RegisterUniqueConstructor(SystemBits bit, std::function<std::unique_ptr<SystemBase>()> uniqueConstructor)
//{
//	if (!bitToUniqueConstructor.contains(bit))
//	{
//		bitToUniqueConstructor[bit] = uniqueConstructor;
//	}
//}
//
///**
//* @brief システムのユニークポインタを作成
//* @param[in] bit 識別ビット
//*/
//std::unique_ptr<SystemBase> UniqueConstructor(SystemBits bit)
//{
//	if (bitToUniqueConstructor.contains(bit))
//	{
//		return bitToUniqueConstructor[bit]();
//	}
//	return nullptr;
//}
//
///**
//* @brief システムの動的確保コンストラクタを登録
//* @param[in] bit 識別ビット
//* @param[in] constructor コンストラクタ
//*/
//void RegisterConstructor(SystemBits bit, std::function<SystemBase* ()> constructor)
//{
//	if (!bitToConstructor.contains(bit))
//	{
//		bitToConstructor[bit] = constructor;
//	}
//}
//
///**
//* @brief システムの動的確保コンストラクタ
//* @param[in] bit 識別ビット
//*/
//SystemBase* Constructor(SystemBits bit)
//{
//	if (bitToConstructor.contains(bit))
//	{
//		return bitToConstructor[bit]();
//	}
//	return nullptr;
//}
//
//} // namespace ComponentRegistry
//
//} // namespace HaraProject::Framework