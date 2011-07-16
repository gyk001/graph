#pragma once



// CAddVexDlg 对话框

class CAddVexDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddVexDlg)

public:
	CAddVexDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddVexDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADD_VEX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//关键字
	CString m_strKey;
public:
	afx_msg void OnBnClickedOk();
public:
	// 备注
	CString strMoreInfo;
public:
	afx_msg void OnBnClickedCancle();
};
