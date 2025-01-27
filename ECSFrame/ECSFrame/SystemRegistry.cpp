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
//* @brief ���O�ƃr�b�g��o�^����
//* @param[in] name �V�X�e����
//* @param[in] bit ���ʃr�b�g
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
//* @brief �V�X�e�������环�ʃr�b�g���擾����
//* @param[in] name �V�X�e����
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
//* @brief �V�X�e���̃��j�[�N�|�C���^�쐬�֐���o�^
//* @param[in] bit ���ʃr�b�g
//* @param[in] uniqueConstructor �쐬�֐�
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
//* @brief �V�X�e���̃��j�[�N�|�C���^���쐬
//* @param[in] bit ���ʃr�b�g
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
//* @brief �V�X�e���̓��I�m�ۃR���X�g���N�^��o�^
//* @param[in] bit ���ʃr�b�g
//* @param[in] constructor �R���X�g���N�^
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
//* @brief �V�X�e���̓��I�m�ۃR���X�g���N�^
//* @param[in] bit ���ʃr�b�g
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