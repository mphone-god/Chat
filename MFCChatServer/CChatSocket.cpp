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

	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf, 200, 0);
	TRACE("#####Receive szRecvBuf", szRecvBuf);

	//��ʾBuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strShow = _T("�ͻ���: ");
	CString strRTime;
	
	//��ʾ����ʷ��Ϣ��
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X");

	strShow = strTime + strShow;
	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
	
}
