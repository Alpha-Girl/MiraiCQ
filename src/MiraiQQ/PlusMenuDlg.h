#pragma once


// CPlusMenuDlg �Ի���

class CPlusMenuDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlusMenuDlg)

public:
	CPlusMenuDlg(__int32 ac,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPlusMenuDlg();

// �Ի�������
	enum { IDD = IDD_PLUS_MENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	__int32 ac;
public:
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
