/**
* @file   SubSceneManager.h
* @brief  サブシーン管理.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifdef _DEBUG
#ifndef _SUBSCENE_MANAGER_H_
#define _SUBSCENE_MANAGER_H_

#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "Transform.h"

namespace HaraProject::Framework {

class EditorManager;

class SubsceneManager
{
public:
	/**
	* @brief サブシーンに紐づく情報
	*/
	struct SubsceneData
	{
		/**
		* @brief トランスフォーム
		*/
		Transform transform;

		/**
		* @brief 所属しているエンティティID
		*/
		std::vector<uint32_t> entities;
	};

	/**
	* @brief コンストラクタ
	* @param[in] editorManager エディターマネージャー
	*/
	SubsceneManager(EditorManager* editorManager);

	/**
	* @brief デストラクタ
	*/
	~SubsceneManager() = default;

	/**
	* @brief 新しいサブシーンを追加
	* @param[in] subsceneName サブシーン名
	* @param[in] transform トランスフォーム
	* @param[in] entities 所属しているエンティティID
	*/
	void AddSubscene(std::string subsceneName, Transform transform = Transform(),
		std::vector<uint32_t> entities = std::vector<uint32_t>());

	/**
	* @brief サブシーンにエンティティを追加
	* @param[in] subsceneName サブシーン名
	* @param[in] entityId エンティティID
	*/
	void AddEntityToSubscene(std::string subsceneName, uint32_t entityId);

	/**
	* @brief サブシーンを削除
	* @param[in] subsceneName サブシーン名
	*/
	void DeleteSubscene(std::string subsceneName);

	/**
	* @brief サブシーン名を変更
	* @param[in] subsceneName 変更したいサブシーンの名前
	* @param[in] newName 新しい名前
	*/
	void RenameSubscene(std::string subsceneName, std::string newName);

	/**
	* @brief サブシーン全体の移動を更新
	*/
	void UpdateSubScenesTransform();

	/**
	* @brief サブシーンからエンティティを削除
	* @param[in] entityId エンティティID
	*/
	void RemoveEntityFromSubscene(uint32_t entityId);

	/**
	* @brief 保持しているサブシーンを全て廃棄
	*/
	void CleanUpSubscenes();

	/**
	* @brief サブシーンのトランスフォームを参照で取得
	* @param[in] subsceneName サブシーン名
	*/
	Transform& GetSubscenesTransform(std::string subsceneName);

	/**
	* @brief サブシーンごとのエンティティを取得
	*/
	std::unordered_map<std::string, std::vector<uint32_t>> GetEntitiesBySubscene();

	/**
	* @brief サブシーンデータを取得
	*/
	std::unordered_map<std::string, SubsceneData> GetSubsceneDatas() {
		return m_name_to_subsceneData;
	}

private:
	/**
	* @brief 被らないサブシーン名に変換
	* @param[in] subsceneName サブシーン名
	*/
	std::string ConvertToUniqueSubsceneName(std::string subsceneName);

	/**
	* @brief サブシーンデータ
	*/
	std::unordered_map<std::string, SubsceneData> m_name_to_subsceneData;

	/**
	* @brief サブシーンごとの前フレームのトランスフォーム
	*/
	std::unordered_map<std::string, Transform> m_name_to_old_transform;

	/**
	* @brief エディター全体管理
	*/
	EditorManager* m_editor_manager;
};

}// !namespace HaraProject::Framework

#endif // !_SUBSCENE_MANAGER_H_
#endif // _DEBUG