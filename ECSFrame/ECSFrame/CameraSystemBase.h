/**
* @file   CameraSystemBase.h
* @brief  カメラシステム基底クラス定義.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _CAMERA_SYSTEM_BASE_H_
#define _CAMERA_SYSTEM_BASE_H_

#include <DirectXMath.h>

#include "SystemBase.h"
#include "Transform.h"
#include "IEntityOperator.h"
#include "IChunkProvider.h"

namespace HaraProject::Framework {
class ISystemDistributor;
class CameraSystemBase : public SystemBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	CameraSystemBase(IEntityOperator* entityOperator, ISystemDistributor* systemDistributor, IChunkProvider* chunkProvider);
	
	/**
	* @brief デストラクタ
	*/
	~CameraSystemBase();

	/**
	* @brief ビュー変換行列取得
	*/
	DirectX::XMFLOAT4X4 GetViewMatrix(bool isTranspose = true);

	/**
	* @brief プロジェクション変換行列取得
	*/
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool isTranspose = true);

	/**
	* @brief 3D用か
	*/
	bool Is3D();

	/**
	* @brief 視野角取得
	*/
	float GetFovy();

	/**
	* @brief 横幅取得
	*/
	float GetWidth();

	/**
	* @brief 最前面取得
	*/
	float GetNear();

	/**
	* @brief 最奥面取得
	*/
	float GetFar();

	/**
	* @brief 
	*/
	float GetAspect();

	/**
	* @brief 
	*/
	float GetFocus();

	/**
	* @brief 注視点取得
	*/
	DirectX::XMFLOAT3 GetLook();

	/**
	* @brief 前方ベクトル取得
	*/
	DirectX::XMFLOAT3 GetFront();

	/**
	* @brief 右方向ベクトル取得
	*/
	DirectX::XMFLOAT3 GetRight();

	/**
	* @brief 上方向ベクトル取得
	*/
	DirectX::XMFLOAT3 GetUp();

	/**
	* @brief 位置取得
	*/
	DirectX::XMFLOAT3 GetPosition();

	/**
	* @brief 位置設定
	* @param[in] position 座標
	*/
	void SetPosition(DirectX::XMFLOAT3 position);

	/**
	* @brief プロジェクション設定
	* @param[in] is3D 透視投影か
	*/
	void SetIs3D(bool is3D);

protected:
	bool m_is_3d;
	float m_fovy;
	float m_width;
	float m_aspect, m_near, m_far;
	float m_focus;

	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT4 m_quaternion;
};
}// namespace HaraProject::Framework

#endif // !_CAMERA_SYSTEM_BASE_H_