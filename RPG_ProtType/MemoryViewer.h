//===================================================================================================================================
//�yMemoryViewer.h�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2019/09/20
// [�X�V��]2019/09/20
//===================================================================================================================================
#pragma once

//===================================================================================================================================
//�y���C�u�����̃��[�h�z
//===================================================================================================================================
#pragma comment( lib, "pdh.lib" )

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "Base.h"
#include <string>
#include <pdh.h>
#include <pdhmsg.h>
#include <string>
#include <vector>

//===================================================================================================================================
//�y�������v���N���X�z
//���܂���CPU���v�����Ă��܂��B
//���x�����ł��B
//Visual Studio�Ȃ��̏ꍇ�ł������l�q���������x�̂��̂ƍl���Ă��������B
//�����I�ɂ́A�����x�ɂ������ł��B
//===================================================================================================================================
class MemoryViewer :public Base
{
private:
	bool            isError = false;
	std::string     instanceName;
	int				cpuNum;					// CPU�R�A��
	PDH_HQUERY      query = nullptr;
	PDH_HCOUNTER    cpuCounter = nullptr;
	PDH_HCOUNTER    memoryCounter = nullptr;
	double			cpuUsage = 0.0;			// CPU�g�p��
	LONG            memoryUsage = 0;		// �����������g�p��kb
	DWORDLONG       physMemorys = 0;		// ������������kb

public:
	MemoryViewer();
	~MemoryViewer();
	bool update();
	double getCpuUsege() { return (cpuUsage / cpuNum); }		//���v���Z�X�̎g�p����CPU�R�A��
	LONG   getMemoryUsege() { return memoryUsage / 1024; }		//kb
	DWORDLONG getPhysMemorys() { return physMemorys / 1024; }	//kb
	std::string getInstanceName(PDH_HQUERY query);
	LONG getProcessID(PDH_HQUERY query, const std::string& instance_name);
};
