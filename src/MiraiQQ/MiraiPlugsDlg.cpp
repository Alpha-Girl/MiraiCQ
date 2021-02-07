// MiraiPlugsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MiraiQQ.h"
#include "MiraiPlugsDlg.h"
#include "PlusMenuDlg.h"
#include "MiraiQ/MIraiQ.h"
#include <boost/lexical_cast.hpp> 

// CMiraiPlugsDlg �Ի���

IMPLEMENT_DYNAMIC(CMiraiPlugsDlg, CDialog)

CMiraiPlugsDlg::CMiraiPlugsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMiraiPlugsDlg::IDD, pParent)
{

}


CMiraiPlugsDlg::~CMiraiPlugsDlg()
{
}

void CMiraiPlugsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, plus_list_ctrl);
}


BEGIN_MESSAGE_MAP(CMiraiPlugsDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMiraiPlugsDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMiraiPlugsDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


BOOL CMiraiPlugsDlg::OnInitDialog()
{
	CListCtrl * list_ctrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	list_ctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	list_ctrl->InsertColumn(0, _T("����"), LVCFMT_LEFT, 100);
	list_ctrl->InsertColumn(1, _T("�汾"), LVCFMT_LEFT, 100); 
	list_ctrl->InsertColumn(2, _T("����"), LVCFMT_LEFT, 100); 
	list_ctrl->InsertColumn(3, _T(""), LVCFMT_LEFT, 3); 
	MiraiQ * mq = MiraiQ::getInstance();
	std::map<__int32,Plus::PlusDef> plus_map = mq->get_plus_ptr()->get_plus_map();
	int i = 0;
	for(std::map<__int32,Plus::PlusDef>::iterator iter = plus_map.begin();iter!=plus_map.end();iter++)
	{

		list_ctrl->InsertItem(i, iter->second.name.c_str());
		list_ctrl->SetItemText(i, 1,iter->second.version.c_str());
		list_ctrl->SetItemText(i, 2,iter->second.author.c_str());
		list_ctrl->SetItemText(i,3,boost::lexical_cast<std::string>(iter->second.ac).c_str());
		++i;
		//iter->second.
	}
	return TRUE;
}


// CMiraiPlugsDlg ��Ϣ�������

void CMiraiPlugsDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�õ�ѡ�еĲ����AC
	CListCtrl * list_ctrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	POSITION pos=list_ctrl->GetFirstSelectedItemPosition();
	int nId=(int)list_ctrl->GetNextSelectedItem(pos);
	if(nId == -1)
	{
		return ;
	}
	CString ac_str=list_ctrl->GetItemText(nId,3);
	
	

	//����AC�õ�����
	MiraiQ * mq = MiraiQ::getInstance();
	int int_ac =  boost::lexical_cast<__int32>(ac_str);
	std::map<__int32,Plus::PlusDef> plus_map = mq->get_plus_ptr()->get_plus_map();
	Plus::PlusDef & plusdef = plus_map[int_ac];
	
	//��������
	CEdit * des_edit = (CEdit*)GetDlgItem(IDC_EDIT1);
	des_edit->SetWindowText(plusdef.description.c_str());
	GetDlgItem(IDC_STATIC1)->SetWindowText(plusdef.author.c_str());
	GetDlgItem(IDC_STATIC2)->SetWindowText(plusdef.version.c_str());
	*pResult = 0;
}

void CMiraiPlugsDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CListCtrl * list_ctrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	int current_pos =  list_ctrl->GetSelectionMark();
	if(current_pos == -1)
	{
		AfxMessageBox(_T("��ѡ��һ�����"));
		return ;
	}

	CString ac_str=list_ctrl->GetItemText(current_pos,3);
	int int_ac =  boost::lexical_cast<__int32>(ac_str);
	CPlusMenuDlg dlg(int_ac);
	dlg.DoModal();
}
