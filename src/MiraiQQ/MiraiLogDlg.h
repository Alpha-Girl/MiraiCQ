#pragma once


// CMiraiLogDlg �Ի���

class CMiraiLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CMiraiLogDlg)

public:
	CMiraiLogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMiraiLogDlg();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();


// �Ի�������
	enum { IDD = IDD_MIRAILOGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	bool isInEdit;
};
