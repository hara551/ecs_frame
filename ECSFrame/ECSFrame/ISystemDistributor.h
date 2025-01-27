/**
* @file   ISystemDistrbutor.h
* @brief  �V�X�e���擾����C���^�t�F�[�X��`.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _ISYSTEM_DISTRIBUTOR_H_
#define _ISYSTEM_DISTRIBUTOR_H_

#include <string>

namespace HaraProject::Framework {
class SystemBase;
class ISystemDistributor
{
public:
	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~ISystemDistributor() = default;

	/**
	* @brief �V�X�e���擾
	* @param[in] bit �V�X�e����
	*/
	virtual SystemBase* FindSystem(std::string name) = 0;
};

} // namespace HaraProject::Framework

#endif // !_ISYSTEM_DISTRIBUTOR_H_
