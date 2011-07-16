// ad.h : ad 应用程序的主头文件
//
#pragma once

typedef int ( CALLBACK * FUNC ) ( PCHAR );

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "OrthListGrap.h"
#include "AdjMatrixGrap.h"
#include "ChildSiblingTree.h"
#include "adView.h"
#include "limits"
#include "ShortPathDlg.h"
// CadApp:
// 有关此类的实现，请参阅 ad.cpp
//

class CadApp : public CWinApp
{
public:
	CadApp();
	~CadApp();
public:
	HMODULE m_hModule;

// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
public:
	void InitSkin();

	bool ResToFile(int ResID, CString ResKind,CString &fileName);
	void UpdateIcon(void);
};

extern CadApp theApp;
extern COrthListGrap OrthGrap;
extern CAdjMatrixGrap AdjMatrixGrap;
extern CadView *pView;
extern CChildSiblingTree ChSibDFSTree;
extern CChildSiblingTree ChSibBFSTree;
extern CString fileName;
extern CShortPathDlg* pShortPathDlg;
static  int MAX_INT = (std::numeric_limits<int>::max)()/2;