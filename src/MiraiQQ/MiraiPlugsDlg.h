#pragma once
#include "afxcmn.h"


// CMiraiPlugsDlg �Ի���

class CMiraiPlugsDlg : public CDialog
{
	DECLARE_DYNAMIC(CMiraiPlugsDlg)

public:
	CMiraiPlugsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMiraiPlugsDlg();

// �Ի�������
	enum { IDD = IDD_MIRAIPLUGSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl plus_list_ctrl;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
};
