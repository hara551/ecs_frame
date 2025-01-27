/**
* @file   MathUtil.h
* @brief  数学ユーティリティ関数群.
* @author Hara Sota.
* @date   2024/10/14.
*/
#ifndef _MATH_UTIL_H_
#define _MATH_UTIL_H_

#include <DirectXMath.h>

namespace HaraProject::Framework {
namespace MathUtil {

/**
* @brief 2つのベクトル (XMFLOAT3) を比較する関数
* @param[in] lhs      比較対象の1つ目のベクトル
* @param[in] rhs      比較対象の2つ目のベクトル
* @param[in] epsilon  許容する誤差の範囲
*/
bool Float3Equals(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs, float epsilon = 1e-6f);

/**
* @brief 2つのベクトル (XMFLOAT3) を加算する関数
* @param[in] lhs  加算対象の1つ目のベクトル
* @param[in] rhs  加算対象の2つ目のベクトル
*/
DirectX::XMFLOAT3 AddFloat3(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs);

/**
* @brief 2つのベクトル (XMFLOAT3) を減算する関数
* @param[in] lhs  減算対象の1つ目のベクトル
* @param[in] rhs  減算対象の2つ目のベクトル
*/
DirectX::XMFLOAT3 SubtractFloat3(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs);

/**
* @brief 2つのベクトルを乗算する関数
* @param[in] lht 乗算対象の１つ目のベクトル
* @param[in] lht 乗算対象の２つ目のベクトル
*/
DirectX::XMFLOAT3 MultiplyFloat3(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs);



/**
* @brief ベクトル (XMFLOAT3) をスケーリングする関数
* @param[in] vec 対象ベクトル
* @param[in] scale スケール
*/
DirectX::XMFLOAT3 ScalingFloat3(const DirectX::XMFLOAT3& vec, const float& scale);

} // namespace MathUtil
} // namespace HaraProject::Framework

#endif // !_MATH_UTIL_H_
