/**
* @file  PS_AlphaFade.hlsl
* @brief  フェード用ピクセルシェーダー
* @author Hara Sota.
* @date    2024/11/04.
*/

struct PS_IN
{
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
};

/**
* @brief 透明度
*/
cbuffer Parameter
{
    float alphaParam;
    float3 dummy;
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = tex.Sample(samp, pin.uv);
    
    color.a = alphaParam;
    
    return color;
}