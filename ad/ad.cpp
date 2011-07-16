// ad.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ad.h"
#include "MainFrm.h"

#include "adDoc.h"
#include "adView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CadApp

BEGIN_MESSAGE_MAP(CadApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CadApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CadApp 构造

CadApp::CadApp()
{
}

CadApp::~CadApp()
{
	FreeLibrary(m_hModule);
}
// 唯一的一个 CadApp 对象

CadApp theApp;
COrthListGrap OrthGrap;
CChildSiblingTree ChSibDFSTree;
CChildSiblingTree ChSibBFSTree;
CAdjMatrixGrap AdjMatrixGrap;
CString fileName = "";
CShortPathDlg* pShortPathDlg = NULL;

CadView *pView;

void CadApp::InitSkin()
{
	CString strDLLName;
	CString strSknName;
	CHAR szSknName [ MAX_PATH ];
	if(ResToFile( IDR_SKIN_DLL,"DLL", strDLLName))
		if(ResToFile( IDR_SKIN,"SKN", strSknName))
		{
			m_hModule  = LoadLibrary ( strDLLName );
			FUNC pFunc = ( FUNC ) GetProcAddress ( theApp.m_hModule, "LoadSkin" );
			strcpy_s ( szSknName, strSknName );
			pFunc ( szSknName );
		}
}


bool CadApp::ResToFile(int ResID, CString ResKind, CString &fileName)
{
	HRSRC  res=::FindResource(NULL,  MAKEINTRESOURCE(ResID),  ResKind);
	HGLOBAL  gl=::LoadResource(NULL,res);
	LPVOID  lp=::LockResource(gl);   //  查找，加载，锁定资源  
	
	char strFileName[MAX_PATH];
	GetTempPath(MAX_PATH,strFileName);
	GetTempFileName(strFileName,"Guo",0,strFileName);

	HANDLE fp=::CreateFile(strFileName,
		GENERIC_WRITE,
		FILE_SHARE_READ ,
		NULL,
		CREATE_ALWAYS, 
		0, 
		NULL);  

		DWORD aa;              
	if (!::WriteFile (fp,lp,::SizeofResource(AfxGetResourceHandle(),res),&aa,NULL))
	{
		return false;      //sizeofResource 得到资源文件的大小 
	}

	::CloseHandle (fp);       //关闭句柄
	::FreeResource (gl);     //释放内存
	fileName = strFileName;
	return true;
}



// CadApp 初始化

BOOL CadApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	
	CWinApp::InitInstance();

	InitSkin();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("Grap_GuoYukun_jk071"));
	  
	// 加载标准 INI 文件选项(包括 MRU)
	LoadStdProfileSettings(4); 
	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CadDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CadView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 启用“DDE 执行”
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	COleObjectFactory::UpdateRegistryAll();
	
	
	//删除右键新建项
	RegDeleteKey(HKEY_CLASSES_ROOT,_T(".grs\\ShellNew"));
	
	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);   

	fileName=cmdInfo.m_strFileName;   
	if(fileName!="")   
	{   
		cmdInfo.m_nShellCommand=CCommandLineInfo::FileNew;   
	}   

	//   Dispatch   commands   specified   on   the   command   line   
	if   (!ProcessShellCommand(cmdInfo))   
		return   FALSE;   


	// 唯一的一个窗口已初始化，因此显示它并对其进行更新

	
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand  之后发生
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CadApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CadApp 消息处理程序


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

CDocument* CadApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
  /*
	CFileFind finder;
	if(finder.FindFile(lpszFileName))
	{

		
		if(AdjMatrixGrap.CreateFromFile(lpszFileName))
		{
			if ( pView->iViewMode != GRAP_VIEW )
			{
				pView->OnMenuOrthlistGrap();
			}
			OrthGrap.CreateOrthListFromMatrix();
			ChSibBFSTree.bNeedChange = true;
			ChSibDFSTree.bNeedChange = true;
			pView->Invalidate();
		}

		return ((CFrameWnd *)this->m_pMainWnd)->GetActiveView()->GetDocument();
	}
	else
	{
		MessageBox(NULL,_T("文件不存在！"),_T("文件打开错误"),MB_OK);
		return NULL;
	}
	*/
	return CWinApp::OpenDocumentFile(lpszFileName);
}

