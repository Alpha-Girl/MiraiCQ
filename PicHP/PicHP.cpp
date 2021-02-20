// PicHP.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"

#pragma comment(lib, "CQP.lib")

static __int32 sg_authCode = 0;


//API��ʵ�ֿ��Բο� https://github.com/super1207/MiraiCQ/blob/main/src/MiraiQQ/MiraiQ/api_list.cpp

#define cq_bool_t __int32

extern "C" __int32 __stdcall CQ_sendPrivateMsg(__int32 auth_code, __int64 qq, const char *msg);
extern "C" __int32 __stdcall CQ_sendGroupMsg(__int32 auth_code, __int64 group_id, const char *msg);
extern "C" __int32 __stdcall CQ_sendDiscussMsg(__int32 auth_code, __int64 discuss_id, const char *msg);  //δʵ��
extern "C" __int32 __stdcall CQ_deleteMsg(__int32 auth_code, __int64 msg_id);

extern "C" __int32 __stdcall CQ_sendLike(__int32 auth_code, __int64 qq);  //δʵ��
extern "C" __int32 __stdcall CQ_sendLikeV2(__int32 auth_code, __int64 qq, __int32 times);  //δʵ��

extern "C" __int32 __stdcall CQ_setGroupKick(__int32 auth_code, __int64 group_id, __int64 qq, cq_bool_t reject_add_request);
extern "C" __int32 __stdcall CQ_setGroupBan(__int32 auth_code, __int64 group_id, __int64 qq, __int64 duration);
extern "C" __int32 __stdcall CQ_setGroupAnonymousBan(__int32 auth_code, __int64 group_id, const char *anonymous, __int64 duration);
extern "C" __int32 __stdcall CQ_setGroupWholeBan(__int32 auth_code, __int64 group_id, cq_bool_t enable);
extern "C" __int32 __stdcall CQ_setGroupAdmin(__int32 auth_code, __int64 group_id, __int64 qq, cq_bool_t set);
extern "C" __int32 __stdcall CQ_setGroupAnonymous(__int32 auth_code, __int64 group_id, cq_bool_t enable);
extern "C" __int32 __stdcall CQ_setGroupCard(__int32 auth_code, __int64 group_id, __int64 qq, const char *new_card);
extern "C" __int32 __stdcall CQ_setGroupLeave(__int32 auth_code, __int64 group_id, cq_bool_t is_dismiss);
extern "C" __int32 __stdcall CQ_setGroupSpecialTitle(__int32 auth_code, __int64 group_id, __int64 qq, const char *new_special_title,__int64 duration);
extern "C" __int32 __stdcall CQ_setDiscussLeave(__int32 auth_code, __int64 discuss_id);  //δʵ��

extern "C" __int32 __stdcall CQ_setFriendAddRequest(__int32 auth_code, const char *response_flag, __int32 response_operation,const char *remark);
extern "C" __int32 __stdcall CQ_setGroupAddRequest(__int32 auth_code, const char *response_flag, __int32 request_type,__int32 response_operation);
extern "C" __int32 __stdcall CQ_setGroupAddRequestV2(__int32 auth_code, const char *response_flag, __int32 request_type,__int32 response_operation, const char *reason);

extern "C" __int64 __stdcall CQ_getLoginQQ(__int32 auth_code);
extern "C" const char * __stdcall CQ_getLoginNick(__int32 auth_code);
extern "C" const char * __stdcall CQ_getStrangerInfo(__int32 auth_code, __int64 qq, cq_bool_t no_cache);
extern "C" const char * __stdcall CQ_getFriendList(__int32 auth_code, cq_bool_t reserved);
extern "C" const char * __stdcall CQ_getGroupList(__int32 auth_code);
extern "C" const char * __stdcall CQ_getGroupInfo(__int32 auth_code, __int64 group_id, cq_bool_t no_cache);
extern "C" const char * __stdcall CQ_getGroupMemberList(__int32 auth_code, __int64 group_id);
extern "C" const char * __stdcall CQ_getGroupMemberInfoV2(__int32 auth_code, __int64 group_id, __int64 qq, cq_bool_t no_cache);

extern "C" const char * __stdcall CQ_getCookies(__int32 auth_code); //δʵ��
extern "C" const char * __stdcall CQ_getCookiesV2(__int32 auth_code, const char *domain); //δʵ��
extern "C" __int32 __stdcall CQ_getCsrfToken(__int32 auth_code); //δʵ��
extern "C" const char * __stdcall CQ_getAppDirectory(__int32 auth_code);
extern "C" const char * __stdcall CQ_getRecord(__int32 auth_code, const char *file, const char *out_format);
extern "C" const char * __stdcall CQ_getRecordV2(__int32 auth_code, const char *file, const char *out_format);
extern "C" const char * __stdcall CQ_getImage(__int32 auth_code, const char *file);
extern "C" __int32 __stdcall CQ_canSendImage(__int32 auth_code);
extern "C" __int32 __stdcall CQ_canSendRecord(__int32 auth_code);
extern "C" __int32 __stdcall CQ_addLog(__int32 auth_code, __int32 log_level, const char *category, const char *log_msg);
extern "C" __int32 __stdcall CQ_setFatal(__int32 auth_code, const char *error_info);
extern "C" __int32 __stdcall CQ_setRestart(__int32 auth_code);  //δʵ��


//event��ʵ�ֿ��Բο� https://github.com/super1207/MiraiCQ/blob/main/src/MiraiQQ/MiraiQ/bot_event.cpp

/* ����authCode */
extern "C" __int32 __stdcall Initialize(__int32 authCode)
{
	sg_authCode = authCode;
	return 0;
}

/* ��������¼� type = 1001 */
extern "C" __int32 __stdcall event_coolq_start()
{
	return 0;
}

/* ��������¼� type = 1003 */
extern "C" __int32 __stdcall event_enable()
{
	return 0;
}

/* ˽���¼� type = 21 */
extern "C" __int32 __stdcall event_private_message(__int32 sub_type, __int32 msg_id, __int64 from_qq, const char *msg, __int32 font)
{
	CQ_sendPrivateMsg(sg_authCode,from_qq,msg);
	return 0;
}

/* Ⱥ���¼� type = 2 from_anonymous_base64ʵ�ֲ����� */
extern "C" __int32 __stdcall event_group_message(__int32 sub_type, __int32 msg_id, __int64 from_group, __int64 from_qq, const char *from_anonymous_base64,const char *msg, __int32 font)
{
	return 0;
}

/* �������¼� type = 4 */
extern "C" __int32 __stdcall event_discuss_message(__int32 sub_type, __int32 msg_id, __int64 from_discuss, __int64 from_qq, const char *msg, __int32 font)
{
	return 0;
}

/* Ⱥ�ļ��ϴ��¼� type = 11 file_base64ʵ�ֲ�����*/
extern "C" __int32 __stdcall event_group_upload(__int32 sub_type, __int32 send_time, __int64 from_group, __int64 from_qq, const char *file_base64)
{
	return 0;
}

/* Ⱥ����Ա�䶯�¼� type = 101 */
extern "C" __int32 __stdcall event_group_admin(__int32 sub_type, __int32 send_time, __int64 from_group, __int64 being_operate_qq)
{
	return 0;
}

/* Ⱥ��Ա�����¼� type = 102 */
extern "C" __int32 __stdcall event_group_member_decrease(__int32 sub_type, __int32 send_time, __int64 from_group, __int64 from_qq, __int64 being_operate_qq)
{
	return 0;
}

/* Ⱥ��Ա�����¼� type = 103 */
extern "C" __int32 __stdcall event_group_member_increase(__int32 sub_type, __int32 send_time, __int64 from_group, __int64 from_qq, __int64 being_operate_qq)
{
	return 0;
}

/* Ⱥ�����¼� type = 104 */
extern "C" __int32 __stdcall event_group_ban(__int32 sub_type, __int32 send_time, __int64 from_group, __int64 from_qq, __int64 being_operate_qq, __int64 duration)
{
	return 0;
}

/* ��������¼� type = 201 */
extern "C" __int32 __stdcall event_friend_add(__int32 sub_type, __int32 send_time, __int64 from_qq)
{
	return 0;
}

/* (��չ)Ⱥ�ڴ�һ���¼�,user_idΪ������QQ type = 202 */
extern "C" __int32 __stdcall event_notify_pock(__int64 group_id, __int64 user_id, __int64 target_id)
{
	if(target_id == CQ_getLoginQQ(sg_authCode))
	{
		CQ_sendGroupMsg(sg_authCode,group_id,"��׼��~");
	}
	
	return 0;
}

/* (��չ)Ⱥ���������¼�,user_idΪ�������QQ type = 203 */
extern "C" __int32 __stdcall event_notify_lucky_king(__int64 group_id, __int64 user_id, __int64 target_id)
{
	return 0;
}

/* (��չ)Ⱥ����������¼�,honor_type����Ϊtalkative��performer��emotion type = 204 */
extern "C" __int32 __stdcall event_notify_honor(__int64 group_id, const char * honor_type, __int64 user_id)
{
	return 0;
}

/* (��չ)Ⱥ����Ϣ�����¼�,user_idΪ��Ϣ������QQ type = 205 */
extern "C" __int32 __stdcall event_group_recall(__int64 group_id, __int64 user_id, __int64 operator_id,__int32 message_id)
{
	return 0;
}

/* (��չ)˽����Ϣ�����¼� type = 206 */
extern "C" __int32 __stdcall event_friend_recall(__int64 user_id, __int32 message_id)
{
	return 0;
}

/* �Ӻ��������¼� type = 301 */
extern "C" __int32 __stdcall event_friend_request(__int32 sub_type, __int32 send_time, __int64 from_qq, const char *msg, const char *response_flag)
{
	return 0;
}

/* ��Ⱥ���������¼� type = 302 */
extern "C" __int32 __stdcall event_group_request(__int32 sub_type, __int32 send_time, __int64 from_group, __int64 from_qq, const char *msg, const char *response_flag)
{
	return 0;
}

/* ���ͣ���¼� type = 1004 �������� */
extern "C" __int32 __stdcall event_disable()
{
	return 0;
}

/* ����˳��¼� type = 1002 */
extern "C" __int32 __stdcall event_coolq_exit()
{
	return 0;
}

/* menu-�������¼� */
extern "C" __int32 __stdcall menu_check_update()
{
	MessageBoxA(NULL,"�����°�ť�����","INFO",MB_OK);
	return 0;
}





