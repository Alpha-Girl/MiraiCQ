// PicHP.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"

#include <string>

#include "jsoncpp/json.h"

static int sg_authCode = 0;

/* ����authCode */
extern "C" int __stdcall Initialize(int authCode)
{
	sg_authCode = authCode;
	return 0;
}

/* �˺��������ͷ�����SendWs���ص��ַ�����������Ĳ���ΪNULL,�����κζ��� */
typedef  void  (__stdcall * FreeType)(void *);
static FreeType Free = NULL;

/* 
   ����:
     �˺�������ֱ�ӵ���onebot�˵�api
   ����:
     retcode���ڽ��յ������
       0�����óɹ�
	   -1����������
	   -2��������󣬻��߳�ʱ
	   -3������ڲ�������鿴��־
     msgΪҪ���͵�json�ַ�������ʹ��gbk����
     timeoutΪ��ʱ����λ����
   ����:
     ����Ϊgbk�����json�ַ��������retcode��Ϊ0,�򷵻�NULL��
	 ���ص��ַ���[����]ʹ�������Free�ͷ�

*/
typedef  char * ( __stdcall * SendWsType)(int ac,const char * msg,int * retcode,unsigned int timeout);
static SendWsType SendWs = NULL;

/*
	����:
	  �˺������ڻ�ȡ���Ŀ¼��ַ
	���أ�
	  ����Ϊgbk������ַ���ĩβ��'\'���������ʧ�ܣ���NULL
	  ���ص��ַ���[����]ʹ�������Free�ͷ�
*/
typedef  char * ( __stdcall * GetAppDirectoryType)(int ac);
static GetAppDirectoryType GetAppDirectory = NULL;

/*
	����:
	  ��ӡ��־
    ����:
     log_levelָ���ȼ�
       0��debug
	   1��info
     categoryΪ��־���࣬Ӧ��Ϊgbk����
     log_msg���ݣ�Ӧ��ΪGBK����
	���أ�
	  0���ɹ�
	  -1��auth_code����
	  -2��log_level����
	  -3���ڲ�����
*/
typedef int ( __stdcall * AddLogType)(int auth_code, int log_level, const char *category, const char *log_msg);
static AddLogType AddLog = NULL; 

/* ���¼����ڻ�ȡ������fΪ����ָ�����飬nΪ�����С(Ŀǰ��Ϊ2) */
extern "C" int __stdcall Initialize2(void ** f,int n)
{
	if(n == 4)
	{
		Free = (FreeType)f[0];
		SendWs = (SendWsType)f[1];
		GetAppDirectory = (GetAppDirectoryType)f[2];
		AddLog = (AddLogType)f[3];
		
	}
	return 0;
	
}

class SBotCore
{
public:
	static void add_info_log(const std::string & category, const std::string &  log_msg)
	{
		AddLog(sg_authCode,1,category.c_str(),log_msg.c_str());
	}
	static void add_debug_log(const std::string & category, const std::string &  log_msg)
	{
		AddLog(sg_authCode,0,category.c_str(),log_msg.c_str());
	}
	static std::string get_app_dir()
	{
		char * ret = GetAppDirectory(sg_authCode);
		std::string retstr;
		if(ret)
		{
			retstr = ret;
		}
		Free(ret);
		return ret;
	}
	static std::string send_ws(const std::string & js_str,unsigned int timeout = 10000)
	{
		int retcode = 0;
		char * ret = SendWs(sg_authCode,js_str.c_str(),&retcode,timeout);
		std::string retstr;
		if(ret)
		{
			retstr = ret;
		}
		Free(ret);
		return retstr;
	}
	
};

struct SBotEventBase
{
	struct PostType {enum T{MESSAGE,NOTICE,REQUEST,META_EVENT};};
	SBotEventBase(){}
	int copy_init(const SBotEventBase & e)
	{
		this->post_type = e.post_type;
		this->self_id = e.self_id;
		this->_time = e._time;
		return 0;
	}
	long long int _time;
    long long int self_id;
	PostType::T post_type;
};

