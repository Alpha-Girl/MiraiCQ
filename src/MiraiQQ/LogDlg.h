#pragma once


// LogDlg �Ի���

class LogDlg : public CDialog
{
	DECLARE_DYNAMIC(LogDlg)

public:
	LogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LogDlg();

// �Ի�������
	enum { IDD = IDD_LOGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
