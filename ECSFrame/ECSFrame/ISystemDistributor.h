/**
* @file   ISystemDistrbutor.h
* @brief  システム取得操作インタフェース定義.
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
	* @brief デストラクタ
	*/
	virtual ~ISystemDistributor() = default;

	/**
	* @brief システム取得
	* @param[in] bit システム名
	*/
	virtual SystemBase* FindSystem(std::string name) = 0;
};

} // namespace HaraProject::Framework

#endif // !_ISYSTEM_DISTRIBUTOR_H_
