//===================================================================================================================================
//�yBase.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2020/01/01
// [�X�V��]2020/01/01
//===================================================================================================================================
#define D3D_DEBUG_INFO
#define XAUDIO2_ON		(true)
#define XADUIO2_OFF		(flase)
#define XADUIO2_STATE	(XAUDIO2_ON) 
//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#pragma once
#include <stdio.h>
#include <crtdbg.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <VersionHelpers.h>

#if(XADUIO2_STATE)
#include <xaudio2.h>
#include <x3daudio.h>
#endif
//===================================================================================================================================
//�y�K�v�ȃ��C�u�����t�@�C���̃��[�h�z
//===================================================================================================================================
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")

#if(XADUIO2_STATE)
#pragma comment(lib,"xaudio2.lib")
#pragma comment(lib,"x3daudio.lib")
#endif

//===================================================================================================================================
//�y�x����\���z
//===================================================================================================================================
#pragma warning(disable:4305)
#pragma warning(disable:4996)
#pragma warning(disable:4018)
#pragma warning(disable:4111)

//===================================================================================================================================
//�y�}�N����`�z
//===================================================================================================================================
#ifdef _DEBUG
//Debug
#define APP_NAME (LPSTR)"D/A:Nature"
#if TRUE
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#else
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#endif
//#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#else
//Release
#define APP_NAME (LPSTR)"D/A:Nature"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#endif // _DEBUG
//Common
#define MFAIL(code,string) if(FAILED(code)){MessageBox(0,string,"error",MB_OK);return E_FAIL;}
#define MFALSE(code,string) if(!(code)) {MessageBox(0,string,"error",MB_OK);return E_FAIL;}
#define MSG(text) MessageBox(0,text,"message", MB_OK|MB_TOPMOST);
#define MESSAGE(text,title) MessageBox(0,text,title, MB_OK|MB_TOPMOST);

//===================================================================================================================================
//�y�|�C���^�Q�ƍ��ڂ����S�ɏ������邽�߂̊֐��e���v���[�g�z
// �����̃e���v���[�g�ɂ���Ē�`���ꂽ�֐��́A
// �ʏ�̊֐��Ăяo���\�����g�p���ČĂяo�����Ƃ��ł��܂��B
// �R���p�C���́AT���Ăяo���p�����[�^�̌^�ɒu��������֐����쐬���܂��B
//===================================================================================================================================
// �|�C���^�Q�Ƃ����A�C�e�������S�ɉ��
template<typename T>
inline void safeRelease(T& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = NULL;
	}
}
#define SAFE_RELEASE safeRelease //����݊����̂��߂�

// �|�C���^�Q�Ƃ����A�C�e�������S�ɍ폜
template<typename T>
inline void safeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE safeDelete//����݊����̂��߂�

// �|�C���^�Q�Ƃ����z������S�ɍ폜
template<typename T>
inline void safeDeleteArray(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = NULL;
	}
}
#define SAFE_DELETE_ARRAY safeDeleteArray //����݊����̂��߂�

//===================================================================================================================================
//�y�萔��`�z
//===================================================================================================================================
static const int FRAME_RATE = 60;
static const int MAX_FRAME_RATE = 200;
static const int MIN_FRAME_RATE = 5;

//===================================================================================================================================
//�y�\���́z
//===================================================================================================================================
struct Vertex3D
{
	D3DXVECTOR3 coord;
};
struct Vertex2D
{
	D3DXVECTOR2 coord;
};
struct UV
{
	D3DXVECTOR2 coord;
};
struct Line
{
	D3DXVECTOR3 start;
	D3DXVECTOR3 end;
};
struct Cylinder
{
	Line		centerLine;
	float		height;
	float		radius;
};

