/**
* @file   GuiInputText.h
* @brief  テキスト入力GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_TEXT_H_
#define _GUI_INPUT_TEXT_H_

#include <string.h>

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputText : public GuiInputBase
{
public:
	/**
	* @brief 最大入力文字数
	*/
	static constexpr uint8_t MAX_INPUT_TEXT_LENGTH = 50;

	/**
	* @brief コンストラクタ
	* @param[in] title ノードラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] overWriteMode 書き換えタイミングオプション
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	*/
	GuiInputText(std::string label, std::string id, OverWriteMode overWriteMode, char* outputBuffer)
		: GuiInputBase(label, id, overWriteMode), m_output_buffer(outputBuffer)
	{
		strcpy_s(m_input_buffer, MAX_INPUT_TEXT_LENGTH, m_output_buffer);
	}

	/**
	* @brief 描画
	*/
	void Draw()override{
		if (m_is_show)
		{
			if (ImGui::InputText(m_imgui_name.c_str(), m_input_buffer, MAX_INPUT_TEXT_LENGTH, m_over_write_flag))
			{
				ChangeValue(m_output_buffer);
			}
		}
	}

private:
	/**
	* @brief 引数のバッファに値を設定
	* @param[in] charBuffer 値を格納するバッファ
	*/
	void ChangeValue(char* charBuffer) {
		strcpy_s(charBuffer, MAX_INPUT_TEXT_LENGTH, m_input_buffer);
	}

	/**
	* @brief 入力用バッファ
	*/
	char m_input_buffer[MAX_INPUT_TEXT_LENGTH];

	/**
	* @brief 出力用バッファ
	*/
	char* m_output_buffer;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_TEXT_H_

