#pragma once


// CMiraiContrlDlg �Ի���

class CMiraiContrlDlg : public CDialog
{
	DECLARE_DYNAMIC(CMiraiContrlDlg)

public:
	CMiraiContrlDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMiraiContrlDlg();

// �Ի�������
	enum { IDD = IDD_MIRAICONTRLDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnClose();
};
