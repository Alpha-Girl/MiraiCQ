#include "MiraiHttpEventDeal.h"
#include "../../tool/StrTool.h"
#include "../../log/MiraiLog.h"

#include <list>
#include <string>

using namespace std;

MiraiHttpEventDeal::MiraiHttpEventDeal()
{
}

MiraiHttpEventDeal::~MiraiHttpEventDeal()
{
}
/*
	text -> Plain
	face -> Face
	image -> Image��FlashImage
	record -> Voice (MiraiCQ�ݲ�֧��)
	video -> ??? (MiraiCQ��mha����֧��)
	at -> At��AtAll
	rps -> ??? (MiraiCQ��mha����֧��)
	dice -> Dice
	shake -> ??? (MiraiCQ��mha����֧��)
	poke -> Poke
	anonymous -> ??? (MiraiCQ��mha����֧��)
	share -> ??? (MiraiCQ��mha����֧��)
	contact ->??? (MiraiCQ��mha����֧��)
	location -> ??? (MiraiCQ��mha����֧��)
	music -> MusicShare (��֧���Զ������ַ���)
	reply -> (MiraiCQ��mha����֧��)
	forward -> ForwardMessage (MiraiCQ�ݲ�֧��)
	xml -> Xml
	json -> Json
*/
static Json::Value deal_mha_msg(const Json::Value& chain)
{
	Json::Value ret_arr = Json::arrayValue;
	if (!chain.isArray())
	{
		return ret_arr;
	}
	for (size_t i = 0; i < chain.size(); i++)
	{
		string type = chain[i]["type"].asString();
		if (type == "Plain")
		{
			Json::Value node;
			node["type"] = "text";
			node["data"]["text"] = chain[i]["text"].asString();
			ret_arr.append(node);
		}
		else if (type == "Face")
		{
			Json::Value node;
			node["type"] = "face";
			node["data"]["id"] = to_string(chain[i]["faceId"].asInt());
			ret_arr.append(node);
		}
		else if (type == "Image")
		{
			Json::Value node;
			node["type"] = "image";
			/* MiraiCQ�е�ͼƬֻ��Ҫurl��������(���Ҵ�url����Ϊtxqq��ur) */
			node["data"]["url"] = chain[i]["url"].asString();
			node["data"]["file"] = chain[i]["imageId"].asString();
			ret_arr.append(node);
		}
		else if (type == "FlashImage")
		{
			Json::Value node;
			node["type"] = "image";
			/* MiraiCQ�е�ͼƬֻ��Ҫurl��������(���Ҵ�url����Ϊtxqq��ur) */
			node["data"]["url"] = chain[i]["url"].asString();
			node["data"]["type"] = "flash";
			node["data"]["file"] = chain[i]["imageId"].asString();
			ret_arr.append(node);
		}
		else if (type == "At")
		{
			Json::Value node;
			node["type"] = "at";
			node["data"]["qq"] = to_string(chain[i]["target"].asInt64());
			ret_arr.append(node);
		}
		else if (type == "AtAll")
		{
			Json::Value node;
			node["type"] = "at";
			node["data"]["qq"] = "all";
			ret_arr.append(node);
		}
		else if (type == "Dice")
		{
			Json::Value node;
			node["type"] = "dice";
			node["data"] = Json::objectValue;
			ret_arr.append(node);
		}
		else if (type == "Poke")
		{
			Json::Value node;
			node["type"] = "poke";
			string name = chain[i]["name"].asString();
			if (name == "Poke")
			{
				node["data"]["type"] = 1;
				node["data"]["id"] = -1;
			}
			else if (name == "ShowLove")
			{
				node["data"]["type"] = 2;
				node["data"]["id"] = -1;
			}
			else if (name == "ShowLove")
			{
				node["data"]["type"] = 3;
				node["data"]["id"] = -1;
			}
			else if (name == "Heartbroken")
			{
				node["data"]["type"] = 4;
				node["data"]["id"] = -1;
			}
			else if (name == "SixSixSix")
			{
				node["data"]["type"] = 5;
				node["data"]["id"] = -1;
			}
			else if (name == "FangDaZhao")
			{
				node["data"]["type"] = 6;
				node["data"]["id"] = -1;
			}
			else
			{
				/* ���ڲ�֧�ֵ����ͣ�������ͨ��һ������ */
				node["data"]["type"] = 1;
				node["data"]["id"] = -1;
			}
			ret_arr.append(node);
		}
		else if (type == "MusicShare")
		{
			Json::Value node;
			node["type"] = "music";
			node["data"]["type"] = "custom";
			node["data"]["url"] = chain[i]["jumpUrl"].asString();
			node["data"]["audio"] = chain[i]["musicUrl"].asString();
			node["data"]["title"] = chain[i]["title"].asString();
			node["data"]["content"] = chain[i]["brief"].asString();
			node["data"]["image"] = chain[i]["pictureUrl"].asString();
			ret_arr.append(node);
		}
		else if (type == "Xml")
		{
			Json::Value node;
			node["type"] = "xml";
			node["data"]["data"] = chain[i]["xml"].asString();
			ret_arr.append(node);
		}
		else if (type == "Json")
		{
			Json::Value node;
			node["type"] = "json";
			node["data"]["data"] = chain[i]["json"].asString();
			ret_arr.append(node);
		}
		else
		{
			MiraiLog::get_instance()->add_debug_log("MiraiHttp", "������δ֪��Ϣ����: " + type);
		}
	}
	return ret_arr;
}


