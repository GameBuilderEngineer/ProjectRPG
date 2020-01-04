//===================================================================================================================================
//�yColorFade.fx�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/11/01
// [�X�V��]2019/11/01
//===================================================================================================================================
///////////////////////////////////////////////////////////////////////////////////
//�^��`
///////////////////////////////////////////////////////////////////////////////////
struct VS_OUT
{
	float4 Pos : POSITION;
	float2 TC0 : TEXCOORD0;
	float2 TC1 : TEXCOORD1;
	float2 TC2 : TEXCOORD2;
	float2 TC3 : TEXCOORD3;
};
///////////////////////////////////////////////////////////////////////////////////
//�O���[�o��
///////////////////////////////////////////////////////////////////////////////////
float TexWidth = 1024;
float TexHeight = 1024;
float Level = 2;
texture BlurTex;

sampler BlurSampler = sampler_state
{
	Texture = (BlurTex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Clamp;
	AddressV = Clamp;
};



/////////////////////////////////////////////////////////////////////
//�o�[�e�b�N�X�E�V�F�[�_�[
///////////////////////////////////////////////////////////////////////////////////
VS_OUT VS(float4 Position : POSITION, float2 TC : TEXCOORD0)
{
	VS_OUT Out = (VS_OUT)0;
	Out.Pos = Position;
	float DeltaH = Level / TexWidth;
	float DeltaV = Level / TexHeight;
	Out.TC0 = TC + float2(-DeltaH, -DeltaV);
	Out.TC1 = TC + float2(DeltaH, -DeltaV);
	Out.TC2 = TC + float2(-DeltaH, DeltaV);
	Out.TC3 = TC + float2(DeltaH, DeltaV);

	return Out;
}

///////////////////////////////////////////////////////////////////////////////////
//�s�N�Z���E�V�F�[�_�[
///////////////////////////////////////////////////////////////////////////////////
float4 PS(VS_OUT In) : COLOR
{
	float4 Color0 = tex2D(BlurSampler,In.TC0);
	float4 Color1 = tex2D(BlurSampler,In.TC1);
	float4 Color2 = tex2D(BlurSampler,In.TC2);
	float4 Color3 = tex2D(BlurSampler,In.TC3);

	float4 FinalColor = (Color0 + Color1 + Color2 + Color3) / 4.0f;
	return FinalColor;
}

///////////////////////////////////////////////////////////////////////////////////
// �e�N�j�b�N
///////////////////////////////////////////////////////////////////////////////////
technique tecBlur
{
	pass p0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}