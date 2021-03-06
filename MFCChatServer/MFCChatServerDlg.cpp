﻿
// MFCChatServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
#include "afxdialogex.h"
#include "CServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatServerDlg 对话框



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CMFCChatServerDlg::OnBnClickedButton4)

	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatServerDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_GET_NAME, &CMFCChatServerDlg::OnBnClickedGetName)
	ON_BN_CLICKED(IDC_OPT_FOR, &CMFCChatServerDlg::OnBnClickedOptFor)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CMFCChatServerDlg::OnBnClickedClearBtn)
END_MESSAGE_MAP()


// CMFCChatServerDlg 消息处理程序

BOOL CMFCChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_KONG)->SetWindowText(_T("5555"));

	//读取配置文件
	WCHAR wszName[MAX_PATH] = { 0 };
	WCHAR wszPath[MAX_PATH] = { 0 };

	GetCurrentDirectoryW(MAX_PATH, wszPath);
	CString strFilePath;
	strFilePath.Format(L"%ls//TestF.ini", wszPath);

	DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"),
		NULL, wszName, MAX_PATH, strFilePath);
	if (dwNum > 0) {
		TRACE(_T("######ererererererererer"));
		SetDlgItemText(IDC_NAME, wszName);
		UpdateData(FALSE);
		
	}
	else{
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"),
			L"服务端", strFilePath);
		SetDlgItemText(IDC_NAME, L"服务端");
		UpdateData(FALSE);
}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CMFCChatServerDlg::CatShowString(CString strInfo, CString strMsg) {

	CString strTime;

	m_tm = CTime::GetCurrentTime();
	strTime = m_tm.Format("%X");

	//if (strInfo == _T("")) strInfo = _T("我");

	strInfo = strTime + strInfo ;
	strInfo += strMsg;

	return strInfo;
}

void CMFCChatServerDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("####OnBnClickedButton4");
	CString strPort;
	//从控件里面获取内容
	GetDlgItem(IDC_KONG)->GetWindowText(strPort);
	
	//CString 转hcar*
	USES_CONVERSION;

	//CString转换char*
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	

	//调试信息
	TRACE("szPort = %s", szPort);

	int iPort = _ttoi(strPort);

	//创建服务器的Socket对象
	m_server = new CServerSocket;

	//创建套接字
	if(!m_server->Create(iPort)){
		TRACE("!m_server  Create =%d", GetLastError());
		return;
	}

	//连接
	if(!m_server->Listen()){
		TRACE("!m_server  Listen =%d", GetLastError());
		return;
	}
	CString str;
	m_tm = CTime::GetCurrentTime();
	str = m_tm.Format("%X ");
	str += _T("建立服务");
	m_list.AddString(str);
	UpdateData((FALSE));
	
}




void CMFCChatServerDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTmpMsg;
	CString strShow;
	GetDlgItem(IDC_PORT_EDIT)->GetWindowTextW(strTmpMsg);
	GetDlgItemText(IDC_NAME, strShow);
	strTmpMsg = strShow + _T(":") +strTmpMsg;
	
	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	//发送给客户端
	m_chat->Send(szSendBuf, SEND_WAX_BUF, 0);

	
	strShow = CatShowString(_T(""), strTmpMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);

	//清空编辑框
	GetDlgItem(IDC_PORT_EDIT)->SetWindowTextW(_T(""));
}


void CMFCChatServerDlg::OnBnClickedGetName()
{
	CString strName;
	GetDlgItemText(IDC_NAME, strName);
	if (strName.GetLength() <= 0) {
		MessageBox(_T("昵称不能为空!"));
		return;
	}
	if (IDOK == AfxMessageBox(_T("确定修改昵称?"), MB_OKCANCEL)) {
		WCHAR strPath[MAX_PATH] = { 0 };
		//获取文件框的内容
		//获取当前路径
		GetCurrentDirectoryW(MAX_PATH, strPath);

		CString strFilePath;
		strFilePath.Format(L"%ls//TestF.ini", strPath);
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
	}
}

void CMFCChatServerDlg::OnBnClickedOptFor()
{
	if (((CButton*)GetDlgItem(IDC_OPT_FOR))->GetCheck()){
		((CButton*)GetDlgItem(IDC_OPT_FOR))->SetCheck(FALSE);
	}
	else {
		((CButton*)GetDlgItem(IDC_OPT_FOR))->SetCheck(TRUE);
	}
}


void CMFCChatServerDlg::OnBnClickedClearBtn()
{
	m_list.ResetContent();
}
