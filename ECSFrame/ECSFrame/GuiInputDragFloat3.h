/**
* @file   GuiInputDragFloat.h
* @brief  マウスドラッグFloat入力GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_DRAG_FLOAT3_H_
#define _GUI_INPUT_DRAG_FLOAT3_H_

#include <DirectXMath.h>

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputDragFloat3 : public GuiInputBase
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
	GuiInputDragFloat3(std::string label, std::string id,DirectX::XMFLOAT3* outputBuffer, float dragSpeed)
		: GuiInputBase(label, id, OverWriteMode::Always), m_output_buffer(outputBuffer), m_drag_speed(dragSpeed)
	{
		m_input_buffer[0] = outputBuffer->x;
		m_input_buffer[1] = outputBuffer->y;
		m_input_buffer[2] = outputBuffer->z;
	}

	/**
	* @brief 描画
	*/
	void Draw()override {
		if (m_is_show)
		{
			if (ImGui::DragFloat3(m_imgui_name.c_str(), m_input_buffer, m_drag_speed))
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
			m_input_buffer[2]
		};
	}
	/**
	* @brief 入力用バッファ
	*/
	float m_input_buffer[3];

	/**
	* @brief 出力用バッファ
	*/
	DirectX::XMFLOAT3* m_output_buffer;

	/**
	* @brief ドラッグで変わる値の速さ
	*/
	float m_drag_speed;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_DRAG_FLOAT3_H_

