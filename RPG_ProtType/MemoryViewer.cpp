//===================================================================================================================================
//�yMemoryViewer.cpp�z
// [�쐬��]HAL����GP12A332 11 ���� ��
// [�쐬��]2020/01/03
// [�X�V��]2020/01/03
//===================================================================================================================================

//===================================================================================================================================
//�y�C���N���[�h�z
//===================================================================================================================================
#include "MemoryViewer.h"

//===================================================================================================================================
//�y�g���[�X�֐��z
//===================================================================================================================================
void trace(const char* format, ...)
{
	char buff[1024];

	va_list argp;
	va_start(argp, format);
	::vsprintf_s(buff, format, argp);
	va_end(argp);

	//    ::printfDx( "%s", buff);
	::OutputDebugString(buff);
}

//===================================================================================================================================
//�y�R���X�g���N�^�z
//===================================================================================================================================
MemoryViewer::MemoryViewer()
{
	// CPU�R�A�����擾����
	SYSTEM_INFO sys_info;
	::GetSystemInfo(&sys_info);
	cpuNum = sys_info.dwNumberOfProcessors;
	trace("CPU�R�A��:%d\n", cpuNum);

	// ������������
	MEMORYSTATUSEX mstatus = { sizeof(MEMORYSTATUSEX) };
	//4G�o�C�g�ȏ�̕����������e�ʂ��擾����
	if (::GlobalMemoryStatusEx(&mstatus)) {
		physMemorys = mstatus.ullTotalPhys;
		trace("������������:%lld\n", physMemorys);
	}
	else {
		trace("�����������ʎ擾�Ɏ��s�I\n");
		isError = true;
		return;
	}

	// �n���h���̍쐬
	if (ERROR_SUCCESS != ::PdhOpenQuery(NULL, 0, &query)) {
		trace("PDH�n���h���̍쐬�Ɏ��s�I\n");
		query = nullptr;
		isError = true;
		return;
	}

	instanceName = getInstanceName(query);
	if (instanceName == "") {
		trace("�C���X�^���X���擾�Ɏ��s�I\n");
		isError = true;
		return;
	}

	// �J�E���^�[�p�X��o�^
	std::string cpu_counter_path = instanceName + "\\% Processor Time";
	if (ERROR_SUCCESS != ::PdhAddCounter(query, cpu_counter_path.c_str(),
		0, &cpuCounter)) {
		trace("PDH CPU�J�E���^�[�p�X�o�^�Ɏ��s�I\n");
		cpuCounter = nullptr;
		isError = true;
		return;
	}

	std::string mem_counter_path = instanceName + "\\Working Set - Private";
	if (ERROR_SUCCESS != ::PdhAddCounter(query, mem_counter_path.c_str(),
		0, &memoryCounter)) {
		trace("PDH �������[�J�E���^�[�p�X�o�^�Ɏ��s�I\n");
		memoryCounter = nullptr;
		isError = true;
		return;
	}

	update();
}

//===================================================================================================================================
//�y�f�X�g���N�^�z
//===================================================================================================================================
MemoryViewer::~MemoryViewer()
{
}

//===================================================================================================================================
//�y�X�V�z
//===================================================================================================================================
bool MemoryViewer::update()
{
	if (isError) return false;
	if (ERROR_SUCCESS != ::PdhCollectQueryData(query)) return false;

	PDH_FMT_COUNTERVALUE fmtvalue;
	::PdhGetFormattedCounterValue(cpuCounter, PDH_FMT_DOUBLE, NULL, &fmtvalue);
	cpuUsage = fmtvalue.doubleValue;

	::PdhGetFormattedCounterValue(memoryCounter, PDH_FMT_LONG, NULL, &fmtvalue);
	memoryUsage = fmtvalue.longValue;

	return true;
}

