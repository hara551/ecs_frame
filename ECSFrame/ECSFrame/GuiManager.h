/**
* @file   GuiStructureManager.h
* @brief  GUI構造管理.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_STRUCTURE_MANAGER_H_
#define _GUI_STRUCTURE_MANAGER_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "GuiWindow.h"
#include "GuiPopup.h"
#include "GuiSelectable.h"
#include "GuiButton.h"
#include "GuiText.h"
#include "GuiTreeNode.h"
#include "GuiInputBase.h"
#include "GuiInputText.h"
#include "GuiCheckBox.h"
#include "GuiInputInt.h"
#include "GuiInputFloat.h"
#include "GuiInputFloat2.h"
#include "GuiInputFloat3.h"
#include "GuiInputColor.h"
#include "GuiInputDragFloat.h"
#include "GuiInputDragFloat3.h"
#include "FileUtil.h"

namespace HaraProject::Framework {

class GuiManager
{
public:
	/**
	* @brief コンストラクタ
	*/
	GuiManager();

	/**
	* @brief デストラクタ
	*/
	~GuiManager();

	/**
	* @brief GUI描画
	*/
	void DrawGUI();

	/**
	* @brief アイテム取得
	* @tparam GuiType 受け取りたい型
	* @param[in] path 階層
	*/
	template<typename GuiType> GuiType* GetGuiItem(const char* path);

	/**
	* @brief アイテム削除
	* @param[in] item GUIアイテム
	*/
	void DeleteGuiItem(GuiItemBase* item) {
		// ウィンドウかポップアップならコンテナからも削除
		auto sort = [item](auto& itr)
		{
			return itr.first == item->GetLabel();
		};
		std::erase_if(m_name_to_root_window, sort);
		std::erase_if(m_name_to_popup, sort);

		// 親から切り離して解放
		item->DetachParent();
		delete item;
	}

	/**
	* @brief ウィンドウを作成し登録
	* @param[in] title ウィンドウタイトル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] isShow 表示フラグ
	* @param[in] pos 表示位置
	* @param[in] size サイズ
	*/
	GuiWindow* RegisterGuiWindow(std::string title, std::string id, bool isShow, ImVec2 pos, ImVec2 size);

	/**
	* @brief ポップアップを作成し登録
	* @param[in] title ポップアップタイトル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] isShow 表示フラグ
	*/
	GuiPopup* RegisterGuiPopup(std::string title, std::string id, bool isShow = false);

	/**
	* @brief 選択項目アイテムを作成
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] onSelect 選択時に実行する関数
	*/
	GuiSelectable* CreateGuiSelectable(std::string label, std::string id, std::function<void()> onSelect) {
		return new GuiSelectable(label, id, onSelect);
	}

	/**
	* @brief ボタンを作成
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] onSelect 選択時に実行する関数
	*/
	GuiButton* CreateGuiButton(std::string label, std::string id, std::function<void()> onClick){
		return new GuiButton(label, id, onClick);
	}

	/**
	* @brief テキストを作成
	* @param[in] text テキスト
	* @param[in] id 内部ID重複防止用の任意の識別子
	*/
	GuiText* CreateGuiText(std::string text) {
		return new GuiText(text);
	}

	/**
	* @brief ツリーノードを作成
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] isDefaultOpen 初期ノード開閉フラグ
	* @param[in] onSelect 選択時に実行する関数
	*/
	GuiTreeNode* CreateGuiTreeNode(std::string label, std::string id, bool isDefaultOpen = true, 
		std::function<void()> onSelect = nullptr, std::function<void()> onClickRight = nullptr, bool isLeaf = false) {
		return new GuiTreeNode(label, id, isDefaultOpen, onSelect, onClickRight, isLeaf);
	}

	/**
	* @brief テキスト入力アイテム作成
	* @param[in] title ノードラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] overWriteMode 書き換えタイミングオプション
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	*/
	GuiInputText* CreateGuiInputText(std::string label, std::string id, GuiInputBase::OverWriteMode overWriteMode, char* outputBuffer) {
		return new GuiInputText(label, id, overWriteMode, outputBuffer);
	}

	/**
	* @brief チェックボックス作成
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	* @param[in] onChage チェック状態変更時に実行する関数
	*/
	GuiCheckBox* CreateGuiCheckBox(std::string label, std::string id, bool* outputBuffer, std::function<void()> onChange = nullptr) {
		return new GuiCheckBox(label, id, outputBuffer, onChange);
	}

	/**
	* @brief int入力アイテム作成
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	* @param[in] overWriteMode 書き換えタイミングオプション
	*/
	GuiInputInt* CreateGuiInputInt(std::string label, std::string id, int* outputBuffer, GuiInputBase::OverWriteMode overWriteMode = GuiInputBase::Always) {
		return new GuiInputInt(label, id, outputBuffer, overWriteMode);
	}

	/**
	* @brief float入力アイテム作成
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	* @param[in] decimalPlaces 表示する少数桁数
	* @param[in] overWriteMode 書き換えタイミングオプション
	*/
	GuiInputFloat* CreateGuiInputFloat(std::string label, std::string id, float* outputBuffer,
		int decimalPlaces = GuiInputFloat::DEFAULT_DECIMAL_PLACES, GuiInputBase::OverWriteMode overWriteMode = GuiInputBase::Always) {
		return new GuiInputFloat(label, id, outputBuffer, decimalPlaces, overWriteMode);
	}

	/**
	* @brief float2入力アイテム作成
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	* @param[in] decimalPlaces 表示する少数桁数
	* @param[in] overWriteMode 書き換えタイミングオプション
	*/
	GuiInputFloat2* CreateGuiInputFloat2(std::string label, std::string id, DirectX::XMFLOAT2* outputBuffer,
		int decimalPlaces = GuiInputFloat::DEFAULT_DECIMAL_PLACES, GuiInputBase::OverWriteMode overWriteMode = GuiInputBase::Always) {
		return new GuiInputFloat2(label, id, outputBuffer, decimalPlaces, overWriteMode);
	}

	/**
	* @brief float3入力アイテム作成
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	* @param[in] decimalPlaces 表示する少数桁数
	* @param[in] overWriteMode 書き換えタイミングオプション
	*/
	GuiInputFloat3* CreateGuiInputFloat3(std::string label, std::string id, DirectX::XMFLOAT3* outputBuffer,
		int decimalPlaces = GuiInputFloat::DEFAULT_DECIMAL_PLACES, GuiInputBase::OverWriteMode overWriteMode = GuiInputBase::Always){
		return new GuiInputFloat3(label, id, outputBuffer, decimalPlaces, overWriteMode);
	}

	/**
	* @brief Color入力アイテム作成
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	*/
	GuiInputColor* CreateGuiInputColor(std::string label, std::string id, DirectX::XMFLOAT4* outputBuffer) {
		return new GuiInputColor(label, id, outputBuffer);
	}

	/**
	* @brief ドラッグでのFloat入力アイテム作成
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	* @param[in] dragSpeed ドラッグで変わる値の大きさについてのパラメータ
	* @param[in] min 最小値
	* @param[in] min 最大値
	*/
	GuiInputDragFloat* CreateGuiInputDragFloat(std::string label, std::string id, float* outputBuffer, float dragSpeed,
		float min, float max) {
		return new GuiInputDragFloat(label, id, outputBuffer, dragSpeed, min, max);
	}

	/**
	* @brief ドラッグでのFloat3入力アイテム作成
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	* @param[in] dragSpeed ドラッグで変わる値の大きさについてのパラメータ
	*/
	GuiInputDragFloat3* CreateGuiInputDragFloat3(std::string label, std::string id, DirectX::XMFLOAT3* outputBuffer, float dragSpeed){
		return new GuiInputDragFloat3(label, id, outputBuffer, dragSpeed);
	}

