#pragma once
#include "afxwin.h"

#define KIND_ADD 0
#define KIND_DEL 1
// CVexInfoDlg 对话框
// 显示顶点信息的对话框


class CVexInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CVexInfoDlg)

public:
	CVexInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVexInfoDlg();

// 对话框数据
	enum { IDD = IDD_VEX_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnInitDialog();

public:
	//顶点关键字
	CString strKey;
public:
	//对话框种类
	int kindFlag;
public:
	//入度
	int iInDegree;
public:
	//出度
	int iOutDegree;
public:
	//备注
	CString strMoreInfo;
public:
	//关键字组合框
	CComboBox ctrlKeyList;

public:
	//更新顶点信息
	void UpdateInfo(CString key);

public:
	afx_msg void OnCbnSelchangeComboKeyList();

};
