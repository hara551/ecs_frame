/**
* @file   Transform.h
* @brief�@�����蔻��p�{�b�N�X
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _COLLISION_BASE_H_
#define _COLLISION_BASE_H_

#include <DirectXMath.h>

#include <cstdint>

#include "ComponentDataBase.h"

namespace HaraProject::Framework
{

class CollisionBase : public ComponentDataBase
{
public:
	/**
	* @brief �f�[�^��
	*/
	static constexpr const char* COLLISION_BOX_NAME = "CollisionBox";
	static constexpr const char* COLLISION_BOX_CENTER_NAME = "center";
	static constexpr const char* COLLISION_BOX_SIZE_NAME = "size";

	/**
	* @brief �f�t�H���g�R���X�g���N�^
	*/
	CollisionBase() = default;

	/**
	* @brief Json�f�[�^����l��ݒ肷��
	* @param[in] json json�I�u�W�F�N�g
	*/
	void SetDataFromJson(nlohmann::json jsonData)override{}

#ifdef _DEBUG
	/**
	* @brief ���݂̒l��Json�f�[�^�ɕϊ�����
	*/
	nlohmann::json WriteDataToJson()override{}
#endif // _DEBUG

public:
	

};

}// !namespace HaraProject::Framework

#endif // !_COLLISION_BASE_H_