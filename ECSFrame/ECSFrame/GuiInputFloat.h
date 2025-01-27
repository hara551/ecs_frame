/**
* @file   GuiInputFloat.h
* @brief  Float入力GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_FLOAT_H_
#define _GUI_INPUT_FLOAT_H_

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputFloat : public GuiInputBase
{
public:
	/**
	* @brief 既定の表示する少数桁数
	*/
	static constexpr uint8_t DEFAULT_DECIMAL_PLACES = 2;

	/**
	* @brief ＋ーボタンで増減する数
	*/
	static constexpr float DEFAULT_FLOAT_STEP = 0.1f;

	/**
	* @brief Ctr & ＋ーボタンで増減する数
	*/
	static constexpr float DEFAULT_FAST_FLOAT_STEP = 10.0f;

	/**
	* @brief コンストラクタ
	* @param[in] title ノードラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	* @param[in] decimalPlaces 表示する少数桁数
	* @param[in] overWriteMode 書き換えタイミングオプション
	*/
	GuiInputFloat(std::string label, std::string id, float* outputBuffer,
				  int decimalPlaces = DEFAULT_DECIMAL_PLACES, OverWriteMode overWriteMode = GuiInputBase::Always)
		: GuiInputBase(label, id, overWriteMode), m_output_buffer(outputBuffer)
	{
		std::string str = std::to_string(decimalPlaces);
		str = "%." + str + "f";
		m_decimal_places = str;
	}

	/**
	* @brief 描画
	*/
	void Draw()override {
		if (m_is_show)
		{
			ImGui::InputFloat(m_imgui_name.c_str(), m_output_buffer, DEFAULT_FLOAT_STEP,
				DEFAULT_FAST_FLOAT_STEP,m_decimal_places.c_str(), m_over_write_flag);
		}
	}

private:
	/**
	* @brief 出力用バッファ
	*/
	float* m_output_buffer;

	/**
	* @brief 表示する少数桁数
	*/
	std::string m_decimal_places;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_FLOAT_H_

