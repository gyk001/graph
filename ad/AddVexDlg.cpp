// DlgAddVex.cpp : 实现文件
//

#include "stdafx.h"
#include "ad.h"
#include "AddVexDlg.h"


// CAddVexDlg 对话框

IMPLEMENT_DYNAMIC(CAddVexDlg, CDialog)

CAddVexDlg::CAddVexDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddVexDlg::IDD, pParent)
	, m_strKey(_T(""))
	, strMoreInfo(_T("备注……"))
{

}

CAddVexDlg::~CAddVexDlg()
{
}

void CAddVexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_KEY, m_strKey);
	DDX_Text(pDX, IDC_MORE_INFO, strMoreInfo);
}


BEGIN_MESSAGE_MAP(CAddVexDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAddVexDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCLE, &CAddVexDlg::OnBnClickedCancle)
END_MESSAGE_MAP()


// CAddVexDlg 消息处理程序


void CAddVexDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strKey.Replace(" ","");
	m_strKey.Replace("-","");
	if (!(m_strKey == ""))
		OnOK();
}

void CAddVexDlg::OnBnClickedCancle()
{
	OnCancel();
}
