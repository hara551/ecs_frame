/**
* @file   ModelManager.h
* @brief  ���\�[�X�Ǘ��N���X��`.
* @author Hara Sota.
* @date   2024/10/17
*/
#ifndef _MODEL_MANAGER_H_
#define _MODEL_MANAGER_H_

#include <string>
#include <unordered_map>
#include <mutex>

#include "Model.h"

namespace HaraProject::Framework {

class ModelManager
{
public:
	/**
	* @brief �C���X�^���X�擾
	*/
	static ModelManager& Instance() {
		static ModelManager instance;
		return instance;
	}

	/**
	* @brief ���f���Ǎ�
	* @param[in] fileName �t�@�C����
	* @param[in] isFlip ���]�t���O
	*/
	bool LoadModel(std::string fileName, bool isFlip = true);

	/**
	* @brief ���f���擾
	* @param[in] fileName �t�@�C����
	*/
	Model* FindModel(std::string fileName);

	/**
	* @brief ���f�����
	* @param[in] fileName �t�@�C����
	*/
	void ReleaseModel(std::string fileName);

	/**
	* @brief �S���f�����
	*/
	void ReleaseAllModel();

private:
	ModelManager() = default;
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;

	/**
	* @brief �f�X�g���N�^
	*/
	~ModelManager();

	/**
	* @brief �t�@�C�����ƃ��f���f�[�^�̃}�b�v
	*/
	std::unordered_map<std::string, Model*> m_name_to_model;

	/**
	* @brief �񓯊����[�h�p���b�N
	*/
	std::mutex m_async_lock;
};

}// !namespace HaraProject::Framework

#endif // !_MODEL_MANAGER_H_

