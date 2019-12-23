#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"


CServerSocket::CServerSocket(){

}

CServerSocket::~CServerSocket() {

}
// 回调
void CServerSocket::OnAccept(int nErrorCode){
	TRACE("####OnAccept");
	TRACE("000000000000");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	
	//如果有连接就再创建一个套接字
	dlg->m_chat = new CChatSocket;

	//连接客户端
	Accept(*(dlg->m_chat));
	CString str;

	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X ");
	str += _T("客户端连接成功");
	dlg->m_list.AddString(str);
	dlg->m_list.UpdateData(FALSE);

	

	CAsyncSocket::OnAccept(nErrorCode);
}