struct SbotEventMessageBase:public SBotEventBase
{
	struct MessageType {enum T{PRIVATR,GROUP};};
	SbotEventMessageBase(){}
	int copy_init_pre(const SBotEventBase & e)
	{
		SBotEventBase::copy_init(e);
		return 0;
	}
	int copy_init(const SbotEventMessageBase & e)
	{
		copy_init_pre(e);
		this->message_type = e.message_type;
		return 0;
	}
	MessageType::T message_type;
};

struct SbotEventMessagePrivate:public SbotEventMessageBase
{
	struct SubType {enum T{FRIEND,GROUP,OTHER};};
	struct Sender
	{
		struct SexType {enum T{MALE,FEMALE,UNKNOWN};};
		long long user_id;
		std::string nickname;
		SexType::T sex;
		int age;
	};
	SbotEventMessagePrivate(){}
	int copy_init_pre(const SbotEventMessageBase & e)
	{
		SbotEventMessageBase::copy_init(e);
		return 0;
	}
	int copy_init(const SbotEventMessagePrivate & e)
	{
		copy_init_pre(e);
		sub_type = e.sub_type;
		message_id = e.message_id;
		user_id = e.user_id;
		message = e.message;
		raw_message = e.raw_message;
		font = e.font;
		sender = e.sender;
		return 0;
	}
	SubType::T sub_type;
    int message_id;
	long long user_id;
	std::string message;
	std::string raw_message;
	int font;
	Sender sender;
};

struct SbotEventMessageGroup:public SbotEventMessageBase
{
	struct SubType {enum T{NORMAL,ANONYMOUS,NOTICE};};
	struct Anonymous
	{
		long long id;
		std::string name;
		std::string flag;
	};
	struct Sender
	{
		struct SexType {enum T{MALE,FEMALE,UNKNOWN};};
		struct RoleType {enum T{OWNER,ADMIN,MEMBER};};
		long long user_id;
		std::string nickname;
		std::string card;
		SexType::T sex;
		int age;
		std::string area;
		std::string level;
		RoleType::T role;
		std::string title;
	};
	int copy_init_pre(const SbotEventMessageBase & e)
	{
		SbotEventMessageBase::copy_init(e);
		return 0;
	}
	int copy_init(const SbotEventMessageGroup & e)
	{
		copy_init_pre(e);
		sub_type = e.sub_type;
		message_id = e.message_id;
		group_id = e.group_id;
		user_id = e.user_id;
		anonymous = e.anonymous;
		message = e.message;
		raw_message = e.raw_message;
		font = e.font;
		sender = e.sender;
		return 0;
	}
	SubType::T sub_type;
    int message_id;
	long long int group_id;
	long long user_id;
	Anonymous anonymous;
	std::string message;
	std::string raw_message;
	int font;
	Sender sender;
};

static int user_event_message_private(const Json::Value & raw_json,const SbotEventMessagePrivate & base)
{
	Json::Value root;
	root["action"] = "send_private_msg";
	Json::Value params;
	params["user_id"] = base.user_id;
	params["message"] = base.message;
	root["params"] = params;
	SBotCore::send_ws(Json::FastWriter().write(root));
	return 0;
}

