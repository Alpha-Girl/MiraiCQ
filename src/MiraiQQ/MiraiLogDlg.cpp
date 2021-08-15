// MiraiLogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MiraiQQ.h"
#include "MiraiLogDlg.h"
#include "gobal_value.h"


// CMiraiLogDlg �Ի���

IMPLEMENT_DYNAMIC(CMiraiLogDlg, CDialog)

CMiraiLogDlg::CMiraiLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMiraiLogDlg::IDD, pParent)
{
	isInEdit = false;
}

CMiraiLogDlg::~CMiraiLogDlg()
{
	
}

void CMiraiLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMiraiLogDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

BOOL CMiraiLogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(FALSE);
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetLimitText(UINT_MAX);
	SetTimer(1,200,NULL);
	return 0;
}

void CMiraiLogDlg::OnTimer( UINT_PTR nIDEvent )
{
	switch (nIDEvent){
		case 1:
			{
				if(!((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
				{
					std::string str = GetLog();
					CEdit * edit = ((CEdit*)GetDlgItem(IDC_EDIT1));
					CString dat;
					edit->GetWindowText(dat);
					if(dat != str.c_str())
					{
						edit->SetWindowText(str.c_str());
						edit->SetSel(edit->GetWindowTextLength(),edit->GetWindowTextLength());
					}
				}
			}
			break;
		default:
			break;
	}
}

void CMiraiLogDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	//������ɫ����ɫ
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(0,245,255)); 

	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}

HBRUSH CMiraiLogDlg::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_CHECK1)
	{
		pDC->SetBkColor(RGB(0,245,255));    
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CMiraiLogDlg::OnClose()
{
	//KillTimer(1);
	CDialog::OnClose();
}

// CMiraiLogDlg ��Ϣ�������
