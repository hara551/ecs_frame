#include <string>
#include <mutex>

#include "Model.h"
#include "FileUtil.h"
#include "Defines.h"

#include "ModelManager.h"

namespace HaraProject::Framework {

/**
* @brief モデル読込
* @param[in] fileName ファイル名
*/
bool ModelManager::LoadModel(std::string fileName, bool isFlip)
{
	// すでにロード済なら成功を返す
	if (m_name_to_model.contains(fileName))return true;

	// ファイルが存在しなければ失敗を返す
	if (!FileExists(FileType::ModelData, fileName.c_str()))
	{
		return false;
	}

	std::string path = CreatePath(FileType::ModelData, fileName.c_str());
	Model* model;
	{
		// ※シェーダーを同時に行うとアクセス違反が起きるため
		//   コンストラクタ実行のみロック
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
* @brief モデル取得
* @param[in] fileName ファイル名
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
* @brief モデル解放
* @param[in] fileName ファイル名
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
* @brief 全モデル解放
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
* @brief デストラクタ
*/
ModelManager::~ModelManager()
{
	ReleaseAllModel();
}

}// !namespace HaraProject::Framework