static int deal_event_message_private(const Json::Value & root,const SbotEventMessageBase & base)
{
	Json::Value defstr = "";
	Json::Value defint = 0;
	SbotEventMessagePrivate bot_event_base;
	bot_event_base.copy_init_pre(base);

	std::string sub_type = root.get("sub_type",defstr).asString();
	if(sub_type == "friend")
	{
		bot_event_base.sub_type = SbotEventMessagePrivate::SubType::FRIEND;
	}
	else if(sub_type == "group")
	{
		bot_event_base.sub_type = SbotEventMessagePrivate::SubType::GROUP;
	}
	else if(sub_type == "other")
	{
		bot_event_base.sub_type = SbotEventMessagePrivate::SubType::OTHER;
	}

	bot_event_base.message_id = root.get("message_id",defint).asInt();

	bot_event_base.user_id = root.get("user_id",defint).asInt64();

	bot_event_base.message = root.get("message",defstr).asString();

	bot_event_base.raw_message = root.get("raw_message",defstr).asString();

	bot_event_base.font = root.get("font",defint).asInt();

	Json::Value js_sender = root.get("sender",Json::Value());
	bot_event_base.sender.user_id = js_sender.get("user_id",defint).asInt64();
	bot_event_base.sender.nickname = js_sender.get("nickname",defstr).asString();
	std::string sexstr = js_sender.get("sex",defstr).asString();
	if(sexstr == "male")
	{
		bot_event_base.sender.sex = SbotEventMessagePrivate::Sender::SexType::MALE;
	}
	else if(sexstr == "female")
	{
		bot_event_base.sender.sex = SbotEventMessagePrivate::Sender::SexType::FEMALE;
	}
	else if(sexstr == "unknown")
	{
		bot_event_base.sender.sex = SbotEventMessagePrivate::Sender::SexType::UNKNOWN;
	}
	bot_event_base.sender.age = js_sender.get("age",defint).asInt();
	
	user_event_message_private(root,bot_event_base);
	
	return 0;
}
static int deal_event_message_group(const Json::Value & root,const SbotEventMessageBase & base)
{
	return 0;
}

static int deal_event_message(const Json::Value & root,const SBotEventBase & base)
{
	Json::Value defstr = "";
	std::string message_type = root.get("message_type",defstr).asString();
	SbotEventMessageBase bot_event_base;
	bot_event_base.copy_init_pre(base);
	if(message_type == "private")
	{
		bot_event_base.message_type = SbotEventMessageBase::MessageType::PRIVATR;
		deal_event_message_private(root,bot_event_base);
	}
	else if(message_type == "group")
	{
		bot_event_base.message_type = SbotEventMessageBase::MessageType::GROUP;
		deal_event_message_group(root,bot_event_base);
	}
	return 0;
}

static int deal_eventjson(const Json::Value & root)
{
	Json::Value defstr = "";
	Json::Value defint = 0;
	std::string post_type = root.get("post_type",defstr).asString();
	SBotEventBase bot_event_base;
	bot_event_base._time = root.get("time",defint).asInt64();
	bot_event_base.self_id = root.get("self_id",defint).asInt64();
	if(post_type == "message")
	{
		bot_event_base.post_type = SBotEventBase::PostType::MESSAGE;
		deal_event_message(root,bot_event_base);
	}
	return 0;
}

/* ��������ws�·����¼���msgΪgbk�����json�ַ��� type = 1207 */
extern "C" int __stdcall event_all(const char * jsonmsg)
{

	Json::Value root;
	Json::Reader reader;
	if(!reader.parse(jsonmsg, root))
	{
		return 0;
	}
	try
	{
		deal_eventjson(root);
	}catch(std::exception & e)
	{
		SBotCore::add_info_log("error",e.what());
	}

	return 0;
}



/* ��������¼� type = 1001 */
extern "C" int __stdcall event_coolq_start()
{
	return 0;
}

/* ��������¼� type = 1003 */
extern "C" int __stdcall event_enable()
{
	return 0;
}


/* ���ͣ���¼� type = 1004 �������� */
extern "C" int __stdcall event_disable()
{
	return 0;
}

/* ����˳��¼� type = 1002 */
extern "C" int __stdcall event_coolq_exit()
{
	return 0;
}

/* menu-�������¼� */
extern "C" int __stdcall menu_check_update()
{
	MessageBoxA(NULL,"�����°�ť�����","INFO",MB_OK);
	return 0;
}






