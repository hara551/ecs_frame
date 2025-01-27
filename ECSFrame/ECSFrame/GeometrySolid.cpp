#include "GeometrySolid.h"
namespace HaraProject::Framework {

/**
* @brief コンストラクタ
*/
GeometrySolid::GeometrySolid()
	: geometryNum(0)
	, color(0,0,1,1)
{
}

/**
* @brief コピーコンストラクタ
* @param[in] base GeometrySolidが入った基底クラスポインタ
*/
GeometrySolid::GeometrySolid(ComponentDataBase* base)
{
	auto* value = dynamic_cast<GeometrySolid*>(base);
	geometryNum = value->geometryNum;
	color = value->color;
}

/**
* @brief Jsonデータから値を設定する
* @param[in] json jsonオブジェクト
*/
void GeometrySolid::SetDataFromJson(nlohmann::json jsonData)
{
	geometryNum = jsonData[GEOMETRY_SOLID_GEOMETRY_NUM];
	color = DirectX::XMFLOAT4(
		jsonData[GEOMETRY_SOLID_COLOR_NAME][0],
		jsonData[GEOMETRY_SOLID_COLOR_NAME][1],
		jsonData[GEOMETRY_SOLID_COLOR_NAME][2],
		jsonData[GEOMETRY_SOLID_COLOR_NAME][3]
	);
}


}//HaraProject::Framework
