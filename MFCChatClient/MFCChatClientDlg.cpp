﻿
// MFCChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
#include "afxdialogex.h"

#include <atlbase.h>

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


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_CONNECT_BIN, &CMFCChatClientDlg::OnBnClickedConnectBin)
	ON_BN_CLICKED(IDC_SEND_BIN, &CMFCChatClientDlg::OnBnClickedSendBin)
	
	ON_BN_CLICKED(IDC_TEXT_NAME, &CMFCChatClientDlg::OnBnClickedTextName)
	ON_BN_CLICKED(IDC_AUTOSEND_RADIO, &CMFCChatClientDlg::OnBnClickedAutosendRadio)
	ON_BN_CLICKED(IDC_CLEARMSG_BIN, &CMFCChatClientDlg::OnBnClickedClearmsgBin)
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
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
	GetDlgItem(IDC_EPORT_EDIT)->SetWindowText(_T("5555"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("192.168.117.1"));
	


	//从文件获取昵称
	WCHAR wszrName[MAX_PATH] = { 0 };
	WCHAR strPath[MAX_PATH] = { 0 };
	//获取当前路径
	GetCurrentDirectoryW(MAX_PATH, strPath);
	TRACE("####strPath= %ls", strPath);
	//文件名
	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", strPath);
	DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"),NULL,
		wszrName,MAX_PATH, strFilePath);
	if(dwNum > 0){
		//把获取的昵称放到控件
		SetDlgItemText(IDC_NAME, wszrName);
		UpdateData(FALSE);
	}
	else {
		
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"客户端", strFilePath);
		SetDlgItemText(IDC_NAME, L"客户端");
		UpdateData(FALSE);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
CString CMFCChatClientDlg::CatShowString(CString strInfo,CString strMsg){
	
	CString strTime;	

	m_tm = CTime::GetCurrentTime();
	strTime = m_tm.Format("%X");

	//if (strInfo == _T("")) strInfo = _T("我");
	
	strInfo = strTime + strInfo ;
	strInfo += strMsg;
	
	return strInfo;
}


void CMFCChatClientDlg::OnPaint()
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
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMFCChatClientDlg::OnBnClickedConnectBin()
{
	//拿到ip 和 端口
	CString strPort, strIP;
	//从控件里面获取内容
	GetDlgItem(IDC_EPORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);
	
	//CString 转hcar*
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	LPCSTR szIP = (LPCSTR)T2A(strIP);
	TRACE("szPort = %s,strID = %s", szPort, szIP);

	//字符串转换int 
	int iPort = _ttoi(strPort);
	//创建一个socket对象
	m_client = new CMySocket;
	
	//创建套接字
	if(!(m_client->Create())){
		TRACE("m_client->Create() %d", GetLastError());
		return;
	}else{
		TRACE("m_client->Create() Success");
	}

	//连接
	if(m_client->Connect(strIP,iPort) == SOCKET_ERROR){
		TRACE("m_client->Connect() %d", GetLastError());
		return;
	}


	// TODO: 在此添加控件通知处理程序代码
	//TRACE("[Connect]LOVE");
}


void CMFCChatClientDlg::OnBnClickedSendBin()
{
	//获取编辑框的内容
	CString strTmpMsg;
	CString strName ;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowTextW(strTmpMsg);
	GetDlgItem(IDC_NAME)->GetWindowTextW(strName);
	
	strTmpMsg = strName + _T(":") + strTmpMsg;
	//转换
	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	//发送给服务端
	m_client->Send(szSendBuf, SEND_WAX_BUF, 0);


	strName = CatShowString(_T(""), strTmpMsg);
	//显示到历史消息框
	m_list.AddString(strName);
	UpdateData(FALSE);

	//清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));
}



void CMFCChatClientDlg::OnBnClickedTextName()
{
	CString strName;
	//获取文件框的昵称内容
	GetDlgItemText(IDC_NAME, strName);
	if(strName.GetLength() <= 0 ){
		MessageBox(_T("昵称不能为空!"));
		return;
	}
	if(IDOK == AfxMessageBox(_T("确定要修改昵称吗?"),MB_OKCANCEL)){
		//保存昵称
		
		WCHAR strPath[MAX_PATH] = { 0 };

		
		

		//获取当前路径
		GetCurrentDirectoryW(MAX_PATH, strPath);
		TRACE("####strPath= %ls", strPath);
		//文件名
		CString strFilePath;
		strFilePath.Format(L"%ls//Test.ini", strPath);
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);

	}
	
	
}


void CMFCChatClientDlg::OnBnClickedAutosendRadio()
{
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->GetCheck()){

		((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->SetCheck(FALSE);
	}
	else {
		((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->SetCheck(TRUE);
	}
}


void CMFCChatClientDlg::OnBnClickedClearmsgBin()
{
	m_list.ResetContent();
}
