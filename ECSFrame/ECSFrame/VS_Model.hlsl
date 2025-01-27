struct VS_IN {	//CPUから渡される頂点データ
	float3 pos : POSITION;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

struct VS_OUT {	//頂点シェーダからピクセルシェーダに渡すデータ
	float4 pos : SV_POSITION;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

cbuffer WVP : register(b0) {	//CPUから渡される定数バッファ
	float4x4 world;	//ワールド変換行列
	float4x4 view;	//ビュー変換行列
	float4x4 proj;	//プロジェクション変換行列
};

VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);	//ローカル座標からワールド座標への変換
	vout.pos = mul(vout.pos, view);		//ワールド座標からビュー座標への変換
	vout.pos = mul(vout.pos, proj);		//ビュー座標からプロジェクション座標への変換

	//その他の値渡し
	vout.normal = mul(vin.normal, (float3x3)world);
	vout.uv = vin.uv;
	vout.color = vin.color;
	return vout;
}

