#ifndef __MSG_ID_CONVERT_H__LGOOODOYHORUBXTX
#define __MSG_ID_CONVERT_H__LGOOODOYHORUBXTX

//����ת��msgIdΪ������

class MsgIdConvert
{
public:
	 __int32 to_cq(__int32 web_msg_id);

	 __int32 to_web(__int32 cq_msg_id);

	 static MsgIdConvert * getInstance();

private:
	MsgIdConvert();
	 
};


#endif