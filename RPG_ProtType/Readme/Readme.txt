//===================================================================================================================================
//�yReadme.txt�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/09/17
// [�X�V��]2019/09/20
//===================================================================================================================================

����������������������������������������������������������������������������������������������
���@[�����Ӂ�]																				��
���@��{�I�ɂ́A�e�V�[�����ɂ��ꂼ��̏������L�q���Ă��炢�܂��B							��
���@Direcotr�N���X��A�G���g���|�C���g�ȂǂɕύX�����������ꍇ�͕K���m�F������Ă��������B	��
���@�v���O�����̑�܂��ȗ���͉��L��[�v���O�����\��]���Q�Ƃ��Ă��������B					��
����������������������������������������������������������������������������������������������

[�����Ӂ�]
����TestProject�́A�Q�[���^�C�g�������肳���܂ł̈ꎞ�I�ȃv���W�F�N�g�ł��B
�Q�[���^�C�g�������肳�ꎟ��A�v���W�F�N�g�̍č쐬���s���܂��B
����́A�v���W�F�N�g�����쐬�������s�t�@�C���̖��O�ƂȂ邽�߂ł��B

[���C���[����]
Constant Layer �E�E�E�Q�[���ŗL�łȂ���{�I�ȃ��W���[���i�G���g���|�C���g��E�B���h�E�ADirectX9�f�o�C�X�A���͏����Ȃǁj

Game Layer �E�E�E�E�E�Q�[���ŗL�̃��W���[���i�v���C���[��A�ŗL�̃V�[���A�G�t�F�N�g��t�B�[���h�Ȃǁj

Loader Layer �E�E�E�E�e��f�[�^���\�[�X��ǂݍ��ރ��W���[���i�e�N�X�`�����[�_�[��A�V�F�[�_�[���[�_�[�Ȃǁj

Readme �E�E�E�E�E�E�E�R�[�f�B���O�K��Ȃǎ��O�ɔc�����ė~�����h�L�������g�Ȃ�

Resorce Layer�E�E�E�E�e�N�X�`����o�̓t�@�C���A�R�c���f���f�[�^�A�T�E���h�f�[�^�Ȃǂ̊e��f�[�^


[�v���O�����\��]

	WINAPI WinMain	//[Entry.cpp]�G���g���|�C���g�F�v���O�����̊J�n�ʒu
		|
		|-director->Director::run()
		|				|-Director::initialize()
		|					|-scene->initialize()
		|				|-Director::mainLoop()
		|					|-Director::changeNextScene()
		|					|			|-scene->uninitialize()
		|					|			|-SAFE_DELETE(scene)
		|					|			|-scene = new AbstractScene()
		|					|
		|					|-Director::update()
		|					|			|-scene->AbstractScene::update()
		|					|			|-scene->AbstractScene::collision()
		|					|			|-scene->AbstractScene::AI()
		|					|			|-scene->AbstractScene::createGUI()
		|					|
		|					|-Director::render()
		|					|			|-scene->AbstractScene::render()
		|
		|-delete director::~Director()
							|-SAFE_DELETE(scene)

[�e�V�[���ɂ���]
	�e�V�[���́A���ۃC���^�[�t�F�[�X�ł���AbstractScene�N���X���p�����Ă��܂��B
	�V�[���̃|�C���^�́ADirector�N���X�̃����o�ϐ��ɂ���܂��B
	Director�N���X���ȉ��̏����̗�����`���Ă��܂��B
		���R���X�g���N�^[AbstractScene::initialize]		
			[���l:�f�o�C�X��A���́A���\�[�X�Ǎ��N���X�Ȃǂ̃|�C���^���擾]

		��������[AbstractScene::initialize]		
			[���l:�V�[���̐������A��x�����Ăяo����܂��B]

		���I������[AbstractScene::uninitialize]	
			[���l:�V�[���̍폜���A��x�����Ăяo����܂��B]

		���X�V[AbstractScene::update]			
			[���l:���t���[���Ăяo����܂��BframeTime�������Ƃ��A�t���[�����ł͂Ȃ����ԓ�����̏������\�ł��B]

		���`��[AbstractScene::render]			
			[���l:���t���[���Ăяo����܂��B�e�V�[���ɂ���ĉ�ʕ����E3D�`��E2D�`��(UI)�Ȃǂ̏����̕��ނ�
				�@Direct3D9�N���X�̊֐���f�o�C�X�y��Camera�N���X��SetTransform���Ăяo���āA��`����K�v������܂��B]

		���Փˏ���[AbstractScene::collision]		
			[���l:���t���[���Ăяo����܂��B�e�V�[���̃I�u�W�F�N�g�̏Փˏ������L�q���܂��B]

		���`�h����[AbstractScene::AI]				
			[���l:���t���[���Ăяo����܂��B�K�v�ɉ����Ċ��p���Ă��������B]

		���f�o�b�O�pGUI����[AbstractScene::createGUI]
			[���l:���t���[���Ăяo����܂��B�����ŁA�f�o�b�O�p�E�B���h�E���쐬���Ă��������B
				�@Director�ɂ�����beginGUI()��endGUI()���쐬����Ă��܂��̂ŁA�K�w�\���ɂ��쐬���]�܂����ł��B
				�@�戵���o�����󂢂̂Ŏ��s���뒆�ł��B��Ă�����΂��C�y�ɂ���������������(�E�ցE)]

	�V�[���́A�ėp�I�ȉ��L�̃N���X�̃|�C���^���R���X�g���N�^�ɂ��擾���Ă��܂��B
	��LPDIRECT3DDEVICE9 device				�FDirectX9�̕`��⃍�[�h�Ȃǂ��s���f�o�C�X
	��Direct3D9* direct3D9					�FDirectX9�̃f�o�C�X��A�p�����[�^���Ǘ�����N���X�BchangeViewport�n�֐��ɂ��`��͈͂�ύX�ł���B
	��Input* input							�F���̓N���X�B�L�[�{�[�h�E�}�E�X�E�R���g���[�����Ǘ��B���\�b�h�ɂ��e���͏�Ԃ��擾�ł���B
	��TextureLoader* textureLoader			�F�e�N�X�`���Ǎ��N���X�B�A�v���S�̂Ŏg�p����S�e�N�X�`�����Ǘ��Bgetter�ɂ��|�C���^���擾�ł���B
	��StaticMeshLoader* staticMeshLoader	�F3D���f���Ǎ��N���X�B�A�v���S�̂Ŏg�p�����A�j���[�V�����̑S���f�����Ǘ��Bgetter�ɂ��|�C���^���擾�ł���B
	��ShaderLoader* shaderLoader			�F�V�F�[�_�[�Ǎ��N���X�B�A�v���S�̂Ŏg�p����S�V�F�[�_�[���Ǘ��Bgetter�ɂ��|�C���^���擾�ł���B
	��AnimationLoader* animationLoader		�F�A�j���[�V�������f���ǂݍ��݃N���X�B���ǒ��E�E�E
	��TextLoader* textLoader				�F�e�L�X�g���\�[�X�̓ǂݍ��݋y�э쐬���s���N���X�Bgetter�ɂ��|�C���^���擾�ł���B���ǒ��E�E�E
	��GameMaster* gameMaster				�F�V�[�����ׂ��f�[�^��ێ��E�Ǘ�����N���X�B���ǒ��E�E�E
	��Sound* sound							�F�T�E���h�v���O���}�ɂ��C�����܂��B
	��������������������������������������������������������������������������������������������������������������
	���@[���֎~������]																							��
	���@�Ǎ��N���X�Ȃǂ̔ėp�N���X���m�ۂ������\�[�X��f�o�C�X�Ȃǂ́A�������̃N���X���Ō㏈�����s���Ă��܂��B	��
	���@�ł��̂ŁAgetter�ȂǂŃ|�C���^���󂯎��A���p���邱�Ƃ͂n�j�ł����A									��
	���@delete��Release�Ȃǂ̏������󂯎���ōs��Ȃ��ł��������B												��
	��������������������������������������������������������������������������������������������������������������

[���̑��A�u���O�ɓ`�B/���L���������Ɓv��u�L�q���ė~�����v�]�v�Ȃǂ�����΁A���L�ɂ����R�ɋL�q���Ă�������(^��^)��]
���t��L�q�҂̎���������Ə�����܂�(�L-��-`)
���̃e�L�X�g�ɂ�����L�q���e�Ɍ�肪�����`�Ȃǂ̕񍐂ł��n�j�ł��B
�v���O�����̃o�O�񍐂́A�����ł͂Ȃ�LINE��ʕ����A���̑��̎�@�ł��A�N�e�B�u�ȏꏊ�ŋ��L/���N���܂��傤�`

�����O�ɓ`�B/���L����������

���L�q���ė~�����v�]