//===================================================================================================================================
//�y�N���X�z
//===================================================================================================================================
class Base
{
public:
	static void postureControl(D3DXQUATERNION* quaternion, D3DXVECTOR3 currentDirection, D3DXVECTOR3 nextDirection, float time);	//�p������
	static void anyAxisRotationSlerp(D3DXQUATERNION* quaternion, D3DXVECTOR3 axis, float radian, float time);						//�C�ӎ����^��ԉ�]
	static void anyAxisRotation(D3DXQUATERNION* quaternion, D3DXVECTOR3 axis, float degree);										//�C�ӎ���]
	static void anyAxisRotation(D3DXVECTOR3* vector, D3DXVECTOR3 axis, float degree);										//�C�ӎ���]
	static bool formedRadianAngle(float* out, D3DXVECTOR3 v1, D3DXVECTOR3 v2);														//��̃x�N�g���̂Ȃ��p���v�Z
	D3DXVECTOR3 slip(D3DXVECTOR3 L, D3DXVECTOR3 N);																					//�X���b�v�֐�(���˃x�N�g��L�̃x�N�g��N�ɔ�����x�N�g��������ł������B�j
	static float between2VectorLength(D3DXVECTOR3 position1, D3DXVECTOR3 position2);												//�Q�̈ʒu�x�N�g���Ԃ̋������v�Z����
	static float between2VectorDirection(D3DXVECTOR3* out, D3DXVECTOR3 position1, D3DXVECTOR3 position2);							//�Q�̈ʒu�x�N�g���Ԃ̋����̌v�Z�ɉ����A�ʒu�P����ʒu�Q�Ɍ������i1��2�j�x�N�g�����쐬����(�m����1)
	void copyVertexBuffer(unsigned size, void *sorce, IDirect3DVertexBuffer9 *buffer);												//���_�o�b�t�@�ւ̃R�s�[
	D3DXVECTOR3 nearestPointOnLine(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXVECTOR3 point);											//����_�Ƃ̐�����ōł��߂��_�����߂�
	static float betweenDistancePointAndPlane(D3DXPLANE plane, D3DXVECTOR3 point);
	static float between2LineDistance(Line line1, Line line2);

};

//===================================================================================================================================
//�y�v���g�^�C�v�錾�z
//===================================================================================================================================
void initializeDirectory(char* root);			//���[�g�p�X�̏������֐�					[�p�r]���[�g�p�X�ϐ��փ��[�g�p�X�֕ۑ�����
void setRootDirectory();						//���[�g�f�B���N�g���ւ̃Z�b�g�֐�			[�p�r]���[�g�f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
void setDataDirectory();						//�f�[�^�f�B���N�g���ւ̃Z�b�g�֐�			[�p�r]�Z�[�u�f�[�^��e�L�X�g�f�[�^���i�[����f�[�^�f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
void setTextureDirectory();						//�e�N�X�`���f�B���N�g���ւ̃Z�b�g�֐�		[�p�r]�e�N�X�`�����i�[����e�N�X�`���f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
void setModelDirectory();						//���f���f�B���N�g���ւ̃Z�b�g�֐�			[�p�r]3D���f���f�[�^���i�[���郂�f���f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
void setShaderDirectory();						//�V�F�[�_�[�f�B���N�g���ւ̃Z�b�g�֐�		[�p�r]�V�F�[�_�[�t�@�C�����i�[����V�F�[�_�[�f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
void setSoundDirectory(int endpointVoiceId);	//�T�E���h�f�B���N�g���ւ̃Z�b�g�֐�		[�p�r]�T�E���h�f�[�^���i�[����T�E���h�f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
void setEffekseerDirectory();					//�G�t�F�N�V�A�[�f�B���N�g���ւ̃Z�b�g�֐�	[�p�r]�G�t�F�N�V�A�[�t�@�C�����i�[����V�F�[�_�[�f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���
void setToolsDirectory();						//�c�[���f�B���N�g���ւ̃Z�b�g�֐�			[�p�r]�c�[���f�[�^���i�[����c�[���f�B���N�g���փJ�����g�f�B���N�g����؂�ւ���