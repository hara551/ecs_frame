/**
* @file EasingUtil.h
* @brief イージング関数まとめ
* @author HaraSota
* @date //
*/
#ifndef __EASING_UTIL_H__
#define __EASING_UTIL_H__

namespace HaraProject::Framework {

/**
* @brief イージングの種類
*/
enum class EaseType
{
    Linear,
    Sine,
    Quad,
    Cubic,
    Quart,
    Quint,
    Expo,
    Circ,
    Back,
    Elastic,
    Bounce
};

/**
* @brief イージングの向き
*/
enum class EaseDir
{
    In,
    Out,
    InOut
};

/**
* @brief イージング
*/
float Ease(EaseType type, EaseDir dir, float param);

/**
* @brief Sine
*/
float EaseInSine(float param);
float EaseOutSine(float param);
float EaseInOutSine(float param);
/**
* @brief Quad
*/
float EaseInQuad(float param);
float EaseOutQuad(float param);
float EaseInOutQuad(float param);
/**
* @brief Qubic
*/
float EaseInCubic(float param);
float EaseOutCubic(float param);
float EaseInOutCubic(float param);
/**
* @brief Quart
*/
float EaseInQuart(float param);
float EaseOutQuart(float param);
float EaseInOutQuart(float param);
/**
* @brief Quint
*/
float EaseInQuint(float param);
float EaseOutQuint(float param);
float EaseInOutQuint(float param);
/**
* @brief Expo
*/
float EaseInExpo(float param);
float EaseOutExpo(float param);
float EaseInOutExpo(float param);
/**
* @brief Circ
*/
float EaseInCirc(float param);
float EaseOutCirc(float param);
float EaseInOutCirc(float param);
/**
* @brief Back
*/
float EaseInBack(float param);
float EaseOutBack(float param);
float EaseInOutBack(float param);
/**
* @brief Elastic
*/
float EaseInElastic(float param);
float EaseOutElastic(float param);
float EaseInOutElastic(float param);
/**
* @brief Bounce
*/
float EaseInBounce(float param);
float EaseOutBounce(float param);
float EaseInOutBounce(float param);

}// namespace HaraProject::Framework

#endif // !__EASING_UTIL_H__
