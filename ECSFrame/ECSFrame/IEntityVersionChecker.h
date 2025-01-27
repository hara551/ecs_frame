/**
* @file   IEntityVersionChecker.h
* @brief  �G���e�B�e�B�L������C���^�[�t�F�[�X.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _IENTITY_VERSION_CHECKER_H_
#define _IENTITY_VERSION_CHECKER_H_

#include <cstdint>

class IEntityVersionChecker
{
public:
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~IEntityVersionChecker() = default;

	/**
	* @brief �L���ȃG���e�B�e�B��
	* @param[in] id �G���e�B�e�BID
	* @param[in] version �o�[�W����
	*/
	virtual bool IsValidEntity(uint32_t id, uint32_t version) = 0;
};

#endif // !_IENTITY_VERSION_CHECKER_H_
