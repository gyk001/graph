#pragma once


// CAreaSizeDlg 对话框
// 调整画板大小的对话框


class CAreaSizeDlg : public CDialog
{
	DECLARE_DYNAMIC(CAreaSizeDlg)

public:
	CAreaSizeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAreaSizeDlg();

// 对话框数据
	enum { IDD = IDD_AREA_SIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//宽
	UINT width;
public:
	//高
	UINT height;
public:
	//自动计算
	bool m_bAuto;

public:
	afx_msg void OnBnClickedAuto();
public:
	afx_msg void OnBnClickedOk();
};
