/**
* @file   ComponentRegistry.h
* @brief  �R���|�[�l���g���Ƃ̏��o�^
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COMPONENT_REGISTRY_H_
#define _COMPONENT_REGISTRY_H_

#include <bitset>
#include <unordered_map>
#include <string>
#include <functional>
#include <stdexcept>
#include <memory>
#include <vector>

#include "ComponentMask.h"
#include "ComponentDataBase.h"

namespace HaraProject::Framework {

namespace ComponentRegistry {

/**
* @brief ���O�Ǝ��ʃr�b�g�̃}�b�v
*/
inline std::unordered_map<std::string, ComponentBits> nameToBit;

/**
* @brief ���ʃr�b�g�Ɣz��쐬�֐��̃}�b�v
*/
inline std::unordered_map<ComponentBits, std::function<void(void*, size_t)>> bitToPlacementNewArray;

/**
* @brief ���ʃr�b�g�ƃC���X�^���X�R�s�[�֐��̃}�b�v
*/
inline std::unordered_map<ComponentBits, std::function<void(void*, ComponentDataBase*)>> bitToAllocateInstance;

/**
* @brief ���ʃr�b�g�ƃR���|�[�l���g�T�C�Y�̃}�b�v
*/
inline std::unordered_map<ComponentBits, size_t> bitToSize;

/**
* @brief ���ʃr�b�g�Ɠ��I�m�ۃR���X�g���N�^�̃}�b�v
*/
inline std::unordered_map<ComponentBits, std::function<ComponentDataBase* ()>> bitToConstructor;

/**
* @brief ���ʃr�b�g�ƃR�s�[�R���X�g���N�^�̃}�b�v
*/
inline std::unordered_map<ComponentBits, std::function<ComponentDataBase* (ComponentDataBase*)>> bitToCopyConstructor;

/**
* @brief ���O�ƃr�b�g��o�^����
* @param[in] name �R���|�[�l���g��
* @param[in] bit ���ʃr�b�g
*/
void RegisterName(std::string name, ComponentBits bit);

/**
* @brief �R���|�[�l���g�����环�ʃr�b�g���擾����
* @param[in] name �R���|�[�l���g��
*/
ComponentBits GetBitByName(std::string name);

/**
* @brief �����̃R���|�[�l���g�����畡���r�b�g���擾����
* @param[in] names �R���|�[�l���g���̃��X�g
*/
ComponentBits GetConbinedMaskByNames(std::vector<std::string> names);

/**
* @brief �z��쐬�֐���o�^����
* @param[in] bit ���ʃr�b�g
* @param[in] placementNewArray �z��쐬�֐�
*/
void RegisterPlacementNewArray(ComponentBits bit, std::function<void(void*, size_t)> placementNewArray);

/**
* @brief �z��쐬�֐����g�p���Ĕz��𐶐�����
* @param[in] bit ���ʃr�b�g
* @param[in] buffer �z����i�[����o�b�t�@
* @param[in] size �z��̃T�C�Y
*/
void PlacementNewArray(ComponentBits bit, void* buffer, size_t size);

/**
* @brief �C���X�^���X�R�s�[�֐���o�^����
* @param[in] bit ���ʃr�b�g
* @param[in] allocateInstance �R�s�[�֐�
*/
void RegisterAllocateInstance(ComponentBits bit, std::function<void(void*, ComponentDataBase*)> allocateInstance);

/**
* @brief �R�s�[�֐����g�p���ăC���X�^���X�𐶐�����
* @param[in] bit ���ʃr�b�g
* @param[in] buffer �C���X�^���X���i�[����o�b�t�@
* @param[in] component �R�s�[���̃R���|�[�l���g
*/
void AllocateInstance(ComponentBits bit, void* buffer, ComponentDataBase* component);

/**
* @brief �R���|�[�l���g�̃T�C�Y��o�^
* @param[in] bit ���ʃr�b�g
* @param[in] size �R���|�[�l���g�T�C�Y
*/
void RegisterSize(ComponentBits bit, size_t size);

/**
* @brief �R���|�[�l���g�̃T�C�Y���擾
* @param[in] bit ���ʃr�b�g
*/
size_t GetSize(ComponentBits bit);

/**
* @brief �R���X�g���N�^�o�^
* @param[in] bit ���ʃr�b�g
* @param[in] constructor �R���X�g���N�^
*/
void RegisterConstructor(ComponentBits bit, std::function<ComponentDataBase*()> constructor);

/**
* @brief �R���X�g���N�^���s
* @param[in] bit ���ʃr�b�g
*/
ComponentDataBase* Constructor(ComponentBits bit);

/**
* @brief �R�s�[�R���X�g���N�^�o�^
* @param[in] bit ���ʃr�b�g
* @param[in] copyConstructor �R�s�[�R���X�g���N�^
*/
void RegisterCopyConstructor(ComponentBits bit, std::function<ComponentDataBase* (ComponentDataBase*)> copyConstructor);

/**
* @brief �R�s�[�R���X�g���N�^���s
* @param[in] bit ���ʃr�b�g
* @param[in] original �R�s�[���f�[�^
*/
ComponentDataBase* CopyConstructor(ComponentBits bit, ComponentDataBase* original);

/**
* @brief �S�R���|�[�l���g�f�[�^�e��o�^����
*/
void RegisterAllComponentData();

/**
* @brief �R���|�[�l���g�f�[�^�e��o�^����
* @param[in] name �R���|�[�l���g�f�[�^��
*/
template<typename T >void RegisterComponentData(std::string name)
{
	ComponentBits bit = ComponentMask<T>::bit;

	RegisterName(name, bit);
	RegisterSize(bit, sizeof(T));
	RegisterPlacementNewArray(bit,
		[](void* buffer, size_t size)
		{
			new (buffer) T[size];
		});
	RegisterAllocateInstance(bit,
		[](void* buffer, ComponentDataBase* component)
		{
			T* cast_buffer = reinterpret_cast<T*>(buffer);
			* cast_buffer = T(component);
		});
	RegisterConstructor(bit,
		[]()
		{
			return new T();
		});
	RegisterCopyConstructor(bit,
		[](ComponentDataBase* original)
		{
			return new T(original);
		});
}

} // namespace ComponentRegistry

} // namespace HaraProject::Framework

#endif // !_COMPONENT_REGISTRY_H_
