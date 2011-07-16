// AreaSizeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ad.h"
#include "AreaSizeDlg.h"


// CAreaSizeDlg 对话框

IMPLEMENT_DYNAMIC(CAreaSizeDlg, CDialog)

CAreaSizeDlg::CAreaSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaSizeDlg::IDD, pParent)
	, width(0)
	, height(0)
	, m_bAuto(false)
{

}

CAreaSizeDlg::~CAreaSizeDlg()
{
}

void CAreaSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, width);
	DDX_Text(pDX, IDC_HEIGHT, height);
}


BEGIN_MESSAGE_MAP(CAreaSizeDlg, CDialog)
	ON_BN_CLICKED(IDC_AUTO, &CAreaSizeDlg::OnBnClickedAuto)
	ON_BN_CLICKED(IDOK, &CAreaSizeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAreaSizeDlg 消息处理程序

void CAreaSizeDlg::OnBnClickedAuto()
{
	m_bAuto = !m_bAuto;
	if(m_bAuto)
	{
		GetDlgItem(IDC_WIDTH)->EnableWindow(false);
		GetDlgItem(IDC_HEIGHT)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_WIDTH)->EnableWindow(true);
		GetDlgItem(IDC_HEIGHT)->EnableWindow(true);
	}
}

void CAreaSizeDlg::OnBnClickedOk()
{
	UpdateData();
	if (!m_bAuto)
	{
		pView->SetAreaSize( width , height);

	}
	else
	{
		pView->AutoCalcAreaSize();
	}
	OnOK();
}
