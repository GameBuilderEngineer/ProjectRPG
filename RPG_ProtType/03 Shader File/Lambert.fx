//===================================================================================================================================
//�yLambert.fx�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/08/07
// [�X�V��]2019/09/03
//===================================================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�O���[�o��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float4x4 matrixProjection;		//�v���W�F�N�V�����i���ߎˉe�j�s��
float4x4 matrixView;			//�r���[�s��
float4x4 matrixWorld;			//���[���h�s��
float4x4 matrixWVP;				//���[���h�s��
float4 lightDirection;			//���s�����̕����x�N�g��
float4 ambient = 0.0f;			//����
float farZ;						//���ߎˉe�s��̍ŉ��ߋ���

sampler textureSmapler : register(s0);	//�e�N�X�`���T���v���[

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�o�[�e�b�N�X�E�V�F�[�_�[
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct VS_OUTPUT
{
	float4 position		: POSITION;
	float4 color		: COLOR0;
	float2 uv			: TEXCOORD0;
	float4 positionWVP	: TEXCOORD1;
};
VS_OUTPUT VS(
	float4	position	: POSITION,
	float4	normal		: NORMAL,
	float2	uv			: TEXCOORD0)
{
	VS_OUTPUT Out;
	
	Out.position = mul(position, matrixWVP);
	Out.uv = uv;

	float3 L = -lightDirection.xyz;
	float3 N = normalize(normal.xyz);
	Out.color = max(ambient, dot(N, L));

	Out.positionWVP = Out.position;

	return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�s�N�Z���E�V�F�[�_�[
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PS_OUTPUT
{
	float4 color1 : COLOR0;
	float4 color2 : COLOR1;
};
PS_OUTPUT PS(VS_OUTPUT In)
{
	PS_OUTPUT Out;
	
	//�F�����i�[����
	Out.color1 = tex2D(textureSmapler, In.uv);
	Out.color1.rgb = Out.color1.rgb * In.color.rgb;

	//Z�l�����i�[����
	Out.color2 = In.positionWVP.z / farZ;

	return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �e�N�j�b�N
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
technique main
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}