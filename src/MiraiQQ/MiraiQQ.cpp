// MiraiQQ.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MiraiQQ.h"
#include "MiraiQQDlg.h"
#include "MiraiContrlDlg.h"
#include "gobal_value.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <boost/filesystem.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace logging=boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMiraiQQApp

BEGIN_MESSAGE_MAP(CMiraiQQApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMiraiQQApp ����

CMiraiQQApp::CMiraiQQApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMiraiQQApp ����

CMiraiQQApp theApp;


// CMiraiQQApp ��ʼ��

BOOL CMiraiQQApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	m_pMainWnd = NULL;


	boost::log::core::get()->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());
	boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");
	logging::add_common_attributes();
	boost::log::add_file_log(  
		keywords::auto_flush = true,  
		keywords::file_name =  "log/sign_%Y-%m-%d_%H-%M-%S.%N.log",  
		keywords::rotation_size = 10 * 1024 * 1024,  
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),  
		boost::log::keywords::format = "[%TimeStamp%](%Severity%): %Message%", 
		keywords::min_free_space=3 * 1024 * 1024  
		);  
	if( boost::filesystem::exists("debug.txt"))
	{
		logging::core::get()->set_filter(logging::trivial::severity>=logging::trivial::trace);
	}else
	{
		logging::core::get()->set_filter(logging::trivial::severity>=logging::trivial::info);
	}
	

	{
		static CMiraiQQDlg dlg;
		INT_PTR nResponse = dlg.DoModal();
		if(nResponse != 2)
		{
			static CMiraiContrlDlg ddlg;
			//m_pMainWnd = &ddlg;
			INT_PTR nResponse = ddlg.DoModal();
		}
		HANDLE hself = GetCurrentProcess();
		TerminateProcess(hself, 0);
	}
	{
		
	}
	//{
	//	CMiraiQQDlg dlg;
	//	m_pMainWnd = &dlg;
	//	INT_PTR nResponse = dlg.DoModal();
	//}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
