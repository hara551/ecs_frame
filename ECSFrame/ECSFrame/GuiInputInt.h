/**
* @file   GuiInputInt.h
* @brief  Int入力GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_INT_H_
#define _GUI_INPUT_INT_H_

#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputInt : public GuiInputBase
{
public:
	/**
	* @brief ＋ーボタンで増減する数
	*/
	static constexpr int DEFAULT_INT_STEP = 1;

	/**
	* @brief Ctr & ＋ーボタンで増減する数
	*/
	static constexpr int DEFAULT_FAST_INT_STEP = 100;

	/**
	* @brief コンストラクタ
	* @param[in] title ノードラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	* @param[in] overWriteMode 書き換えタイミングオプション
	*/
	GuiInputInt(std::string label, std::string id, int* outputBuffer, OverWriteMode overWriteMode = GuiInputBase::Always)
		: GuiInputBase(label, id, overWriteMode), m_output_buffer(outputBuffer){}

	/**
	* @brief 描画
	*/
	void Draw()override {
		if (m_is_show)
		{
			ImGui::InputInt(m_imgui_name.c_str(), m_output_buffer,
				DEFAULT_INT_STEP, DEFAULT_FAST_INT_STEP, m_over_write_flag);
		}
	}

private:
	/**
	* @brief 出力用バッファ
	*/
	int* m_output_buffer;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_INT_H_

