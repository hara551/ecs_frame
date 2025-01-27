/**
* @file   EditorManager.h
* @brief  エディター全体管理.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifdef _DEBUG
#ifndef _EDITOR_MANAGER_H_
#define _EDITOR_MANAGER_H_

#include <memory>
#include <vector>
#include <string>

#include "GuiManager.h"
#include "EntityManager.h"
#include "ComponentDataManager.h"
#include "SystemManager.h"
#include "WindowBase.h"

#include "EditDataManager.h"
#include "SubsceneManager.h"

#include "Transform.h"

namespace HaraProject::Framework {

class EditorManager
{
public:
	/**
	* @brief 編集モード
	*/
	enum EditMode
	{
		Edit,	// ワールドを編集
		Play	// ワールドを実行
	};

	/**
	* @brief コンストラクタ
	*/
	EditorManager();

	/**
	* @brief デストラクタ
	*/
	~EditorManager();

	/**
	* @brief 初期化処理
	*/
	void InitEditor();

	/**
	* @brief 終了処理
	*/
	void UninitEditor();

	/**
	* @brief エディター更新
	*/
	void UpdateEditor(float deltaTime);

	/**
	* @brief ECS要素をリセット
	*/
	void ResetECS();

	/**
	* @brief エディターで使用するシステムを登録
	*/
	void RegisterEditorSystems();

	/**
	* @brief エディター描画
	*/
	void DrawEditor();

	/**
	* @brief 編集モードを変更
	* @param[in] editMode 編集モード
	*/
	void ChangeEditMode(EditMode editMode);

	/**
	* @brief ワールドをロード
	*/
	void LoadWorld();

	/**
	* @brief エンティティに足りないリソースをロード
	*/
	void ReloadResource();

	/**
	* @brief サブシーンをロード
	* @param[in] subsceneName サブシーン名
	*/
	void LoadSubscene(std::string name);

	/**
	* @brief サブシーンを作成
	* @param[in] subsceneName サブシーン名
	*/
	void CreateSubsceen(std::string subsceneName);

	/**
	* @brief 選択中のサブシーンを削除
	*/
	void DeleteSelectSubScene();

	/**
	* @brief ワールドをセーブ
	*/
	void SaveWorld();

	/**
	* @brief サブシーンをセーブ
	* @param[in] subSceneName サブシーン名
	*/
	void SaveSubscene(std::string subSceneName);

	/**
	* @brief 空のエンティティを作成
	*/
	void CreateEmptyEntity();

	/**
	* @brief ワールド名変更
	* @param[in] newName 新ワールド名
	*/
	void RenameWorld(std::string newName);

	/**
	* @brief 選択中のサブシーン名を変更
	* @param[in] newName 新サブシーン名
	*/
	void RenameSubScene(std::string newName);

	/**
	* @brief サブシーンの移動をエンティティに反映する
	*/
	void UpdateSubSceneTransforms();

	/**
	* @brief 選択中のサブシーン内のエンティティを全てコピーする
	*/
	void CopySubsceneEntities();

	/**
	* @brief コピー中のサブシーンのエンティティを選択中のサブシーン内に作成する
	*/
	void PasteSubsceneEntities();

	/**
	* @brief 選択中のエンティティのデータをコピーして保持する
	*/
	void CopySelectEntity();

	/**
	* @brief コピー中のデータでエンティティを作成
	*/
	void PasteEntity();

	/**
	* @brief 選択中のエンティティを削除
	*/
	void DeleteSelectEntity();

	/**
	* @brief GUIマネージャー取得
	*/
	std::shared_ptr<GuiManager> GetGuiManager();

	/**
	* @brief 選択中サブシーン設定
	* @param[in] name サブシーン名
	*/
	void SetSelectSubScene(std::string name);

	/**
	* @brief 選択中サブシーン名取得
	*/
	std::string GetSelectSubScene();

	/**
	* @brief 選択中エンティティ設定
	*/
	void SetSelectEntityId(uint32_t id);

	/**
	* @brief 選択中エンティティID取得
	*/
	uint32_t GetSelectEntityId();

	/**
	* @brief ウィンドウ取得
	* @param[in] windowName ウィンドウ名
	*/
	WindowBase* GetWindow(std::string windowName);

	/**
	* @brief エンティティマネージャー取得
	*/
	EntityManager* GetEntityManager();

	/**
	* @brief コンポーネントデータマネージャー取得
	*/
	ComponentDataManager* GetComponentDataManager();

	/**
	* @brief システムマネージャー取得
	*/
	SystemManager* GetSystemManager();

	/**
	* @brief 編集中のワールド名を取得
	*/
	std::string GetEditWorldName();

	/**
	* @brief 編集モード取得
	*/
	EditMode GetEditMode() {
		return m_edit_mode;
	}

	/**
	* @brief 編集モード設定
	* @param[in] editMode 編集モード
	*/
	void SetEditMode(EditMode editMode) {
		m_edit_mode = editMode;
	}

	/**
	* @brief EditDataManagerを取得
	*/
	EditDataManager* GetEditDataManager() {
		return m_edit_data_manager;
	}

	/**
	* @brief SubsceneManagerを取得
	*/
	SubsceneManager* GetSubsceneManager() {
		return m_subscene_manager;
	}

private:
	/**
	* @brief ウィンドウ登録
	* @param[in] windowName ウィンドウ名
	*/
	template <typename T>
	void RegisterWindow(std::string windowName) 
	{
		m_name_to_window[windowName] = new T(this); 
	}

	/**
	* @brief GUI管理
	*/
	std::shared_ptr<GuiManager> m_gui_manager;

	/**
	* @brief コンポーネントデータ管理
	*/
	ComponentDataManager* m_component_data_manager;

	/**
	* @brief エンティティ管理
	*/
	EntityManager* m_entity_manager;

	/**
	* @brief システム管理
	*/
	SystemManager* m_system_manager;

	/**
	* @brief ウィンドウ一覧
	*/
	std::unordered_map<std::string, WindowBase*> m_name_to_window;

	/**
	* @brief 編集中のワールド名
	*/
	std::string m_edit_world_name;

	/**
	* @brief 選択中サブシーン名
	*/
	std::string m_select_subscene_name;

	/**
	* @brief 選択中エンティティ
	*/
	uint32_t m_select_entity_id;

	/**
	* @brief 編集モード
	*/
	EditMode m_edit_mode;

	/**
	* @brief コピーしたエンティティデータ
	*/
	std::unordered_map<ComponentBits, ComponentDataBase*> m_copy_entity_data;

	/**
	* @brief コピーしたサブシーンのエンティティデータ
	*/
	std::vector<std::unordered_map<ComponentBits, ComponentDataBase*>> m_copy_subscene_data;

	/**
	* @brief Guiを表示するか
	*/
	bool m_is_draw_gui;


	/**
	* @brief 編集データ管理
	*/
	EditDataManager* m_edit_data_manager;

	/**
	* @brief サブシーン管理
	*/
	SubsceneManager* m_subscene_manager;
};

}// !namespace HaraProject::Framework

#endif // !_EDITOR_MANAGER_H_
#endif // _DEBUG