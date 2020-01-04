//===================================================================================================================================
//�yInstancingBillboard.fx�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/09/23
// [�X�V��]2019/10/17
//===================================================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�O���[�o��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float4x4 matrixProjection;
float4x4 matrixView;
texture planeTexture;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��`
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
sampler textureSampler = sampler_state
{
	texture = <planeTexture>;
	MipFilter = NONE;
	MinFilter = POINT;
	MagFilter = LINEAR;
	AddressU = BORDER;
	AddressV = BORDER;
	BorderColor = 0x00000000;
};

struct VS_OUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�o�[�e�b�N�X�E�V�F�[�_�[
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�r���{�[�h
VS_OUT vsMain(
	float2 position				: POSITION, 
	float2 localUV				: TEXCOORD0,
	float3 worldPosition		: TEXCOORD1,
	float2 uv					: TEXCOORD2,
	float3 rotation				: TEXCOORD3,
	float2 scale				: TEXCOORD4,
	float4 color				: COLOR0)
{
	VS_OUT Out;

	Out.position = float4(
		position.x,
		position.y,
		0.0f,
		1.0f);

	float cosX = cos(rotation.x);
	float sinX = sin(rotation.x);
	float cosY = cos(rotation.y);
	float sinY = sin(rotation.y);
	float cosZ = cos(rotation.z);
	float sinZ = sin(rotation.z);

	//���[���h�s��
	float4x4 matrixWorld = float4x4(
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f);
	//�X�P�[���s��
	float4x4 scaleMatrix = float4x4(
		scale.x,0.0f,0.0f,0.0f,
		0.0f, scale.y,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f);
	//�ʒu�s��
	float4x4 positionMatrix = float4x4(
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		worldPosition.x, worldPosition.y, worldPosition.z,1.0f);
	//X����]�s��
	float4x4 xRotationMatrix = float4x4(
		1.0f,0.0f,0.0f,0.0f,
		0.0f,cosX,-sinX,0.0f,
		0.0f,sinX,cosX,0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//Y����]�s��
	float4x4 yRotationMatrix = float4x4(
		cosY,0.0f,sinY,0.0f,
		0.0f, 1.0f,0.0f,0.0f,
		-sinY,0.0f, cosY,0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//Z����]�s��
	float4x4 zRotationMatrix = float4x4(
		cosZ,-sinZ,0.0f,0.0f,
		sinZ,cosZ,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f);
	//�r���{�[�h����
	float4x4 cancelRotation = matrixView;
	cancelRotation._41_42_43 = 0.0f;
	cancelRotation = transpose(cancelRotation);


	//�s��̉��Z
	matrixWorld = mul(matrixWorld,scaleMatrix);				//*�X�P�[��
	matrixWorld = mul(matrixWorld,xRotationMatrix);			//*x����]
	matrixWorld = mul(matrixWorld,yRotationMatrix);			//*y����]
	matrixWorld = mul(matrixWorld,zRotationMatrix);			//*z����]
	matrixWorld = mul(matrixWorld,cancelRotation);			//*�r���{�[�h
	matrixWorld = mul(matrixWorld,positionMatrix);			//*�ړ�

	//�r���[�s��
	matrixWorld = mul(matrixWorld,matrixView);
	//�v���W�F�N�V�����s��
	matrixWorld = mul(matrixWorld,matrixProjection);

	//���_�։��Z
	Out.position = mul(Out.position, matrixWorld);

	Out.uv = localUV+uv;

	Out.color = color;

	return Out;
}

//Y���r���{�[�h
VS_OUT vsMainY(
	float2 position				: POSITION, 
	float2 localUV				: TEXCOORD0,
	float3 worldPosition		: TEXCOORD1,
	float2 uv					: TEXCOORD2,
	float3 rotation				: TEXCOORD3,
	float2 scale				: TEXCOORD4,
	float4 color				: COLOR0)
{
	VS_OUT Out;

	Out.position = float4(
		position.x,
		position.y,
		0.0f,
		1.0f);

	float cosX = cos(rotation.x);
	float sinX = sin(rotation.x);
	float cosY = cos(rotation.y);
	float sinY = sin(rotation.y);
	float cosZ = cos(rotation.z);
	float sinZ = sin(rotation.z);

	//���[���h�s��
	float4x4 matrixWorld = float4x4(
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f);
	//�X�P�[���s��
	float4x4 scaleMatrix = float4x4(
		scale.x,0.0f,0.0f,0.0f,
		0.0f, scale.y,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f);
	//�ʒu�s��
	float4x4 positionMatrix = float4x4(
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		worldPosition.x, worldPosition.y, worldPosition.z,1.0f);
	//X����]�s��
	float4x4 xRotationMatrix = float4x4(
		1.0f,0.0f,0.0f,0.0f,
		0.0f,cosX,-sinX,0.0f,
		0.0f,sinX,cosX,0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//Y����]�s��
	float4x4 yRotationMatrix = float4x4(
		cosY,0.0f,sinY,0.0f,
		0.0f, 1.0f,0.0f,0.0f,
		-sinY,0.0f, cosY,0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//Z����]�s��
	float4x4 zRotationMatrix = float4x4(
		cosZ,-sinZ,0.0f,0.0f,
		sinZ,cosZ,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f);
	//�r���{�[�h�����i�x���j
	float4x4 cancelRotation = matrixView;
	cancelRotation._41_42_43 = 0.0f;
	cancelRotation._12_22_32 = float3(0.0f,1.0f,0.0f);//Y����]�ͷ�ݾق��Ȃ�
	cancelRotation = transpose(cancelRotation);

	//�s��̉��Z
	matrixWorld = mul(matrixWorld,scaleMatrix);				//*�X�P�[��
	matrixWorld = mul(matrixWorld,xRotationMatrix);			//*x����]
	matrixWorld = mul(matrixWorld,yRotationMatrix);			//*y����]
	matrixWorld = mul(matrixWorld,zRotationMatrix);			//*z����]
	matrixWorld = mul(matrixWorld ,cancelRotation);			//*�r���{�[�h
	matrixWorld = mul(matrixWorld,positionMatrix);			//*�ړ�

	//�r���[�s��
	matrixWorld = mul(matrixWorld,matrixView);
	//�v���W�F�N�V�����s��
	matrixWorld = mul(matrixWorld,matrixProjection);

	//���_�։��Z
	Out.position = mul(Out.position, matrixWorld);

	Out.uv = localUV+uv;

	Out.color = color;

	return Out;
}

//�r���{�[�hOFF
VS_OUT vsMainOFF(
	float2 position				: POSITION, 
	float2 localUV				: TEXCOORD0,
	float3 worldPosition		: TEXCOORD1,
	float2 uv					: TEXCOORD2,
	float3 rotation				: TEXCOORD3,
	float2 scale				: TEXCOORD4,
	float4 color				: COLOR0)
{
	VS_OUT Out;

	Out.position = float4(
		position.x,
		position.y,
		0.0f,
		1.0f);

	float cosX = cos(rotation.x);
	float sinX = sin(rotation.x);
	float cosY = cos(rotation.y);
	float sinY = sin(rotation.y);
	float cosZ = cos(rotation.z);
	float sinZ = sin(rotation.z);

	//���[���h�s��
	float4x4 matrixWorld = float4x4(
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f);
	//�X�P�[���s��
	float4x4 scaleMatrix = float4x4(
		scale.x,0.0f,0.0f,0.0f,
		0.0f, scale.y,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f);
	//�ʒu�s��
	float4x4 positionMatrix = float4x4(
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		worldPosition.x, worldPosition.y, worldPosition.z,1.0f);
	//X����]�s��
	float4x4 xRotationMatrix = float4x4(
		1.0f,0.0f,0.0f,0.0f,
		0.0f,cosX,-sinX,0.0f,
		0.0f,sinX,cosX,0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//Y����]�s��
	float4x4 yRotationMatrix = float4x4(
		cosY,0.0f,sinY,0.0f,
		0.0f, 1.0f,0.0f,0.0f,
		-sinY,0.0f, cosY,0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//Z����]�s��
	float4x4 zRotationMatrix = float4x4(
		cosZ,-sinZ,0.0f,0.0f,
		sinZ,cosZ,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f);

	//�s��̉��Z
	matrixWorld = mul(matrixWorld,scaleMatrix);				//*�X�P�[��
	matrixWorld = mul(matrixWorld,xRotationMatrix);			//*x����]
	matrixWorld = mul(matrixWorld,yRotationMatrix);			//*y����]
	matrixWorld = mul(matrixWorld,zRotationMatrix);			//*z����]
	matrixWorld = mul(matrixWorld,positionMatrix);			//*�ړ�

	//�r���[�s��
	matrixWorld = mul(matrixWorld,matrixView);
	//�v���W�F�N�V�����s��
	matrixWorld = mul(matrixWorld,matrixProjection);

	//���_�։��Z
	Out.position = mul(Out.position, matrixWorld);

	Out.uv = localUV+uv;

	Out.color = color;

	return Out;
}

//�Œ�T�C�Y�r���{�[�h
VS_OUT vsMainFixedSize(
	float2 position				: POSITION, 
	float2 localUV				: TEXCOORD0,
	float3 worldPosition		: TEXCOORD1,
	float2 uv					: TEXCOORD2,
	float3 rotation				: TEXCOORD3,
	float2 scale				: TEXCOORD4,
	float4 color				: COLOR0)
{
	VS_OUT Out;

	Out.position = float4(
		position.x,
		position.y,
		0.0f,
		1.0f);

	float cosX = cos(rotation.x);
	float sinX = sin(rotation.x);
	float cosY = cos(rotation.y);
	float sinY = sin(rotation.y);
	float cosZ = cos(rotation.z);
	float sinZ = sin(rotation.z);

	//���[���h�s��
	float4x4 matrixWorld = float4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//�X�P�[���s��
	float4x4 scaleMatrix = float4x4(
		scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	//�ʒu�s��
	//float4x4 positionMatrix = float4x4(
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//	0.0f, 0.0f, 1.0f, 0.0f,
	//	worldPosition.x, worldPosition.y, worldPosition.z, 1.0f);
	//X����]�s��
	float4x4 xRotationMatrix = float4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosX, -sinX, 0.0f,
		0.0f, sinX, cosX, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//Y����]�s��
	float4x4 yRotationMatrix = float4x4(
		cosY, 0.0f, sinY, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sinY, 0.0f, cosY, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//Z����]�s��
	float4x4 zRotationMatrix = float4x4(
		cosZ, -sinZ, 0.0f, 0.0f,
		sinZ, cosZ, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	//�r���{�[�h����
	//float4x4 cancelRotation = matrixView;
	//cancelRotation._41_42_43 = 0.0f;
	//cancelRotation = transpose(cancelRotation);


	//�s��̉��Z
	matrixWorld = mul(matrixWorld, scaleMatrix);				//*�X�P�[��
	//matrixWorld = mul(matrixWorld, xRotationMatrix);			//*x����]
	//matrixWorld = mul(matrixWorld, yRotationMatrix);			//*y����]
	//matrixWorld = mul(matrixWorld, zRotationMatrix);			//*z����]
	//matrixWorld = mul(matrixWorld, cancelRotation);				//*�r���{�[�h
	//matrixWorld = mul(matrixWorld, positionMatrix);				//*�ړ�

	//�r���[�s��
	//matrixWorld = mul(matrixWorld, matrixView);
	//�v���W�F�N�V�����s��
	//matrixWorld = mul(matrixWorld, matrixProjection);
	//���ˉe�s��
	//matrixWorld = mul(matrixWorld, matrixOrtho);

	//���_�։��Z
	Out.position = mul(Out.position, matrixWorld);

	//�r���[�~�v���W�F�N�V�����ϊ�
	float4 orthoPosition = float4(worldPosition, 1.0f);
	orthoPosition = mul(orthoPosition, matrixView);
	orthoPosition = mul(orthoPosition, matrixProjection);
	orthoPosition = orthoPosition / orthoPosition.w;
	Out.position.xy = Out.position.xy + orthoPosition.xy;

	Out.uv = localUV + uv;

	Out.color = color;

	return Out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�s�N�Z���E�V�F�[�_�[
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float4 psMain(VS_OUT In) : COLOR0
{
	return tex2D(textureSampler, In.uv)*In.color;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �e�N�j�b�N
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
technique mainTechnique {


	//�ʏ�r���{�[�h
	pass p0 {
		//�X�e�[�g�ݒ�
		Zenable					= TRUE;				//Z�o�b�t�@
		ZWriteEnable			= TRUE;				//Z�o�b�t�@�ւ̏�������
		CullMode				= CCW;				//�w�ʂ��J�����O
		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain();
	}

	//�ʏ�r���{�[�h�i���߁j
	pass p1 {

		//�X�e�[�g�ݒ�
		Zenable					= TRUE;			//Z�o�b�t�@
		ZWriteEnable			= FALSE;		//Z�o�b�t�@�ւ̏�������
		CullMode				= CCW;			//�w�ʂ��J�����O

		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain();
	}

	//�ʏ�r���{�[�h�i�őO�ʁj
	pass p2 {

		//�X�e�[�g�ݒ�
		Zenable					= FALSE;		//Z�o�b�t�@
		ZWriteEnable			= FALSE;		//Z�o�b�t�@�ւ̏�������
		CullMode				= CCW;			//�w�ʂ��J�����O

		VertexShader = compile vs_2_0 vsMain();
		PixelShader = compile ps_2_0 psMain();
	}

	//Y���r���{�[�h
	pass p3 {
		//�X�e�[�g�ݒ�
		Zenable					= TRUE;				//Z�o�b�t�@
		ZWriteEnable			= TRUE;				//Z�o�b�t�@�ւ̏�������
		CullMode				= CCW;				//�w�ʂ��J�����O
		VertexShader = compile vs_2_0 vsMainY();
		PixelShader = compile ps_2_0 psMain();
	}


	//Y���r���{�[�h�i���߁j
	pass p4 {

		//�X�e�[�g�ݒ�
		Zenable					= TRUE;			//Z�o�b�t�@
		ZWriteEnable			= FALSE;		//Z�o�b�t�@�ւ̏�������
		CullMode				= CCW;			//�w�ʂ��J�����O

		VertexShader = compile vs_2_0 vsMainY();
		PixelShader = compile ps_2_0 psMain();
	}

	//Y���r���{�[�h�i�őO�ʁj
	pass p5 {

		//�X�e�[�g�ݒ�
		Zenable					= FALSE;		//Z�o�b�t�@
		ZWriteEnable			= FALSE;		//Z�o�b�t�@�ւ̏�������
		CullMode				= CCW;			//�w�ʂ��J�����O

		VertexShader = compile vs_2_0 vsMainY();
		PixelShader = compile ps_2_0 psMain();
	}

	//�r���{�[�hOFF
	pass p6 {
		//�X�e�[�g�ݒ�
		Zenable = TRUE;				//Z�o�b�t�@
		ZWriteEnable = TRUE;				//Z�o�b�t�@�ւ̏�������
		CullMode = CCW;				//�w�ʂ��J�����O
		VertexShader = compile vs_2_0 vsMainOFF();
		PixelShader = compile ps_2_0 psMain();
	}


	//�r���{�[�hOFF�i���߁j
	pass p7 {

		//�X�e�[�g�ݒ�
		Zenable = TRUE;			//Z�o�b�t�@
		ZWriteEnable = FALSE;		//Z�o�b�t�@�ւ̏�������
		CullMode = CCW;			//�w�ʂ��J�����O

		VertexShader = compile vs_2_0 vsMainOFF();
		PixelShader = compile ps_2_0 psMain();
	}

	//�r���{�[�hOFF�i�őO�ʁj
	pass p8 {

		//�X�e�[�g�ݒ�
		Zenable = FALSE;		//Z�o�b�t�@
		ZWriteEnable = FALSE;		//Z�o�b�t�@�ւ̏�������
		CullMode = CCW;			//�w�ʂ��J�����O

		VertexShader = compile vs_2_0 vsMainOFF();
		PixelShader = compile ps_2_0 psMain();
	}

	//�Œ�T�C�Y
	pass p9 {
		//�X�e�[�g�ݒ�
		Zenable = TRUE;				//Z�o�b�t�@
		ZWriteEnable = TRUE;				//Z�o�b�t�@�ւ̏�������
		CullMode = CCW;				//�w�ʂ��J�����O
		MultiSampleAntialias = TRUE;		//�A���`�G�C���A�V���O��L��
		VertexShader = compile vs_2_0 vsMainFixedSize();
		PixelShader = compile ps_2_0 psMain();
	}


	//�Œ�T�C�Y�i���߁j
	pass p10 {

		//�X�e�[�g�ݒ�
		Zenable = TRUE;			//Z�o�b�t�@
		ZWriteEnable = FALSE;		//Z�o�b�t�@�ւ̏�������
		CullMode = CCW;			//�w�ʂ��J�����O
		MultiSampleAntialias = TRUE;		//�A���`�G�C���A�V���O��L��

		VertexShader = compile vs_2_0 vsMainFixedSize();
		PixelShader = compile ps_2_0 psMain();
	}

	//�Œ�T�C�Y�i�őO�ʁj
	pass p11 {

		//�X�e�[�g�ݒ�
		Zenable = FALSE;		//Z�o�b�t�@
		ZWriteEnable = FALSE;		//Z�o�b�t�@�ւ̏�������
		CullMode = CCW;			//�w�ʂ��J�����O
		MultiSampleAntialias = TRUE;		//�A���`�G�C���A�V���O��L��

		VertexShader = compile vs_2_0 vsMainFixedSize();
		PixelShader = compile ps_2_0 psMain();
	}

}
