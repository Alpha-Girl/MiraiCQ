// MiraiContrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MiraiQQ.h"
#include "MiraiContrlDlg.h"
#include "MiraiPlugsDlg.h"
#include "MiraiQ/MIraiQ.h"
#include <boost/thread/thread.hpp>


#define WM_SHOWTASK WM_USER+1

// CMiraiContrlDlg �Ի���

IMPLEMENT_DYNAMIC(CMiraiContrlDlg, CDialog)

CMiraiContrlDlg::CMiraiContrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMiraiContrlDlg::IDD, pParent)
{

}

CMiraiContrlDlg::~CMiraiContrlDlg()
{
}


void CMiraiContrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMiraiContrlDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &CMiraiContrlDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMiraiContrlDlg::OnBnClickedButton4)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_SHOWTASK,onShowTask)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

static NOTIFYICONDATA nid;
 BOOL CMiraiContrlDlg::OnInitDialog()
 {
    CDialog::OnInitDialog();

	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK;
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy_s(nid.szTip,"MiraiCQ");
	Shell_NotifyIcon(NIM_ADD,&nid);

    return 0;

 }


LRESULT CMiraiContrlDlg::onShowTask(WPARAM wParam,LPARAM lParam)
{
	if(wParam!=IDR_MAINFRAME)
		return 1;
	if(lParam == WM_LBUTTONDBLCLK)
	{
		this->ShowWindow(SW_SHOW);
	}
	return 0;
}

// CMiraiContrlDlg ��Ϣ�������

void CMiraiContrlDlg::OnBnClickedButton3()
{
	CMiraiPlugsDlg dlg;
	dlg.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CMiraiContrlDlg::OnBnClickedButton4()
{
	if(MiraiQ::getInstance()->is_bot_connect() == MIRAIQ_BOT_IS_CONNECT)
	{
		AfxMessageBox("websocket�Ѿ��ɹ�����");
	}else
	{
		AfxMessageBox("websocketû�гɹ�����");
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
static void stop_tip()
{
	MessageBoxA(NULL,"���ڹرգ�5s��","",MB_OK);
}
void CMiraiContrlDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	boost::function0< void> f =  boost::bind(&stop_tip);
	new boost::thread(f);
	MiraiQ * mq = MiraiQ::getInstance();
	mq->call_cq_stop_fun();
	HANDLE hself = GetCurrentProcess();
	::Shell_NotifyIcon(NIM_DELETE,&nid);
	TerminateProcess(hself, 0);
	CDialog::OnClose();
}

void CMiraiContrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nID==SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
		return ;
	}
	CDialog::OnSysCommand(nID, lParam);
}
