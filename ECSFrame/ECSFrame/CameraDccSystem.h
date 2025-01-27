/**
* @file  CameraDccSystem.h
* @brief  DCC���J�����i�ҏW�p�J�����j
* @author Hara Sota.
* @date    2024/10/30.
*/
#ifndef _CAMERA_DCC_SYSTEM_H_
#define _CAMERA_DCC_SYSTEM_H_

#include <windows.h>
#include <DirectXMath.h>

#include "SystemBase.h"
#include "CameraSystemBase.h"
#include "Transform.h"
#include "IEntityOperator.h"
#include "IChunkProvider.h"

class SystemManager;

namespace HaraProject::Framework {

class CameraDccSystem : public CameraSystemBase
{
public:
	/**
	* @brief �o�^�p�V�X�e����
	*/
	static inline const char* CAMERA_DCC_SYSTEM = "CameraDccSystem";

	/**
	* @brief
	*/
	struct Argument
	{
		DirectX::XMFLOAT2 mouseMove;
		DirectX::XMVECTOR vCamFront;
		DirectX::XMVECTOR vCamSide;
		DirectX::XMVECTOR vCamUp;
		DirectX::XMVECTOR vCamPos;
		DirectX::XMVECTOR vCamLook;
	};
public:
	/**
	* @brief �R���X�g���N�^
	*/
	CameraDccSystem(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);

	/**
	* @brief �V�X�e���X�V
	*/
	void UpdateSystem(float deltaTime)override;

private:
	void UpdateState();
	void UpdateOrbit(Argument& arg);
	void UpdateTrack(Argument& arg);
	void UpdateDolly(Argument& arg);
	void UpdateFlight(Argument& arg);

private:
	int _state;
	POINT _oldPosition;
};
}// namespace HaraProject::Framework


#endif // !_CAMERA_DCC_SYSTEM_H_
