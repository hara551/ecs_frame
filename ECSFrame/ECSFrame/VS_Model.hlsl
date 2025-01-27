struct VS_IN {	//CPU����n����钸�_�f�[�^
	float3 pos : POSITION;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

struct VS_OUT {	//���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
	float4 pos : SV_POSITION;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

cbuffer WVP : register(b0) {	//CPU����n�����萔�o�b�t�@
	float4x4 world;	//���[���h�ϊ��s��
	float4x4 view;	//�r���[�ϊ��s��
	float4x4 proj;	//�v���W�F�N�V�����ϊ��s��
};

VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);	//���[�J�����W���烏�[���h���W�ւ̕ϊ�
	vout.pos = mul(vout.pos, view);		//���[���h���W����r���[���W�ւ̕ϊ�
	vout.pos = mul(vout.pos, proj);		//�r���[���W����v���W�F�N�V�������W�ւ̕ϊ�

	//���̑��̒l�n��
	vout.normal = mul(vin.normal, (float3x3)world);
	vout.uv = vin.uv;
	vout.color = vin.color;
	return vout;
}

