/**
* @file   ModelManager.h
* @brief  リソース管理クラス定義.
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
	* @brief インスタンス取得
	*/
	static ModelManager& Instance() {
		static ModelManager instance;
		return instance;
	}

	/**
	* @brief モデル読込
	* @param[in] fileName ファイル名
	* @param[in] isFlip 反転フラグ
	*/
	bool LoadModel(std::string fileName, bool isFlip = true);

	/**
	* @brief モデル取得
	* @param[in] fileName ファイル名
	*/
	Model* FindModel(std::string fileName);

	/**
	* @brief モデル解放
	* @param[in] fileName ファイル名
	*/
	void ReleaseModel(std::string fileName);

	/**
	* @brief 全モデル解放
	*/
	void ReleaseAllModel();

private:
	ModelManager() = default;
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;

	/**
	* @brief デストラクタ
	*/
	~ModelManager();

	/**
	* @brief ファイル名とモデルデータのマップ
	*/
	std::unordered_map<std::string, Model*> m_name_to_model;

	/**
	* @brief 非同期ロード用ロック
	*/
	std::mutex m_async_lock;
};

}// !namespace HaraProject::Framework

#endif // !_MODEL_MANAGER_H_

