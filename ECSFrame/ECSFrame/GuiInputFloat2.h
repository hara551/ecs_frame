/**
* @file   GuiInputFloat2.h
* @brief  Float2入力GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_FLOAT2_H_
#define _GUI_INPUT_FLOAT2_H_

#include <DirectXMath.h>

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"
#include "GuiInputFloat.h"

namespace HaraProject::Framework {

class GuiInputFloat2 : public GuiInputBase
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] title ノードラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	* @param[in] decimalPlaces 表示する少数桁数
	* @param[in] overWriteMode 書き換えタイミングオプション
	*/
	GuiInputFloat2(std::string label, std::string id, DirectX::XMFLOAT2* outputBuffer,
		int decimalPlaces = GuiInputFloat::DEFAULT_DECIMAL_PLACES, OverWriteMode overWriteMode = GuiInputBase::Always)
		: GuiInputBase(label, id, overWriteMode), m_output_buffer(outputBuffer)
	{
		std::string str = std::to_string(decimalPlaces);
		str = "%." + str + "f";
		m_decimal_places = str;

		m_input_buffer[0] = outputBuffer->x;
		m_input_buffer[1] = outputBuffer->y;
	}

	/**
	* @brief 描画
	*/
	void Draw()override {
		if (m_is_show)
		{
			if (ImGui::InputFloat2(m_imgui_name.c_str(), m_input_buffer, m_decimal_places.c_str(), m_over_write_flag))
			{
				ChangeValue();
			}
		}
	}

private:
	/**
	* @brief 出力用バッファに値を格納
	*/
	void ChangeValue() {
		*m_output_buffer = {
			m_input_buffer[0],
			m_input_buffer[1],
		};
	}

	/**
	* @brief 入力用バッファ
	*/
	float m_input_buffer[2];

	/**
	* @brief 出力用バッファ
	*/
	DirectX::XMFLOAT2* m_output_buffer;

	/**
	* @brief 表示する少数桁数
	*/
	std::string m_decimal_places;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_FLOAT3_H_

