//===================================================================================================================================
//�yBase.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2020/01/01
// [�X�V��]2020/01/01
//===================================================================================================================================

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "Base.h"
//#include "Sound.h"

//===================================================================================================================================
//�y�O���[�o���ϐ��z
//===================================================================================================================================
char rootPath[1124] = { 0 };

//===================================================================================================================================
//�y�֐���`�z
//===================================================================================================================================

//-----------------------------------------------------------------------------------------------------------------------------------
//���[�g�p�X�̏������֐�
//[�p�r]���[�g�p�X�ϐ��փ��[�g�p�X�֕ۑ�����
//-----------------------------------------------------------------------------------------------------------------------------------
void initializeDirectory(char* root)
{
	strcpy(rootPath, root);//�p�X(root)��rootPath�փR�s�[
}

//-----------------------------------------------------------------------------------------------------------------------------------
//���[�g�f�B���N�g���ւ̃Z�b�g�֐�			
//[�p�r]���[�g�f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
//-----------------------------------------------------------------------------------------------------------------------------------
void setRootDirectory()
{
	SetCurrentDirectory(rootPath);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�f�[�^�f�B���N�g���ւ̃Z�b�g�֐�	
//[�p�r]�Z�[�u�f�[�^��e�L�X�g�f�[�^���i�[����f�[�^�f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
//-----------------------------------------------------------------------------------------------------------------------------------
void setDataDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\01 Data File");
	SetCurrentDirectory(tmporary);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�e�N�X�`���f�B���N�g���ւ̃Z�b�g�֐�
//[�p�r]�e�N�X�`�����i�[����e�N�X�`���f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
//-----------------------------------------------------------------------------------------------------------------------------------
void setTextureDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\02 Texture File");
	SetCurrentDirectory(tmporary);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�V�F�[�_�[�f�B���N�g���ւ̃Z�b�g�֐�		
//[�p�r]�V�F�[�_�[�t�@�C�����i�[����V�F�[�_�[�f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
//-----------------------------------------------------------------------------------------------------------------------------------
void setShaderDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\03 Shader File");
	SetCurrentDirectory(tmporary);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�T�E���h�f�B���N�g���ւ̃Z�b�g�֐�		
//[�p�r]�T�E���h�f�[�^���i�[����T�E���h�f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
//-----------------------------------------------------------------------------------------------------------------------------------
void setSoundDirectory(int endpointVoiceId)
{
	//char tmporary[512] = { 0 };
	//strcpy(tmporary, rootPath);
	//if (endpointVoiceId == ENDPOINT_VOICE_LIST::ENDPOINT_SE)
	//{
	//	strcat(tmporary, "\\04 Sound File\\SE");
	//}
	//else if (endpointVoiceId == ENDPOINT_VOICE_LIST::ENDPOINT_BGM)
	//{
	//	strcat(tmporary, "\\04 Sound File\\BGM");
	//}
	//else if (endpointVoiceId == ENDPOINT_VOICE_LIST::ENDPOINT_S3D)
	//{
	//	strcat(tmporary, "\\04 Sound File\\3D");
	//}
	//else
	//{
	//	strcat(tmporary, "\\04 Sound File");
	//}
	//SetCurrentDirectory(tmporary);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�c�[���f�B���N�g���ւ̃Z�b�g�֐�	
//[�p�r]�c�[���f�[�^���i�[����c�[���f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
//-----------------------------------------------------------------------------------------------------------------------------------
void setToolsDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\05 Tools File");
	SetCurrentDirectory(tmporary);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�G�t�F�N�V�A�[�f�B���N�g���ւ̃Z�b�g�֐�		
//[�p�r]�G�t�F�N�V�A�[�t�@�C�����i�[����G�t�F�N�V�A�[�f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
//-----------------------------------------------------------------------------------------------------------------------------------
void setEffekseerDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\06 Effekseer File");
	SetCurrentDirectory(tmporary);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//���f���f�B���N�g���ւ̃Z�b�g�֐�
//[�p�r]3D���f���f�[�^���i�[���郂�f���f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
//-----------------------------------------------------------------------------------------------------------------------------------
void setModelDirectory()
{
	char tmporary[512] = { 0 };
	strcpy(tmporary, rootPath);
	strcat(tmporary, "\\07 Model File");
	SetCurrentDirectory(tmporary);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�p������
//-----------------------------------------------------------------------------------------------------------------------------------
void Base::postureControl(D3DXQUATERNION* quaternion, D3DXVECTOR3 currentDirection, D3DXVECTOR3 nextDirection, float t)
{
	D3DXVECTOR3 controlAxis;
	//�@���ƃL�����N�^�[�Ƃ̊O�ς����߂�i���ʂɒ������邽�߂̉�]���ƂȂ�j
	D3DXVec3Cross(&controlAxis, &currentDirection, &nextDirection);
	D3DXVec3Normalize(&controlAxis, &controlAxis);
	float rotationRadian;
	if (formedRadianAngle(&rotationRadian, currentDirection, nextDirection))
	{
		anyAxisRotationSlerp(quaternion, controlAxis, rotationRadian, t);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�C�ӎ����^��ԉ�]
//-----------------------------------------------------------------------------------------------------------------------------------
void Base::anyAxisRotationSlerp(D3DXQUATERNION* quaternion, D3DXVECTOR3 axis, float radian, float t)
{
	D3DXQUATERNION deltaRotation(0, 0, 0, 1);
	D3DXQuaternionRotationAxis(&deltaRotation, &axis, radian);
	deltaRotation = *quaternion * deltaRotation;
	D3DXQuaternionSlerp(quaternion, quaternion, &deltaRotation, t);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�C�ӎ���]
//-----------------------------------------------------------------------------------------------------------------------------------
void Base::anyAxisRotation(D3DXQUATERNION* quaternion, D3DXVECTOR3 axis, float degree)
{
	D3DXQUATERNION rotationQ(0, 0, 0, 1);
	float radian = D3DXToRadian(degree);
	D3DXQuaternionRotationAxis(&rotationQ, &axis, radian);

	//����*��]�Ώ�*��]�N�H�[�^�j�I��
	*quaternion *= rotationQ;
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�C�ӎ���]
//-----------------------------------------------------------------------------------------------------------------------------------
void Base::anyAxisRotation(D3DXVECTOR3* vector,D3DXVECTOR3 axis, float degree)
{
	//�x�N�g�����N�H�[�^�j�I���ɒu��������
	D3DXQUATERNION vectorQuaternion;
	vectorQuaternion.x = vector->x;
	vectorQuaternion.y = vector->y;
	vectorQuaternion.z = vector->z;
	vectorQuaternion.w = 1.0f;

	D3DXQUATERNION conjugateQ;
	D3DXQUATERNION rotationQ(0, 0, 0, 1);
	float radian = D3DXToRadian(degree);
	D3DXQuaternionRotationAxis(&rotationQ, &axis, radian);
	D3DXQuaternionConjugate(&conjugateQ, &rotationQ);
	
	D3DXQUATERNION temporaryQ;
	//����*��]�Ώ�*��]�N�H�[�^�j�I��
	temporaryQ = conjugateQ * vectorQuaternion * rotationQ;

	*vector = (D3DXVECTOR3)temporaryQ;
}

//-----------------------------------------------------------------------------------------------------------------------------------
//��̃x�N�g���̂Ȃ��p���v�Z
//          v1�Ev2
//cos�� = -------------
//         |v1|*|v2|
//-----------------------------------------------------------------------------------------------------------------------------------
bool Base::formedRadianAngle(float* out, D3DXVECTOR3 v1, D3DXVECTOR3 v2) {
	float dot = D3DXVec3Dot(&v1, &v2);
	if (isnan(dot))return false;

	float v1Length = D3DXVec3Length(&v1);
	float v2Length = D3DXVec3Length(&v2);
	if (v1Length == 0 || v2Length == 0)return false;

	*out = acosf(dot / (v1Length*v2Length));
	if (isnan(*out))return false;
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�X���b�v�֐�(���˃x�N�g��L�̃x�N�g��N�ɔ�����x�N�g��������ł������B�j
//-----------------------------------------------------------------------------------------------------------------------------------
D3DXVECTOR3 Base::slip(D3DXVECTOR3 L, D3DXVECTOR3 N)
{
	D3DXVECTOR3 S; //����x�N�g���i��������j

	//����x�N�g�� S=L-(N * L)/(|N|^2)*N
	S = L - ((D3DXVec3Dot(&N, &L)) / (powf(D3DXVec3Length(&N), 2)))*N;

	return S;
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�Q�̈ʒu�x�N�g���Ԃ̋������v�Z����
//-----------------------------------------------------------------------------------------------------------------------------------
float Base::between2VectorLength(D3DXVECTOR3 position1, D3DXVECTOR3 position2)
{
	return D3DXVec3Length(&(position1 - position2));
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�Q�̈ʒu�x�N�g���Ԃ̋����̌v�Z�ɉ����A�ʒu�P����ʒu�Q�Ɍ������i1��2�j�x�N�g�����쐬����(�m����1)
//-----------------------------------------------------------------------------------------------------------------------------------
float Base::between2VectorDirection(D3DXVECTOR3* out, D3DXVECTOR3 position1, D3DXVECTOR3 position2)
{
	D3DXVECTOR3 direction = position2 - position1;
	D3DXVec3Normalize(out, &direction);
	return D3DXVec3Length(&direction);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//���_�o�b�t�@�ւ̃R�s�[
//-----------------------------------------------------------------------------------------------------------------------------------
void Base::copyVertexBuffer(unsigned size, void *sorce, IDirect3DVertexBuffer9 *buffer) {
	void *p = 0;
	buffer->Lock(0, 0, &p, 0);
	memcpy(p, sorce, size);
	buffer->Unlock();
}

//-----------------------------------------------------------------------------------------------------------------------------------
//����_�Ƃ̐�����ōł��߂��_�����߂�
//-----------------------------------------------------------------------------------------------------------------------------------
D3DXVECTOR3 Base::nearestPointOnLine(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXVECTOR3 point)
{
	//�n�_����I�_�ւ̐����x�N�g�������߂�
	D3DXVECTOR3 line = end - start;
	//�����̑傫�������߂�
	float length = D3DXVec3Length(&line);
	//�����̑傫����0�ł���΍ł��߂��_�͎n�_�y�яI�_�Ƃ�߂����ƂŐ�������i0���Z�h�~�j
	if (length == 0)return start;

	//�n�_����_�ւ̃x�N�g�������߂�
	D3DXVECTOR3 toPoint = point - start;
	//��L��̃x�N�g���̓��ς����߂�
	float dot = D3DXVec3Dot(&line, &toPoint);
	//�����̎n�_����A�_��������֐����ɉ�������_�Ƃ̋��������߂�(����/�����̑傫���j
	float distance = dot / length;
	//�n�_�����_�Ƃ̋����𔻒f���āA�ł��߂��_��߂�
	if (distance <= 0)
	{
		return start;
	}
	else if (distance >= D3DXVec3Length(&line)) {
		return end;
	}
	else
	{
		D3DXVECTOR3 result;
		D3DXVec3Normalize(&result, &line);
		result = (result * distance) + start;
		return result;
	}
}

//-----------------------------------------------------------------------------------------------------------------------------------
//����_���畽�ʂ܂ł̋��������߂�
//-----------------------------------------------------------------------------------------------------------------------------------
float Base::betweenDistancePointAndPlane(D3DXPLANE plane, D3DXVECTOR3 point)
{
	D3DXVECTOR3 normal;
	D3DXVec3Normalize(&normal,&D3DXVECTOR3(plane.a,plane.b,plane.c));
	D3DXPLANE tmp = D3DXPLANE(normal.x, normal.y, normal.z, plane.d);
	return D3DXPlaneDotCoord(&tmp, &point);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//�Q�����̍ŒZ����
//-----------------------------------------------------------------------------------------------------------------------------------
float Base::between2LineDistance(Line line1, Line line2)
{
	float distance;
	
	D3DXVECTOR3 v1;between2VectorDirection(&v1, line1.start, line1.end);
	D3DXVECTOR3 v2;between2VectorDirection(&v2, line2.start, line2.end);
	D3DXVECTOR3 v12 = line2.start - line1.start;
	D3DXVECTOR3 normal;D3DXVec3Cross(&normal, &v1, &v2);D3DXVec3Normalize(&normal, &normal);
	//���� = |N�Ev12|/|N|;
	distance = D3DXVec3Dot(&normal, &v12);

	if (distance < 0)distance *= -1;

	return distance;
}



