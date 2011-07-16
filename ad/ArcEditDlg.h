#pragma once

#define KIND_ADD 0
#define KIND_DEL 1
#define KIND_FIND 2

// CArcEdit 对话框
// 弧的 <添加 删除 查找> 对话框


class CArcEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CArcEditDlg)

public:
	CArcEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CArcEditDlg();


// 对话框数据
	enum { IDD = IDD_DIALOG_ARC_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	DECLARE_MESSAGE_MAP()


public:
	//关键字一
	CString strFirKey;
public:
	//关键字二
	CString strSecKey;
public:
	//权重
	int uWeight;
public:
	//对话框种类 ： 添加 删除 查找
	int kindFlag;
public:
	//复选框：双向边等
	BOOL bDouble;


public:
	//设置对话框种类
	void SetKind( int kind );
public:
	afx_msg void OnBnClickedOk();
public:
	virtual BOOL OnInitDialog();

};
