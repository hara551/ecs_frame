#include <cmath>

#include "MathUtil.h"

namespace HaraProject::Framework {
namespace MathUtil {

/**
* @brief 2つのベクトル (XMFLOAT3) を比較する関数
* @param[in] lhs      比較対象の1つ目のベクトル
* @param[in] rhs      比較対象の2つ目のベクトル
* @param[in] epsilon  許容する誤差の範囲 (デフォルト値は 1e-6)
*/
bool Float3Equals(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs, float epsilon)
{
    return std::abs(lhs.x - rhs.x) < epsilon &&
        std::abs(lhs.y - rhs.y) < epsilon &&
        std::abs(lhs.z - rhs.z) < epsilon;
}

/**
* @brief 2つのベクトル (XMFLOAT3) を加算する関数
* @param[in] lhs  加算対象の1つ目のベクトル
* @param[in] rhs  加算対象の2つ目のベクトル
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
* @brief 2つのベクトル (XMFLOAT3) を減算する関数
* @param[in] lhs  減算対象の1つ目のベクトル
* @param[in] rhs  減算対象の2つ目のベクトル
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
* @brief 2つのベクトルを乗算する関数
* @param[in] lht 乗算対象の１つ目のベクトル
* @param[in] lht 乗算対象の２つ目のベクトル
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
* @brief ベクトル (XMFLOAT3) をスケーリングする関数
* @param[in] vec 対象ベクトル
* @param[in] scale スケール
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