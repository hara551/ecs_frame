#include "EasingUtil.h"	
#include <DirectXMath.h>

namespace HaraProject::Framework {

const float PI = DirectX::XM_PI;

/**
* @brief
*/
float Ease(EaseType type, EaseDir dir, float param)
{
	float result{};
	switch (type)
	{
	case EaseType::Linear:
		if (dir == EaseDir::In)return param;
		if (dir == EaseDir::Out)return param;
		if (dir == EaseDir::InOut)return param;
		break;
	case EaseType::Sine:
		if (dir == EaseDir::In)result = EaseInSine(param);
		else if (dir == EaseDir::Out)result = EaseOutSine(param);
		else if (dir == EaseDir::InOut)result = EaseInOutSine(param);
		break;
	case EaseType::Quad:
		if (dir == EaseDir::In)result = EaseInQuad(param);
		else if (dir == EaseDir::Out)result = EaseOutQuad(param);
		else if (dir == EaseDir::InOut)result = EaseInOutQuad(param);
		break;
	case EaseType::Cubic:
		if (dir == EaseDir::In)result = EaseInCubic(param);
		else if (dir == EaseDir::Out)result = EaseOutCubic(param);
		else if (dir == EaseDir::InOut)result = EaseInOutCubic(param);
		break;
	case EaseType::Quart:
		if (dir == EaseDir::In)result = EaseInQuart(param);
		else if (dir == EaseDir::Out)result = EaseOutQuart(param);
		else if (dir == EaseDir::InOut)result = EaseInOutQuart(param);
		break;
	case EaseType::Quint:
		if (dir == EaseDir::In)result = EaseInQuint(param);
		else if (dir == EaseDir::Out)result = EaseOutQuint(param);
		else if (dir == EaseDir::InOut)result = EaseInOutQuint(param);
		break;
	case EaseType::Expo:
		if (dir == EaseDir::In)result = EaseInExpo(param);
		else if (dir == EaseDir::Out)result = EaseOutExpo(param);
		else if (dir == EaseDir::InOut)result = EaseInOutExpo(param);
		break;
	case EaseType::Circ:
		if (dir == EaseDir::In)result = EaseInCirc(param);
		else if (dir == EaseDir::Out)result = EaseOutCirc(param);
		else if (dir == EaseDir::InOut)result = EaseInOutCirc(param);
		break;
	case EaseType::Back:
		if (dir == EaseDir::In)result = EaseInBack(param);
		else if (dir == EaseDir::Out)result = EaseOutBack(param);
		else if (dir == EaseDir::InOut)result = EaseInOutBack(param);
		break;
	case EaseType::Elastic:
		if (dir == EaseDir::In)result = EaseInElastic(param);
		else if (dir == EaseDir::Out)result = EaseOutElastic(param);
		else if (dir == EaseDir::InOut)result = EaseInOutElastic(param);
		break;
	case EaseType::Bounce:
		if (dir == EaseDir::In)result = EaseInBounce(param);
		else if (dir == EaseDir::Out)result = EaseOutBounce(param);
		else if (dir == EaseDir::InOut)result = EaseInOutBounce(param);
		break;
	}
	return result;
}

float EaseInSine(float param)
{
	return 1 - cos(param * PI / 2.0f);
}

float EaseOutSine(float param)
{
	return sin(param * PI / 2.0f);
}

float EaseInOutSine(float param)
{
	return -1.0f * (cos(PI * param) - 1.0f) / 2.0f;
}

float EaseInQuad(float param)
{
	return pow(param, 2.0f);
}

float EaseOutQuad(float param)
{
	return 1.0f - pow(1.0f - param, 2.0f);
}

float EaseInOutQuad(float param)
{
	return param < 0.5f ?
		2.0f * pow(param, 2.0f) :
		1.0f - pow(-2.0f * param * 2.0f, 2.0f) / 2.0f;
}

float EaseInCubic(float param)
{
	return pow(param, 3.0f);
}

float EaseOutCubic(float param)
{
	return 1.0f - pow(1.0f - param, 2.0f);
}

float EaseInOutCubic(float param)
{
	return param < 0.5f ?
		4.0f * pow(param, 3.0f) :
		1.0f - pow(-2.0f * param + 2.0f, 3.0f) / 2.0f;
}

float EaseInQuart(float param)
{
	return pow(param, 4.0f);
}

float EaseOutQuart(float param)
{
	return 1.0f - pow(1.0f - param, 4.0f);
}

float EaseInOutQuart(float param)
{
	return param < 0.5f ?
		8.0f * pow(param, 4.0f) :
		1.0f - pow(-2.0f * param + 2.0f, 4.0f) / 2.0f;
}

float EaseInQuint(float param)
{
	return pow(param, 5.0f);
}

float EaseOutQuint(float param)
{
	return 1.0f - pow(1.0f - param, 5.0f);
}

float EaseInOutQuint(float param)
{
	return param < 0.5f ?
		16.0f * pow(param, 5.0f) :
		1.0f - pow(-2.0f * param + 2.0f, 5.0f) / 2.0f;
}

float EaseInExpo(float param)
{
	return param == 0.0f ? 0.0f :
		pow(2.0f, 10.0f * param - 10.0f);
}

float EaseOutExpo(float param)
{
	return param == 1.0f ? 1.0f :
		1.0f - pow(2.0f, -10.0f * param);
}

float EaseInOutExpo(float param)
{
	return param == 0.0f ? 0.0f : param == 1.0f ? 1.0f : param < 0.5f ?
		pow(2.0f, 20.0f * param - 10.0f) / 2.0f :
		(2.0f - pow(2.0f, 20.0f * param + 10.0f)) / 2.0f;
}

float EaseInCirc(float param)
{
	return 1.0f - sqrt(1.0f - pow(param, 2.0f));
}

float EaseOutCirc(float param)
{
	return sqrt(1.0f - pow(param - 1.0f, 2.0f));
}

float EaseInOutCirc(float param)
{
	return param < 0.5f ?
		(1.0f - sqrt(1.0f - pow(2.0f * param, 2.0f))) / 2.0f :
		(sqrt(1.0f - pow(-2.0f * param + 2.0f, 2.0f)) + 1.0f) / 2.0f;
}

float EaseInBack(float param)
{
	float c1 = 1.70158f;
	float c3 = c1 + 1.0f;
	return c3 * pow(param, 3.0f) - c1 * pow(param, 2.0f);
}

float EaseOutBack(float param)
{
	float c1 = 1.70158f;
	float c3 = c1 + 1.0f;
	return 1.0f + c3 * pow(param - 1.0f, 3.0f) + c1 * pow(param - 1.0f, 2.0f);
}

float EaseInOutBack(float param)
{
	float c1 = 1.70158f;
	float c2 = c1 * 1.525f;
	return param < 0.5f ?
		(pow(2.0f * param, 2.0f) *((c2 + 1.0f) * 2.0f * param - c2)) / 2.0f :
		(pow(2.0f * param - 2.0f, 2.0f) *
		((c2 + 1.0f) * (param * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;
}

float EaseInElastic(float param)
{
	float c4 = (2.0f * PI) / 3.0f;
	return param == 0.0f ? 0.0f :param == 1.0f ? 1.0f :
		-pow(2.0f, 10.0f * param - 10.0f) *
		sin((param * 10.0f - 10.75f) * c4);
//‚Ü‚½‚Ísin(param * 10.0f - 10.75f) * c4;	
}

float EaseOutElastic(float param)
{
	float c4 = (2.0f * PI) / 3.0f;
	return param == 0.0f ? 0.0f : param == 1 ? 1 :
		pow(2.0f, -10.0f * param) *
		sin((param * 10.0f - 0.75f) * c4) + 1;
}

float EaseInOutElastic(float param)
{
	float c5 = (2.0f * PI) / 4.5f;
	return param == 0.0f ? 0.0f : param == 1.0f ? 1.0f : param < 0.5f ?
		-(pow(2.0f, 20.0f * param - 10.0f) *
		sin((20.0f * param - 11.125f) * c5)) / 2.0f :
		(pow(2.0f, -20.0f * param + 10.0f) *
		sin((20.0f * param - 11.125f) * c5)) / 2.0f + 1.0f;
}

float EaseInBounce(float param)
{
	return 1.0f - EaseOutBounce(1.0f - param);
}

float EaseOutBounce(float param)
{
	float n1 = 7.5625f;
	float d1 = 2.75f;
	return param < 1.0f / d1 ? n1 * param * param :
		param < 2.0f / d1 ?
		n1 * pow(param - 1.5f / d1, 2.0f) + 0.75f :
		param < 2.5f / d1 ?
		n1 * pow(param - 2.25f / d1, 2.0f) + 0.9375f :
		n1 * pow(param - 2.625 / d1, 2) + 0.984375;
}

float EaseInOutBounce(float param)
{
	return param < 0.5f ?
		(1.0f - EaseOutBounce(1.0f - 2.0f * param)) / 2.0f :
		(1.0f + EaseOutBounce(2.0f * param - 1.0f)) / 2.0f;
}

}// namespace HaraProject::Framework