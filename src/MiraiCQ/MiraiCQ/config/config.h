#pragma once

#include <string>

class Config
{
public:
	/* ��ȡ����ʵ�� */
	static Config * get_instance() noexcept;
	std::string get_ws_url() noexcept;
	std::string get_access_token() noexcept;
private:
	Config();
	~Config();
	std::string ws_url = "ws://localhost:6700";
	std::string access_token = "";
};

