#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServerDlg.h"
#include "MFCChatServer.h"




CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}

void CChatSocket::OnReceive(int nErrorCode)
{
	TRACE("####Server OnReceive");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();

	char szRecvBuf[SEND_WAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_WAX_BUF, 0);
	TRACE("#####Receive szRecvBuf", szRecvBuf);

	//显示Buf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strShow = _T("客户端: ");

#if 0
	//显示到历史消息框
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X");

	strShow = strTime + strShow;
	strShow += strRecvMsg;
#endif
	strShow = dlg->CatShowString(strShow,strRecvMsg);
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
	
}
