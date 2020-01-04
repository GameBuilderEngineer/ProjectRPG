//===================================================================================================================================
//�yInstancingStaticMesh.fx�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/09/23
// [�X�V��]2019/10/23
//===================================================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�O���[�o��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float4x4	matrixProjection;
float4x4	matrixView;
texture		textureDecal;
float4		diffuse;
float		alphaValue;
float4		lightDirection		= float4(-1.0f, 1.0f, -1.0f, 0.2f);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��`
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
sampler textureSampler = sampler_state
{
	texture			= <textureDecal>;
	//MinFilter		= ANISOTROPIC;
	//MagFilter		= POINT;
	//MipFilter		= LINEAR;
	//MaxAnisotropy	= 4;
	//AddressU		= Wrap;
	//AddressV		= Wrap;
};

struct VS_OUT
{
	float4 position	: POSITION;
	float2 uv		: TEXCOORD0;
	float4 diffuse	: COLOR0;
	float4 color	: COLOR1;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�o�[�e�b�N�X�E�V�F�[�_�[
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VS_OUT VS(
	float4 position		: POSITION,
	float2 localUV		: TEXCOORD0,
	float3 normal		: NORMAL,
	float4 matrix1		: TEXCOORD1,
	float4 matrix2		: TEXCOORD2,
	float4 matrix3		: TEXCOORD3,
	float4 matrix4		: TEXCOORD4,
	float4 color		: TEXCOORD5)
{
	VS_OUT Out;
	
	//���_��ۑ�
	Out.position = float4(
		position.x,
		position.y,
		position.z,
		1.0f);


	//���[���h�s���p�ӂ���B
	float4x4 worldMatrix = float4x4(
		matrix1,
		matrix2,
		matrix3,
		matrix4);

	//���ƂŎ����\��
	//���݂�CPU���ŉ��Z
	//�v�Z��S��GPU���ōs�������������H�H
	//�ړ��s��̓K�p
	//��]�s��̓K�p
	//�X�P�[���s��̓K�p

	//�r���[�s��
	worldMatrix = mul(worldMatrix, matrixView);
	//�v���W�F�N�V�����s��
	worldMatrix = mul(worldMatrix, matrixProjection);
	//���[���h�s��
	Out.position = mul(Out.position, worldMatrix);
	
	//UV���W
	Out.uv = localUV;

	//�A���r�G���g�J���[
	float ambient = lightDirection.w;

	//�����o�[�g���Z�J���[
	float4 lambert = max(ambient,saturate(dot(normal, lightDirection)));
	Out.diffuse = lambert*diffuse;
	Out.color = color;

	return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�s�N�Z���E�V�F�[�_�[
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float4 PS(VS_OUT In) : COLOR0
{
	float4 texel		= tex2D(textureSampler, In.uv);
	float4 finalColor	= texel*In.diffuse;
	return finalColor;
}
//���C�g���l�����Ȃ�
float4 PS1(VS_OUT In) : COLOR0
{
	float4 texel		= tex2D(textureSampler, In.uv);
	float4 finalColor	= texel * In.color;
	return finalColor;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �e�N�j�b�N
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
technique mainTechnique {
	//���C�g��ON �����o�[�g�g�U���˂ɂ��o��
	pass p0 {
		//�X�e�[�g�ݒ�
		Zenable					= TRUE;			//Z�o�b�t�@�L��
		ZWriteEnable			= TRUE;			//Z�o�b�t�@�ւ̏������ݗL��
		ShadeMode				= GOURAUD;		//�O�[���[�E�V�F�[�f�B���O
		CullMode				= CCW;			//�w�ʂ��J�����O
		MultiSampleAntialias	= TRUE;			//�A���`�G�C���A�V���O��L��
		AlphaTestEnable			= TRUE;			//���e�X�g�̗L��
		AlphaBlendEnable		= FALSE;		//���u�����h�̖���

		//�V�F�[�_�ݒ�
		VertexShader			= compile vs_3_0 VS();
		PixelShader				= compile ps_3_0 PS();
	}

	//���C�g��OFF �����o�[�g�g�U���˂��l�������e�N�Z���J���[�݂̂ŏo��
	pass p1 {
		//�X�e�[�g�ݒ�
		Zenable					= TRUE;			//Z�o�b�t�@�L��
		ZWriteEnable			= TRUE;			//Z�o�b�t�@�ւ̏������ݗL��
		ShadeMode				= GOURAUD;		//�O�[���[�E�V�F�[�f�B���O
		CullMode				= CCW;			//�w�ʂ��J�����O
		MultiSampleAntialias	= FALSE;		//�A���`�G�C���A�V���O��L��
		AlphaTestEnable			= FALSE;		//���e�X�g�̗L��
		AlphaBlendEnable		= FALSE;		//���u�����h�̖���
		//AlphaFunc				= GREATEREQUAL;	//�A���t�@��r�֐�(>=)
		//AlphaRef				= 0x00000001;	//����r��A���ȏ�̏ꍇ�`��

		//�V�F�[�_�ݒ�
		VertexShader			= compile vs_3_0 VS();
		PixelShader				= compile ps_3_0 PS1();
	}

	//���ߗL���`��
	pass p2 {
		//�X�e�[�g�ݒ�
		Zenable					= TRUE;			//Z�o�b�t�@�L��
		ZWriteEnable			= TRUE;			//Z�o�b�t�@�ւ̏������ݗL��
		ShadeMode				= GOURAUD;		//�O�[���[�E�V�F�[�f�B���O
		CullMode				= NONE;			//�w�ʂ��J�����O
		MultiSampleAntialias	= FALSE;		//�A���`�G�C���A�V���O��L��
		AlphaTestEnable			= TRUE;			//���e�X�g�̗L��
		AlphaBlendEnable		= TRUE;			//���u�����h�̖���
		AlphaFunc				= GREATEREQUAL;	//�A���t�@��r�֐�(>=)
		AlphaRef				= 0x00000001;	//����r��A���ȏ�̏ꍇ�`��

		//�V�F�[�_�ݒ�
		VertexShader			= compile vs_3_0 VS();
		PixelShader				= compile ps_3_0 PS1();
	}

	//���ߗL���`��&�őO�ʕ`��
	pass p3 {
		//�X�e�[�g�ݒ�
		Zenable					= FALSE;		//Z�o�b�t�@�L��
		ZWriteEnable			= TRUE;			//Z�o�b�t�@�ւ̏������ݗL��
		ShadeMode				= GOURAUD;		//�O�[���[�E�V�F�[�f�B���O
		CullMode				= NONE;			//�w�ʂ��J�����O
		MultiSampleAntialias	= FALSE;		//�A���`�G�C���A�V���O��L��
		AlphaTestEnable			= TRUE;			//���e�X�g�̗L��
		AlphaBlendEnable		= FALSE;		//���u�����h�̖���
		AlphaFunc				= GREATEREQUAL;	//�A���t�@��r�֐�(>=)
		AlphaRef				= 0x00000001;	//����r��A���ȏ�̏ꍇ�`��

		//�V�F�[�_�ݒ�
		VertexShader			= compile vs_3_0 VS();
		PixelShader				= compile ps_3_0 PS1();
	}
}
