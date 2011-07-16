#pragma once
#include "afxcmn.h"


// CArcInfoDlg 对话框
// 显示弧信息的对话框

class CArcInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CArcInfoDlg)

public:
	CArcInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CArcInfoDlg();

// 对话框数据
	enum { IDD = IDD_ARC_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ctrlArcList;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
