/**
* @file   MathUtil.h
* @brief  ���w���[�e�B���e�B�֐��Q.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _MATH_UTIL_H_
#define _MATH_UTIL_H_

#include <DirectXMath.h>

namespace HaraProject::Framework {
namespace MathUtil {

/**
* @brief 2�̃x�N�g�� (XMFLOAT3) ���r����֐�
* @param[in] lhs      ��r�Ώۂ�1�ڂ̃x�N�g��
* @param[in] rhs      ��r�Ώۂ�2�ڂ̃x�N�g��
* @param[in] epsilon  ���e����덷�͈̔�
*/
bool Float3Equals(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs, float epsilon = 1e-6f);

/**
* @brief 2�̃x�N�g�� (XMFLOAT3) �����Z����֐�
* @param[in] lhs  ���Z�Ώۂ�1�ڂ̃x�N�g��
* @param[in] rhs  ���Z�Ώۂ�2�ڂ̃x�N�g��
*/
DirectX::XMFLOAT3 AddFloat3(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs);

/**
* @brief 2�̃x�N�g�� (XMFLOAT3) �����Z����֐�
* @param[in] lhs  ���Z�Ώۂ�1�ڂ̃x�N�g��
* @param[in] rhs  ���Z�Ώۂ�2�ڂ̃x�N�g��
*/
DirectX::XMFLOAT3 SubtractFloat3(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs);

/**
* @brief 2�̃x�N�g������Z����֐�
* @param[in] lht ��Z�Ώۂ̂P�ڂ̃x�N�g��
* @param[in] lht ��Z�Ώۂ̂Q�ڂ̃x�N�g��
*/
DirectX::XMFLOAT3 MultiplyFloat3(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs);



/**
* @brief �x�N�g�� (XMFLOAT3) ���X�P�[�����O����֐�
* @param[in] vec �Ώۃx�N�g��
* @param[in] scale �X�P�[��
*/
DirectX::XMFLOAT3 ScalingFloat3(const DirectX::XMFLOAT3& vec, const float& scale);

} // namespace MathUtil
} // namespace HaraProject::Framework

#endif // !_MATH_UTIL_H_
