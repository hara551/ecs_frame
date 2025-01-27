#include <cmath>

#include "MathUtil.h"

namespace HaraProject::Framework {
namespace MathUtil {

/**
* @brief 2�̃x�N�g�� (XMFLOAT3) ���r����֐�
* @param[in] lhs      ��r�Ώۂ�1�ڂ̃x�N�g��
* @param[in] rhs      ��r�Ώۂ�2�ڂ̃x�N�g��
* @param[in] epsilon  ���e����덷�͈̔� (�f�t�H���g�l�� 1e-6)
*/
bool Float3Equals(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs, float epsilon)
{
    return std::abs(lhs.x - rhs.x) < epsilon &&
        std::abs(lhs.y - rhs.y) < epsilon &&
        std::abs(lhs.z - rhs.z) < epsilon;
}

/**
* @brief 2�̃x�N�g�� (XMFLOAT3) �����Z����֐�
* @param[in] lhs  ���Z�Ώۂ�1�ڂ̃x�N�g��
* @param[in] rhs  ���Z�Ώۂ�2�ڂ̃x�N�g��
*/
DirectX::XMFLOAT3 AddFloat3(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
    return DirectX::XMFLOAT3{
        lhs.x + rhs.x,
            lhs.y + rhs.y,
            lhs.z + rhs.z
    };
}

/**
* @brief 2�̃x�N�g�� (XMFLOAT3) �����Z����֐�
* @param[in] lhs  ���Z�Ώۂ�1�ڂ̃x�N�g��
* @param[in] rhs  ���Z�Ώۂ�2�ڂ̃x�N�g��
*/
DirectX::XMFLOAT3 SubtractFloat3(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
    return DirectX::XMFLOAT3{
        lhs.x - rhs.x,
            lhs.y - rhs.y,
            lhs.z - rhs.z
    };
}

/**
* @brief 2�̃x�N�g������Z����֐�
* @param[in] lht ��Z�Ώۂ̂P�ڂ̃x�N�g��
* @param[in] lht ��Z�Ώۂ̂Q�ڂ̃x�N�g��
*/
DirectX::XMFLOAT3 MultiplyFloat3(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
    return DirectX::XMFLOAT3{
        lhs.x * rhs.x,
        lhs.y * rhs.y,
        lhs.z * rhs.z
    };
}

/**
* @brief �x�N�g�� (XMFLOAT3) ���X�P�[�����O����֐�
* @param[in] vec �Ώۃx�N�g��
* @param[in] scale �X�P�[��
*/
DirectX::XMFLOAT3 ScalingFloat3(const DirectX::XMFLOAT3& vec, const float& scale)
{
    return DirectX::XMFLOAT3{
        vec.x* scale,
            vec.y* scale,
            vec.z* scale
    };
}

}// !namespace MathUtil
} //!namespace HaraProject::Framework::MathUtil