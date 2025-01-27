/**
* @file   GuiInputColor.h
* @brief  Color入力GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_COLOR_H_
#define _GUI_INPUT_COLOR_H_

#include <DirectXMath.h>

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputColor : public GuiInputBase
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] label ラベル
	* @param[in] id 内部ID重複防止用の任意の識別子
	* @param[in] outputBuffer 値変更時に値を格納するバッファ
	*/
	GuiInputColor(std::string label, std::string id, DirectX::XMFLOAT4* outputBuffer)
		: GuiInputBase(label, id, Always), m_output_buffer(outputBuffer)
	{
		m_input_buffer[0] = outputBuffer->x;
		m_input_buffer[1] = outputBuffer->y;
		m_input_buffer[2] = outputBuffer->z;
		m_input_buffer[3] = outputBuffer->w;
	}

	/**
	* @brief 描画
	*/
	void Draw()override {
		if (m_is_show)
		{
			if(ImGui::ColorEdit4(m_label.c_str(), m_input_buffer))
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
			m_input_buffer[2],
			m_input_buffer[3]
		};
	}

	/**
	* @brief 入力用バッファ
	*/
	float m_input_buffer[4];

	/**
	* @brief 出力用バッファ
	*/
	DirectX::XMFLOAT4* m_output_buffer;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_COLOR_H_

