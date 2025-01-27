/**
* @file   GuiCheckBox.h
* @brief  チェックボックスGUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_CHECK_BOX_H_
#define _GUI_CHECK_BOX_H_

#include <string>
#include <functional>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiCheckBox : public GuiInputBase
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] title ノードラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	* @param[in] onChage チェック状態変更時に実行する関数
	*/
	GuiCheckBox(std::string label, std::string id, bool* outputBuffer, std::function<void()> onChange = nullptr)
		: GuiInputBase(label, id, GuiInputBase::Always), m_output_buffer(outputBuffer), m_on_change_check(onChange){}

	/**
	* @brief 描画
	*/
	void Draw()override {
		if (m_is_show)
		{
			if (ImGui::Checkbox(m_imgui_name.c_str(), m_output_buffer))
			{
				if (m_on_change_check != nullptr)
				{
					m_on_change_check();
				}
			}
		}
	}

private:
	/**
	* @brief 出力用バッファ
	*/
	bool* m_output_buffer;

	/**
	* @brief チェック状態変更時に実行する関数
	*/
	std::function<void()> m_on_change_check;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_CHECK_BOX_H_

