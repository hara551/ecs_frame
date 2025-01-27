/**
* @file   GuiInputDragFloat.h
* @brief  マウスドラッグFloat入力GUI.
* @author Hara Sota.
* @date   2024/11/15
*/
#ifndef _GUI_INPUT_DRAG_FLOAT_H_
#define _GUI_INPUT_DRAG_FLOAT_H_

#include <cstdint>
#include <string>

#include "imgui.h"

#include "GuiInputBase.h"

namespace HaraProject::Framework {

class GuiInputDragFloat : public GuiInputBase
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
	GuiInputDragFloat(std::string label, std::string id, float* outputBuffer, float dragSpeed , float min, float max)
		: GuiInputBase(label, id, OverWriteMode::Always), m_output_buffer(outputBuffer), m_drag_speed(dragSpeed)
		, m_min(min), m_max(max)
	{
	}

	/**
	* @brief 描画
	*/
	void Draw()override {
		if (m_is_show)
		{
			ImGui::DragFloat(m_imgui_name.c_str(), m_output_buffer, m_drag_speed, m_min, m_max);
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

	/**
	* @brief ドラッグで変わる値の速さ
	*/
	float m_drag_speed;

	/**
	* @brief 最小値
	*/
	float m_min;

	/**
	* @brief 最大値
	*/
	float m_max;
};

}// !namespace HaraProject::Framework

#endif // !_GUI_INPUT_DRAG_FLOAT_H_

