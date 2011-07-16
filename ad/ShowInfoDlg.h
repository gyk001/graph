#pragma once
#include "afxwin.h"


// CShowInfoDlg 对话框
//	显示深度优先或广度优先搜索序列的对话框

class CShowInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CShowInfoDlg)

public:
	CShowInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowInfoDlg();

// 对话框数据
	enum { IDD = IDD_SHOW_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	//遍历序列
	CString strMessage;
public:
	//遍历方式组合框
	CComboBox ctrlDB_FS;
public:
	//关键字组合框
	CComboBox ctrlKeyList;
public:
	//关键字当前
	CString strKey;
public:
	//遍历方式
	int iDB_FS;

public:
	//更新遍历序列
	void UpdateMessage(void);

public:
	afx_msg void OnChangeKey();
public:
	afx_msg void OnChange();

};
