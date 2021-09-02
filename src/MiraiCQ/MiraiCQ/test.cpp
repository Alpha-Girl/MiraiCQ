#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include "config/config.h"
#include "log/MiraiLog.h"
#include "tool/TimeTool.h"
#include "tool/InputTool.h"
#include "center/center.h"
#include "tool/PathTool.h"
#include <iostream>
#include <string>

std::atomic_bool printLog = true;
static thread_local std::string retStr;

int InitBot()  
{
	static auto  net = MiraiNet::get_instance("onebot");
	if (!net)
	{
		MiraiLog::get_instance()->add_debug_log("Net", "����ģ��ʵ����ʧ��");
		return -1;
	}
	net->set_config("ws_url", Config::get_instance()->get_ws_url());
	net->set_config("access_token", Config::get_instance()->get_access_token());
	if (!net->connect())
	{
		MiraiLog::get_instance()->add_debug_log("Net", "�������Ӵ���");
		return -1;
	}
	Center::get_instance()->set_net(net);
	std::thread([&]() {
		while (1)
		{
			TimeTool::sleep(5000);
			if (!net->is_connect())
			{
				printLog = true;
				MiraiLog::get_instance()->add_debug_log("Net", "���ӶϿ�,��������...");
				auto new_net = MiraiNet::get_instance(net->get_config("net_type"));
				if (!new_net)
				{
					MiraiLog::get_instance()->add_debug_log("Net", "����������ʧ��...");
					continue;
				}
				new_net->set_all_config(net->get_all_config());
				if (!new_net->connect())
				{
					MiraiLog::get_instance()->add_debug_log("Net", "��������ʧ�ܣ�5�������");
					continue;
				}
				net = new_net;
				Center::get_instance()->set_net(net);
				MiraiLog::get_instance()->add_debug_log("Net", "�������ӳɹ�");
			}
		}

	}).detach();
	if (Center::get_instance()->load_all_plus() < 0)
	{
		MiraiLog::get_instance()->add_debug_log("Center", "�������ʧ��");
		return -1;
	}
	if (Center::get_instance()->enable_all_plus() < 0)
	{
		MiraiLog::get_instance()->add_debug_log("Center", "�������ʧ��");
		return -1;
	}

	if (!Center::get_instance()->run())
	{
		MiraiLog::get_instance()->add_debug_log("Center", "Center����ʧ��");
		return -1;
	}
	return 0;
}

const char* GetAllAC(const char* gap)
{
	if (!gap)
	{
		return "";
	}
	auto center = Center::get_instance();
	auto ac_vec = center->get_ac_vec();
	if (ac_vec.size() == 0)
	{
		return "";
	}
	retStr.clear();
	for (size_t i = 0; i < ac_vec.size(); ++i)
	{
		if (i == 0)
		{
			retStr.append(std::to_string(ac_vec[i]));
		}
		else
		{
			retStr.append(gap + std::to_string(ac_vec[i]));
		}
	}
	return retStr.c_str();
}

const char* GetName(int ac)
{
	auto center = Center::get_instance();
	std::string err_msg;
	auto info = center->get_plus_by_ac(ac);
	if (!info)
	{
		return "";
	}
	retStr = info->name;
	return retStr.c_str();
}

const char* GetMenuName(int ac, int pos)
{
	auto center = Center::get_instance();
	auto name = center->get_menu_name_by_ac(ac, pos);
	retStr = name;
	return retStr.c_str();
}

void CallMenuFun(int ac, int pos)
{
	auto center = Center::get_instance();
	center->call_menu_fun_by_ac(ac, pos);
}

static std::vector<std::string> tokenize(const std::string& s, char c) {
	std::string::const_iterator end = s.end();
	std::string::const_iterator start = end;

	std::vector<std::string> v;
	for (std::string::const_iterator it = s.begin(); it != end; ++it) {
		if (*it != c) {
			if (start == end)
				start = it;
			continue;
		}
		if (start != end) {
			v.push_back(std::string(start, it));
			start = end;
		}
	}
	if (start != end)
		v.push_back(std::string(start, end));
	return v;
}

