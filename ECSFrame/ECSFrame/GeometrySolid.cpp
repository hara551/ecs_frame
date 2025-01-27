#include "GeometrySolid.h"
namespace HaraProject::Framework {

/**
* @brief �R���X�g���N�^
*/
GeometrySolid::GeometrySolid()
	: geometryNum(0)
	, color(0,0,1,1)
{
}

/**
* @brief �R�s�[�R���X�g���N�^
* @param[in] base GeometrySolid�����������N���X�|�C���^
*/
GeometrySolid::GeometrySolid(ComponentDataBase* base)
{
	auto* value = dynamic_cast<GeometrySolid*>(base);
	geometryNum = value->geometryNum;
	color = value->color;
}

/**
* @brief Json�f�[�^����l��ݒ肷��
* @param[in] json json�I�u�W�F�N�g
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
