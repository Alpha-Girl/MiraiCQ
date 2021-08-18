#include "httphelp.h"

#include <afxinet.h>

static std::string& replace_all_distinct(std::string& str, const std::string& old_value, const std::string& new_value)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())
	{
		if ((pos = str.find(old_value, pos)) != std::string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}

bool HttpGet( const std::string & strUrl_,const std::string & strSavePath,std::string & contentType,unsigned int timeout )
{
	unsigned short nPort;        //���ڱ���Ŀ��HTTP����˿�
	CString strServer, strObject;    //strServer���ڱ����������ַ��strObject���ڱ����ļ���������
	DWORD dwServiceType,dwRet;        //dwServiceType���ڱ���������ͣ�dwRet���ڱ����ύGET���󷵻ص�״̬��

	std::string strUrl = strUrl_;
	replace_all_distinct(strUrl,"https://","http://");

	//����URL����ȡ��Ϣ
	if(!AfxParseURL(strUrl.c_str(), dwServiceType, strServer, strObject, nPort))
	{
		//����ʧ�ܣ���Url����ȷ
		return false;
	}
	//�����������Ӷ���HTTP���Ӷ���ָ������ڸ����ӵ�HttpFile�ļ�����ָ�룬ע��delete
	CInternetSession intsess;
	CHttpFile *pHtFile = NULL;
	//������������
	CHttpConnection *pHtCon = intsess.GetHttpConnection(strServer,nPort);
	if(pHtCon == NULL)
	{
		//������������ʧ��
		intsess.Close();
		return false;
	}
	//����GET����
	pHtFile = pHtCon->OpenRequest(CHttpConnection::HTTP_VERB_GET,strObject);
	if(pHtFile == NULL)
	{
		//����GET����ʧ��
		intsess.Close();
		delete pHtCon;pHtCon = NULL;
		return false;
	}
	//�ύ����
	pHtFile->SendRequest();
	//��ȡ���������ص�״̬��
	pHtFile->QueryInfoStatusCode(dwRet);
	if (dwRet != HTTP_STATUS_OK)
	{
		//����������������
		intsess.Close();
		delete pHtCon;;
		delete pHtFile;;
		return false;
	}
	//��ȡ�ļ���С
	UINT nFileLen = (UINT)pHtFile->GetLength();
	DWORD dwRead = 1;        //���ڱ�ʶ���˶��٣�Ϊ1��Ϊ�˽���ѭ��
	//����������
	CHAR *szBuffer = new CHAR[nFileLen+1];
	TRY
	{
		//�����ļ�
		CFile PicFile(strSavePath.c_str(),CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive);
		while(dwRead>0)
		{
			//��ջ�����
			memset(szBuffer,0,(size_t)(nFileLen+1));
			//��ȡ��������
			dwRead = pHtFile->Read(szBuffer,nFileLen);
			//д�뵽�ļ�
			PicFile.Write(szBuffer,dwRead);
		}
		//�ر��ļ�
		PicFile.Close();
		//�ͷ��ڴ�
		delete []szBuffer;
		delete pHtFile;
		delete pHtCon;
		//�ر���������
		intsess.Close();
	}
	CATCH(CFileException,e)
	{
		//�ͷ��ڴ�
		delete []szBuffer;
		delete pHtFile;
		delete pHtCon;
		//�ر���������
		intsess.Close();
		return false;            //��д�ļ��쳣
	}
	END_CATCH
		return true;
}
