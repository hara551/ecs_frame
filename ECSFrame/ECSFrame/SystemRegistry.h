///**
//* @file   SystemRegistry.h
//* @brief  �V�X�e�����Ƃ̏��o�^
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
//* @brief ���O�Ǝ��ʃr�b�g�̃}�b�v
//*/
//inline std::unordered_map<std::string, SystemBits> nameToBit;
//
///**
//* @brief ���ʃr�b�g�ƃ��j�[�N�R���X�g���N�^�̃}�b�v
//*/
//inline std::unordered_map<SystemBits, std::function<std::unique_ptr<SystemBase>()>> bitToUniqueConstructor;
//
///**
//* @brief ���ʃr�b�g�ƃR���X�g���N�^�̃}�b�v
//*/
//inline std::unordered_map<SystemBits, std::function<SystemBase*()>> bitToConstructor;
//
///**
//* @brief ���O�ƃr�b�g��o�^����
//* @param[in] name �V�X�e����
//* @param[in] bit ���ʃr�b�g
//*/
//void RegisterName(std::string name, SystemBits bit);
//
///**
//* @brief �V�X�e�������环�ʃr�b�g���擾����
//* @param[in] name �V�X�e����
//*/
//SystemBits GetBitByName(std::string name);
//
///**
//* @brief �V�X�e���̃��j�[�N�|�C���^�쐬�֐���o�^
//* @param[in] bit ���ʃr�b�g
//* @param[in] uniqueConstructor �쐬�֐�
//*/
//void RegisterUniqueConstructor(SystemBits bit, std::function<std::unique_ptr<SystemBase>()> uniqueConstructor);
//
///**
//* @brief �V�X�e���̃��j�[�N�|�C���^���쐬
//* @param[in] bit ���ʃr�b�g
//*/
//std::unique_ptr<SystemBase> UniqueConstructor(SystemBits bit);
//
///**
//* @brief �V�X�e���̓��I�m�ۃR���X�g���N�^��o�^
//* @param[in] bit ���ʃr�b�g
//* @param[in] constructor �R���X�g���N�^
//*/
//void RegisterConstructor(SystemBits bit, std::function<SystemBase*()> constructor);
//
///**
//* @brief �V�X�e���̓��I�m�ۃR���X�g���N�^
//* @param[in] bit ���ʃr�b�g
//*/
//SystemBase* Constructor(SystemBits bit);
//
//} // namespace ComponentRegistry
//
//} // namespace HaraProject::Framework
//
//#endif // !_SYSTEM_REGISTRY_H_