static MiraiNet::NetStruct deal_group_message(const MiraiNet::NetStruct & root)
{
	auto ret_json = MiraiNet::NetStruct(new Json::Value());
	auto & chain = (*root)["data"]["messageChain"];
	auto& sender = (*root)["data"]["sender"];

	(*ret_json)["time"] = chain[0]["time"].asInt64();
	//(*ret_json)["self_id"] = 0; /* ��mha���޷��õ�self_id
	(*ret_json)["post_type"] = "message";
	(*ret_json)["message_type"] = "group";
	if (sender["id"].asInt64() == 80000000)
	{
		/* ˵����������Ϣ */
		(*ret_json)["sub_type"] = "anonymous";
	}else
	{
		(*ret_json)["sub_type"] = "normal";
		/* mha��֧��onebot�е�`ϵͳ��ʾ���硸����Ա�ѽ�ֹȺ���������졹���� notice`*/
		/* ��Q���Ҳ�ò���*/
	}
	(*ret_json)["message_id"] = chain[0]["id"].asInt();
	(*ret_json)["group_id"] = sender["group"]["id"].asInt64();
	(*ret_json)["user_id"] = sender["id"].asInt64();
	if ((*ret_json)["sub_type"].asString() == "anonymous")
	{
		/* ������Ϣ */
		Json::Value anonymous;
		anonymous["id"] = 80000000;
		anonymous["name"] = sender["memberName"].asString();
		anonymous["flag"] = ""; /* mha�������û����ܵõ�flag��Ҳ����˵�����ܱ����� */
		(*ret_json)["anonymous"] = anonymous;
	}
	/* ��mha��chain���cq��array */
	(*ret_json)["message"] = deal_mha_msg(chain);
	(*ret_json)["raw_message"] = StrTool::jsonarr_to_cq_str((*ret_json)["message"]);
	/* mha��û������ */
	(*ret_json)["font"] = 0;
	(*ret_json)["sender"]["user_id"] = sender["id"].asInt64();
	/* mha��û���ǳƣ�����ʹ��Ⱥ��Ƭ���� */
	(*ret_json)["sender"]["nickname"] = sender["memberName"].asString();
	/* mhaû���Ա����� */
	(*ret_json)["sender"]["sex"] = "unknown";
	(*ret_json)["sender"]["age"] = 0;
	return ret_json;
}


static MiraiNet::NetStruct deal_private_message(const MiraiNet::NetStruct& root)
{
	auto ret_json = MiraiNet::NetStruct(new Json::Value());
	auto& chain = (*root)["data"]["messageChain"];
	auto& sender = (*root)["data"]["sender"];

	(*ret_json)["time"] = chain[0]["time"].asInt64();
	//(*ret_json)["self_id"] = 0; /* ��mha���޷��õ�self_id
	(*ret_json)["post_type"] = "message";
	(*ret_json)["message_type"] = "private";
	if ((*root)["data"]["type"].asString() == "FriendMessage")
	{
		(*ret_json)["sub_type"] = "friend";
	}
	else if ((*root)["data"]["type"].asString() == "TempMessage")
	{
		(*ret_json)["sub_type"] = "group";
	}
	else
	{
		/* ������������� */
	}
	(*ret_json)["message_id"] = chain[0]["id"].asInt();
	(*ret_json)["user_id"] = sender["id"].asInt64();
	
	/* ��mha��chain���cq��array */
	(*ret_json)["message"] = deal_mha_msg(chain);
	(*ret_json)["raw_message"] = StrTool::jsonarr_to_cq_str((*ret_json)["message"]);
	/* mha��û������ */
	(*ret_json)["font"] = 0;
	(*ret_json)["sender"]["user_id"] = sender["id"].asInt64();
	/* mha��û���ǳƣ�����ʹ��Ⱥ��Ƭ���� */
	if ((*ret_json)["sub_type"].asString() == "friend")
	{
		(*ret_json)["sender"]["nickname"] = sender["nickname"].asString();
	}
	else if((*ret_json)["sub_type"].asString() == "group")
	{
		(*ret_json)["sender"]["nickname"] = sender["memberName"].asString();
	}
	
	/* mhaû���Ա����� */
	(*ret_json)["sender"]["sex"] = "unknown";
	(*ret_json)["sender"]["age"] = 0;
	return ret_json;
}


MiraiNet::NetStruct MiraiHttpEventDeal::deal_event(const Json::Value & root_,std::mutex & mx_msg_id_vec, std::list<std::pair<int, int>> & msg_id_vec, int& curr_msg_id)
{
	auto root = MiraiNet::NetStruct(new Json::Value(root_));
	MiraiNet::NetStruct ret_json;
	string type = (*root)["data"]["type"].asString();
	if (type == "GroupMessage")
	{
		ret_json = deal_group_message(root);
	}
	else if (type == "FriendMessage" || type == "TempMessage")
	{
		ret_json = deal_private_message(root);
	}
	return ret_json;
}
