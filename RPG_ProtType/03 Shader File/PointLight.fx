//===================================================================================================================================
//�yPointLight.fx�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/09/01
// [�X�V��]2019/09/01
//===================================================================================================================================

struct ConstantBuffer {
	float4x4 world;
	float4x4 view;
	float4x4 projection;
	float4 light;			//�����̍��W
	float4 attenuation;		//�����p�����[�^
};


struct VS_IN
{
	float4 pos : POSITION;
	float4 nor : NORMAL;
};

struct VS_OUT
{
	float4 pos	: SV_POSTION;
	float4 posw	: SV_POSTION;
	float4 pos	: SV_POSTION;

};







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�O���[�o��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float4x4	matrixWVP;		//���[���h�~�r���[�~���ߎˉe
float4		color;			//�{�����[�����C�g�̐F���w�肷��
float		farZ;			//���ߎˉe�s��̍ŉ��ߋ���

sampler textureSampler0 :register(s0);	//PASS0:�{�����[�����C�g�̃e�N�X�`�� PASS1:�V�[���̃J���[���e�N�X�`��
sampler textureSampler1 :register(s1);	//�o�b�N�o�b�t�@�̂y�l
sampler textureSampler2 :register(s2);	//�{�����[�����C�g�̎�O�ʂ�Z�l
sampler textureSampler3 :register(s3);	//�{�����[�����C�g�̉��ʂ�Z�l

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�{�����[�����C�g��Z�l���擾����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct VSVolume_OUTPUT
{
	float4 position		:POSITION;
	float2 uv			:TEXCOORD0;
	float4 positionWVP	:TEXCOORD1;
};

VSVolume_OUTPUT VSVolume(
	float4 position		: POSITION,
	float2 uv			: TEXCOORD0)
{
	VS_OUTPUT Out;

	Out.position = mul(position, matrixWVP);
	Out.uv = uv;
	Out.positionWVP = Out.position;

	return Out;
}

float4 PSVolume(VSVolume_OUTPUT In) : COLOR0
{
	float4 Out;

	//Z�l���Z�b�g
	Out.r = In.positionWVP.z / farZ;

	//�{�����[�����C�g�ɒ���t�����e�N�X�`������F�����擾����
	Out.g = tex2D(textureSampler0, In.uv);

	Out.b = 0.0f;
	Out.a = 0.0f;

	return Out;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�{�����[�����C�g�̌��ݏ����擾���A�V�[���̃J���[���Ɖ��Z��������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct VSFinal_OUTPUT
{
	float4 position	: POSITION;
	float2 uv		:TEXCOORD0;
};

VSFinal_OUTPUT VSFinal(
	float4 position		: POSITION,
	float2 uv : TEXCOORD0)
{
	VSFinal_OUTPUT Out;
	Out.position = position;
	Out.uv = uv;

	return Out;
}

//�{�����[�����C�g�̖��邳�𒲐����邽�߂̊֐�
float Adjustment(float parameter)
{
	return parameter * 120.0f;
}

float4 PSFinal(VSFinal_OUTPUT In):COLOR
{
	float4 col;

	//�o�b�N�o�b�t�@��Z�l���
	float z = tex2D(textureSampler1, In.uv).r;

	//�{�����[�����C�g�̎�O�ʂ�Z�l���擾
	float2 ColCCW = tex2D(textureSmapler2, In.uv).rg;

	//�{�����[�����C�g�̉��ʂ�Z�l���擾
	float2 ColCW = tex2D(textureSampler3, In.uv).rg;

	float C;

	//�{�����[�����C�g��������Ȃ����� �܂��� �V�[����Z�l <= �{�����[�����C�g�̎�O�ʂ�Z�l�̂Ƃ�(�{�����[�����C�g�����S�ɎՒf����Ƃ�)
	if (ColCW.r == 0.0f || z <= ColCCW.r)
	{
		col = tex2D(texuterSampler0, In.uv);
	}

	//�V�[����Z�l <= �{�����[�����C�g�̉��ʂ�Z�l�̂Ƃ�
	//�{�����[�����C�g�̒��ɃI�u�W�F�N�g�����݂���Ƃ�
	else if (z <= ColCw.r && z >= ColCCW.r)
	{
		C = (z - ColCCW.r);

		//�{�����[�����C�g�̖��邳�𒲐߂��A����Ɏ�O�ʂƉ��ʂł��ꂼ��e�N�X�`������擾�����F���̕��ϒl��ώZ����
		C = Adjustment(C)*(ColCCW.g + ColCW.g)*0.5f;
		col = tex2D(textureSampler0, In.uv) + color * C;
	}

	else
	{
		C = (ColCW.r - ColCCW.r);
		C = Adjustment(C) * (ColCCW.g + ColCW.g) * 0.5f;
		Col = tex2D(textureSampler0, In.uv) + color * C;
	}

	return col;
}

technique main
{
	//�{�����[�����C�g��Z�l���擾
	pass P0
	{
		VertexShader = compile vs_2_0 VSVolume();
		PixelShader = compile vs_2_0 PSVolume();
	}

	//�{�����[�����C�g�̌��݂��v�Z���A�V�[���̐F���Ɖ��Z��������
	pass P1
	{
		VertexShader = compile vs_2_0 VSFinal();
		PixelShader = compile vs_2_0 PSFinal();
	}
}