private:
	/**
	* @brief GUI描画準備
	*/
	void BeginDrawImGui() {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	/**
	* @brief GUI描画終了
	*/
	void EndDrawImGui() {
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	/**
	* @brief ウィンドウ名とウィンドウのマップ
	*/
	std::unordered_map<std::string, GuiWindow*> m_name_to_root_window;

	/**
	* @brief ポップアップ名とポップアップメニューのマップ
	*/
	std::unordered_map<std::string, GuiPopup*> m_name_to_popup;
};

/**
* @brief アイテム取得
* @tparam GuiType 受け取りたい型
* @param[in] path 階層
*/
template<typename GuiType>
inline GuiType* GuiManager::GetGuiItem(const char* path)
{
	// パスを分割
	std::vector<std::string> parts = SplitPath(path);

	GuiItemBase* item{};

	if (m_name_to_root_window.contains(parts[0]))
	{
		// 上から下に名前で辿っていく
		item = m_name_to_root_window[parts[0]];
		for (int current = 1; current < parts.size(); ++current)
		{
			if (item != nullptr)
			{
				item = item->GetChild(parts[current]);
			}
		}
		return  dynamic_cast<GuiType*>(item);
	}

	if (m_name_to_popup.contains(parts[0]))
	{
		item = m_name_to_popup[parts[0]];
		for (int current = 1; current < parts.size(); ++current)
		{
			if (item != nullptr)
			{
				item = item->GetChild(parts[current]);
			}
		}
		return dynamic_cast<GuiType*>(item);
	}
	return nullptr;
}

}// !namespace HaraProject::Framework

#endif // !_GUI_STRUCTURE_MANAGER_H_
