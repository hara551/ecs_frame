#include <string>
#include <mutex>

#include "Model.h"
#include "FileUtil.h"
#include "Defines.h"

#include "ModelManager.h"

namespace HaraProject::Framework {

/**
* @brief ���f���Ǎ�
* @param[in] fileName �t�@�C����
*/
bool ModelManager::LoadModel(std::string fileName, bool isFlip)
{
	// ���łɃ��[�h�ςȂ琬����Ԃ�
	if (m_name_to_model.contains(fileName))return true;

	// �t�@�C�������݂��Ȃ���Ύ��s��Ԃ�
	if (!FileExists(FileType::ModelData, fileName.c_str()))
	{
		return false;
	}

	std::string path = CreatePath(FileType::ModelData, fileName.c_str());
	Model* model;
	{
		// ���V�F�[�_�[�𓯎��ɍs���ƃA�N�Z�X�ᔽ���N���邽��
		//   �R���X�g���N�^���s�̂݃��b�N
		std::lock_guard lock(m_async_lock);
		model = new Model();
	}

	if (model->Load(path.c_str(), 1.0f, isFlip))
	{
		m_name_to_model[fileName] = model;
		return true;
	}

	SAFE_DELETE(model);
	return false;
}

/**
* @brief ���f���擾
* @param[in] fileName �t�@�C����
*/
Model* ModelManager::FindModel(std::string fileName)
{
	if (m_name_to_model.contains(fileName))
	{
		return m_name_to_model[fileName];
	}
	return nullptr;
}

/**
* @brief ���f�����
* @param[in] fileName �t�@�C����
*/
void ModelManager::ReleaseModel(std::string fileName)
{
	if (!m_name_to_model.contains(fileName)) return;

	SAFE_DELETE(m_name_to_model[fileName]);

	std::erase_if(m_name_to_model, 
		[&](const auto& itr)
		{
			return itr.first == fileName;
		});
}

/**
* @brief �S���f�����
*/
void ModelManager::ReleaseAllModel()
{
	for (auto& itr : m_name_to_model)
	{
		SAFE_DELETE(itr.second);
	}
	m_name_to_model.clear();
}

/**
* @brief �f�X�g���N�^
*/
ModelManager::~ModelManager()
{
	ReleaseAllModel();
}

}// !namespace HaraProject::Framework