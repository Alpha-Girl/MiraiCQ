// MiraiQQDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MiraiQQ.h"
#include "MiraiQQDlg.h"
#include "MiraiQ/MIraiQ.h"
#include "MiraiContrlDlg.h"
#include <boost/thread/thread.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMiraiQQDlg �Ի���


CMiraiQQDlg::CMiraiQQDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMiraiQQDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMiraiQQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMiraiQQDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CMiraiQQDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMiraiQQDlg ��Ϣ�������

BOOL CMiraiQQDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_NORMAL);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_EDIT1)->SetWindowText("ws://localhost:6700");

	//AllocConsole();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMiraiQQDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMiraiQQDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMiraiQQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�õ�ִ�е�exe�����ֺ�·��(windows)
static void get_program_dir(std::string &path_name, std::string &exe_name)
{
	char exe_path[MAX_PATH];
	if (GetModuleFileNameA(NULL, exe_path, MAX_PATH) == 0)
	{
		return ;
		//throw logic_error("GetModuleFileNameA����");
	}
	std::string exe_path_string = exe_path;
	size_t pos = exe_path_string.find_last_of('\\', exe_path_string.length());
	path_name = exe_path_string.substr(0, pos);
	exe_name = exe_path_string.substr(pos + 1);
}


static int runBot()
{

	MiraiQ * mq = MiraiQ::getInstance();
	while(true)
	{
		__int32 ret = mq->deal_a_message();
		if(ret == -1)
		{
			BOOST_LOG_TRIVIAL(info) << "�Ѿ����ߣ��������������";
			boost::this_thread::sleep_for(boost::chrono::seconds(5));
			BOOST_LOG_TRIVIAL(info) << "������������......";
			if(mq->bot_connect() == MIRAI_OK)
			{
				BOOST_LOG_TRIVIAL(info) << "�������ӳɹ�" ;
			}else
			{
				BOOST_LOG_TRIVIAL(info) << "��������ʧ��" ;
			}

		}else if(ret == 0)  //no message be dealed
		{
			Sleep(1);
		}else if(ret == 1)  //dealed a message
		{
			continue;
		}

	}

	return 0;
}


void CMiraiQQDlg::OnBnClickedButton1()
{

	if(!LoadLibrary(_T("CQP.dll")))
	{
		AfxMessageBox(_T("CQP.dll not found!"));
		return ;
	}

	CString ws_url;
	GetDlgItem(IDC_EDIT1)->GetWindowText(ws_url);
	MiraiQ * mq = MiraiQ::getInstance();
	assert(mq);
	if(mq->bot_connect(ws_url.GetBuffer(0)) != MIRAI_OK)
	{
		AfxMessageBox(_T("��½ʧ��"));
		return ;
	}
	std::string path_name, exe_name;
	get_program_dir(path_name, exe_name);
	std::vector<boost::filesystem::path>  dll_path_vec = MiraiQ::get_plus_ptr()->find_plus_file(boost::filesystem::path(path_name)/"app");
	for(size_t i = 0;i < dll_path_vec.size();++i)
	{
		BOOST_LOG_TRIVIAL(debug) << dll_path_vec[i];
		mq->load_plus(dll_path_vec[i]);
	}
	mq->call_cq_start_fun();

	//BOOST_LOG_TRIVIAL(debug) << "get_plus_id_list";
	std::vector<__int32> ac_list = mq->get_plus_id_list();

	//���ã�����
	for (size_t i = 0; i < ac_list.size();++i)
	{
		mq->enable_plus(ac_list[i]);
	}
	boost::function0< void> f =  boost::bind(&runBot);
	new boost::thread(f);
	
	
	//CMiraiContrlDlg ddlg;
    //INT_PTR nResponse = ddlg.DoModal();

	CMiraiQQDlg::OnOK();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