static void PrintUnkowCmd()
{
	printf("δ֪������\n");
	printf("ʹ��`ls`���鿴���в��\nʹ��`log`������log\n����`q`���԰�ȫ�˳�����\n>>>");
}

int main()
{	
	MiraiLog::get_instance()->add_backend_sinks([&](const MiraiLog::Level& lv, const std::string& category, const std::string& dat, void* user_ptr) {
		if (!printLog)
		{
			return;
		}
		static std::mutex mx;
		std::lock_guard<std::mutex> lock(mx);
		switch (lv)
		{
		case MiraiLog::Level::DEBUG:
			printf("[DEBUG][%s]:%s\n", category.c_str(), dat.c_str());
			break;
		case MiraiLog::Level::INFO:
			printf("[INFO][%s]:%s\n", category.c_str(), dat.c_str());
			break;
		case MiraiLog::Level::WARNING:
			printf("[WARNING][%s]:%s\n", category.c_str(), dat.c_str());
			break;
		case MiraiLog::Level::FATAL:
			printf("[FATAL][%s]:%s\n", category.c_str(), dat.c_str());
			break;
		default:
			break;
		}
	}, NULL);
	if (InitBot() != 0)
	{
		printf("����ʧ��\n1:���configĿ¼�µ������ļ�\n2:���appĿ¼�����޲��\n3:���CQP.dll�Ƿ����\n");
		while (true)
		{
			TimeTool::sleep(0);
		}
	}
	int last_ac = 1000;
	std::string name = "";
	/* ������ʱ���ڵȴ���ӡlifecycle����֤�Ӿ����� */
	TimeTool::sleep(1000);
	printf("ʹ��`ls`���鿴���в��\nʹ��`log`������log\n����`q`���԰�ȫ�˳�����\n>>>");
	/* printLog = !printLog; */
	while (true)
	{
		std::vector<std::string> LineVec = InputTool::get_line();
		if (LineVec.size() == 1 && LineVec[0] == "ls")
		{
			last_ac = 1000;
			std::string ac_str = GetAllAC("\n");
			auto ac_vec = tokenize(ac_str, '\n');
			printf("ʹ��`cd <����>`���鿴һ������Ĳ˵�:\n\n");
			for (auto i : ac_vec)
			{
				std::string name = GetName(atoi(i.c_str()));
				printf("%s	%s\n", i.c_str(), name.c_str());
			}
			printf("\n>>>");
		}
		else if (LineVec.size() == 2 && LineVec[0] == "cd")
		{
			int ac;
			try
			{
				ac = std::stoi(LineVec[1]);
			}
			catch (const std::exception&)
			{
				PrintUnkowCmd();
			}
			name = GetName(ac);
			last_ac = ac;
			printf("ʹ��`call <����>`�����ò��[%s]��һ���˵�:\n\n", name.c_str());
			for (int i = 0;; ++i)
			{
				std::string name = GetMenuName(ac, i);
				if (name != "")
				{
					printf("%d	%s\n", i, name.c_str());
				}
				else
				{
					break;
				}
			}
			printf("\n>>>");
		}
		else if (LineVec.size() == 2 && LineVec[0] == "call")
		{
			int n;
			try
			{
				n = std::stoi(LineVec[1]);
			}
			catch (const std::exception&)
			{
				PrintUnkowCmd();
			}
			CallMenuFun(last_ac, n);
			printf("\n>>>");
		}
		else if (LineVec.size() == 1 && LineVec[0] == "log")
		{
			printLog = !printLog;
			if (printLog)
				printf("log�Ѿ���,�ٴ�����`log`���ر�log\n>>>");
			else
				printf("log�Ѿ��ر�,�ٴ�����`log`������log\n>>>");
		}
		else if (LineVec.size() == 1 && LineVec[0] == "q")
		{
			printLog = true;
			auto center = Center::get_instance();
			center->del_all_plus();
			HANDLE hself = GetCurrentProcess();
			TerminateProcess(hself, 0);
		}
		else if (LineVec.size() != 0)
		{
			PrintUnkowCmd();
		}
	}

	return 0;
}