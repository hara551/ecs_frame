/**
* @file   SystemBase.h
* @brief  �V�X�e�����N���X��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _SYSTEM_BASE_H_
#define _SYSTEM_BASE_H_

#include <vector>

#include "nlohmann/json.hpp"

#include "IEntityOperator.h"
#include "ISystemDistributor.h"
#include "IChunkProvider.h"
#include "ComponentMask.h"
#include "ComponentDataChunk.h"

#ifdef _DEBUG
#include "GuiItemBase.h"
#endif // _DEBUG

namespace HaraProject::Framework {

class ISystemDistributor;

class SystemBase
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param[in] entityManager �G���e�B�e�B�}�l�[�W���[
	* @param[in] systemDistributor �V�X�e���}�l�[�W���[
	* @param[in] chunkProvider �R���|�[�l���g�f�[�^�}�l�[�W���[
	*/
	SystemBase(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider)
	: m_entity_operator(entityOperator), m_system_distributor(systemDistributor), m_chunk_provider(chunkProvider)
	{
		InitSystem(); 
	}

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~SystemBase() { UninitSystem(); }

	/**
	* @brief �V�X�e���X�V
	*/
	virtual void UpdateSystem(float deltaTime) = 0;

	/**
	* @brief �w��̃R���|�[�l���g�f�[�^�S�Ă��܂ރ`�����N��S�Ď擾
	* @tparam �R���|�[�l���g�f�[�^�^
	*/
	template<typename ... T>
	std::vector<ComponentDataChunk*> FindChunks(){
		ComponentBits mask;
		((mask = mask | ComponentMask<T>::bit), ...);
		return m_chunk_provider->FindChunks(mask);
	}

protected:
	/**
	* @brief ����������
	*/
	virtual void InitSystem() {};

	/**
	* @brief �I������
	*/
	virtual void UninitSystem() {};

	/**
	* @brief �G���e�B�e�B����p
	*/
	IEntityOperator* m_entity_operator;

	/**
	* @brief �V�X�e���擾�p
	*/
	ISystemDistributor* m_system_distributor;

	/**
	* @brief �`�����N�擾�p
	*/
	IChunkProvider* m_chunk_provider;
};

} // namespace HaraProject::Framework

#endif // !_SYSTEM_BASE_H_
