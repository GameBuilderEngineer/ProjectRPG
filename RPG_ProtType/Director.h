//===================================================================================================================================
//�yDirector.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/09/17
// [�X�V��]2019/10/19
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "Base.h"
#include "MemoryViewer.h"
#include "Window.h"
#include "Direct3D9.h"
#include "ImguiManager.h"
#include "Input.h"
//#include "VirtualController.h"
//#include "AbstractScene.h"
//#include "TextureLoader.h"
//#include "StaticMeshLoader.h"
//#include "ShaderLoader.h"
//#include "TextManager.h"
//#include "GameMaster.h"
//#include "Fader.h"
//#include "EffekseerManager.h"
//#include "SerialCommunication.h"
//#include "AnimationLoader.h"
//#include <thread>
//#include "Sound.h"

//===================================================================================================================================
//�y�񋓌^�萔�z
//===================================================================================================================================
enum
{
	VARIABLE_FPS,	//�σt���[�����[�g
	FIXED_FPS,		//�Œ�t���[�����[�g
};

//===================================================================================================================================
//�y�Ǘ��N���X�z
//[�p�r]�A�v���P�[�V�����S�̂̊Ǘ����s���N���X
//===================================================================================================================================
class Director : public Base
{
public:
	//Data
#ifdef _DEBUG
	MemoryViewer*		memory;
	ImguiManager*		imgui;					//imgui�}�l�[�W���[�N���X
	//std::thread*		thread_a;
	bool				onGUI;					//GUI�\���t���O
#endif // _DEBUG

	HINSTANCE				instance;				//�C���X�^���X
	Window*					window;					//�E�B���h�E�N���X�E�n���h��
	HWND					wnd;					//�E�B���h�E�n���h��
	Direct3D9*				d3d;					//DirectX9�N���X�E�f�o�C�X
	Input*					input;					//Input�N���X
	//AbstractScene*			scene;					//���ۃV�[���N���X
	//TextureLoader*			textureLoader;			//�e�N�X�`���Ǎ��N���X
	//StaticMeshLoader*		staticMeshLoader;		//�X�^�e�B�b�N���b�V���Ǎ��N���X
	//ShaderLoader*			shaderLoader;			//�V�F�[�_�[�Ǎ��N���X
	//SoundInterface*			soundInterface;			//�T�E���h�̃C���^�[�t�F�[�X�N���X
	//TextManager*			textManager;			//�e�L�X�g�f�[�^�Ǎ��N���X
	//Fader*					fader;					//�t�F�[�_�[(�C���E�A�E�g)�N���X
	//EffekseerManager*		effekseerManager[3];	//�G�t�F�N�V�A�[�}�l�[�W���[
	//GameMaster*				gameMaster;				//�Q�[���^�c�N���X
	//SerialCommunication*	serialCommunication;	//�V���A���ʐM�N���X
	//AnimationLoader*		animationLoader;		//�A�j���[�V�����Ǎ��N���X
	std::string*			currentSceneName;		//���݂̃V�[���̖��O
	int						fpsMode;				//�t���[�����[�g��ԕϐ�
	int						fixedFps;				//�Œ�t���[�����[�g�l
	LARGE_INTEGER			timeStart;				// �p�t�H�[�}���X�J�E���^�[�̊J�n�l
	LARGE_INTEGER			timeEnd;				// �p�t�H�[�}���X�J�E���^�[�̏I���l
	LARGE_INTEGER			timerFreq;				// �p�t�H�[�}���X�J�E���^�[�̎��g��
	float					frameTime;				//�t���[������
	float					sleepRenderTime;		//�`��ҋ@����
	bool					hiddenCursor;			//�J�[�\����\���t���O
	bool					lockCursor;				//�J�[�\���ʒu�Œ�t���O



	//Method
	Director();
	~Director();
	void recoverDevice();						//�f�o�C�X�̕���
	HRESULT initialize();						//������
	void run(HINSTANCE);						//�G���g���|�C���g�ɂ�����Ăяo���֐�
	void mainLoop();							//���b�Z�[�W���[�v�����[�v�����֐�
	void update();								//�X�V
	void createGUI();							//GUI�E�B���h�E�̍쐬
	void render();								//�`��
	void setFrameTime();						//frameTime�̐ݒ�
	void displayFPS();							//FPS�\��
	void fixFPS();								//�Œ�FPS�␳
	void changeNextScene();						//�V�[���̐؂�ւ�
};
//void threadA();