//===================================================================================================================================
//�y���v���Z�X�̃C���X�^���X���擾�z
//�C���X�^���X��
//�@�ʏ�̓v���Z�X���Ɠ��ꂾ���A���������グ��ƌ��ɔԍ������Ă����B
//�@��Fhoge hoge#1 hoge#2 hoge#3 ...��
//===================================================================================================================================
std::string MemoryViewer::getInstanceName(PDH_HQUERY query)
{
	char module_path[_MAX_PATH + 1];
	if (!::GetModuleFileName(NULL, module_path, sizeof(module_path))) {
		return "";//error
	}

	// �p�X����t�@�C����(�g���q�Ȃ�)�𒊏o
	char process_name[_MAX_FNAME + 1];
	if (0 != _splitpath_s(module_path, NULL, 0, NULL, 0,
		process_name, sizeof(process_name), NULL, 0)) {
		return "";//error
	}

	trace("process_name:%s\n", process_name);

	const char* OBJECT_NAME = "Process";
	//�C���X�^���X���X�g���󂯎��o�b�t�@�̃T�C�Y�擾
	DWORD counter_list_length = 0;
	DWORD instance_list_length = 0;
	if (PDH_MORE_DATA != ::PdhEnumObjectItems(NULL, NULL, OBJECT_NAME,
		NULL, &counter_list_length,
		NULL, &instance_list_length,
		PERF_DETAIL_WIZARD, 0)) {
		return "";//error
	}

	//�C���X�^���X���X�g���󂯎��
	std::vector<char> counter_list(counter_list_length);//�o�b�t�@�̊m��
	std::vector<char> instance_list(instance_list_length);//�o�b�t�@�̊m��
	PDH_STATUS sts = ::PdhEnumObjectItems(NULL, NULL, OBJECT_NAME,
		counter_list.data(), &counter_list_length,
		instance_list.data(), &instance_list_length,
		PERF_DETAIL_WIZARD, 0);
	if (sts != ERROR_SUCCESS) {
		return "";//error
	}

	// �v���Z�XID���L�[�Ƃ��āA�J�����g�C���X�^���X����T��
	LONG process_id = ::GetCurrentProcessId();

	//trace("instance_list_length:%d\n", instance_list_length);
		// �C���X�^���X���X�g����C���X�^���X�������o��
		//"�C���X�^���X��\0�C���X�^���X��\0�C���X�^���X��\0\0"�̍\���ɂȂ��Ă�

	int cnt = 0;//�����v���Z�X��
	int i = 0;
	while (instance_list[i])
	{
		//trace("%04d: %s\n", i, &instance_list[i]);
		if (0 == std::strcmp(&instance_list[i], process_name)) { //�����H
			//�C���X�^���X����
			std::string instance_name = std::string("\\Process(") + process_name;
			if (cnt > 0) {
				instance_name += std::string("#") + std::to_string(cnt);
			}
			instance_name += std::string(")");
			if (process_id == getProcessID(query, instance_name)) {
				trace("pid: %d instance_name:[%s]\n", process_id, instance_name.c_str());
				return instance_name;
			}
			++cnt;
		}
		i += std::strlen(&instance_list[i]) + 1;
	}

	return "";
}

//===================================================================================================================================
//�y���v���Z�X���̎擾�z
//�v���Z�X�� = .exe����菜������
//�@�����v���Z�X����ꍇ�ł����ꖼ�́APID�͕ʂɂȂ�B
//�@��Fhoge.exe �� hoge
//===================================================================================================================================
LONG MemoryViewer::getProcessID(PDH_HQUERY query, const std::string& instance_name)
{

	if (isError) return -1;

	std::string counter_path = instance_name + "\\ID Process";
	PDH_HCOUNTER counter;

	if (ERROR_SUCCESS == ::PdhAddCounter(query, counter_path.c_str(), 0, &counter)) {
		if (ERROR_SUCCESS == ::PdhCollectQueryData(query)) {
			PDH_FMT_COUNTERVALUE fmtvalue;
			::PdhGetFormattedCounterValue(counter, PDH_FMT_LONG, NULL, &fmtvalue);
			::PdhRemoveCounter(counter);
			return fmtvalue.longValue;
		}
		::PdhRemoveCounter(counter);
	}
	return -1;
}
