#pragma once

#include <string>

class Config
{
public:
	/* ��ȡ����ʵ�� */
	static Config * get_instance() ;
	std::string get_ws_url() ;
	std::string get_access_token() ;
private:
	Config();
	~Config();
	std::string ws_url = "ws://localhost:6700";
	std::string access_token = "";
};

