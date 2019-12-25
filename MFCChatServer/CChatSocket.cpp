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
	CString strShow;
	
	//显示Buf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);

	strShow = dlg->CatShowString(strShow,strRecvMsg);
	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);
	//选中单选框按钮
	if (((CButton*)dlg->GetDlgItem(IDC_OPT_FOR))->GetCheck()) {
		//自动回复
		
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_SEND_EDIT, strAutoSendMsg);
		//封包+组格式
		CString strName;
		dlg->GetDlgItemText(IDC_NAME, strName);

		CString strMsg = _T("自动回复:") + strAutoSendMsg;
		//CString strMsgMsg = dlg->CatShowString(strName, strMsg);
		USES_CONVERSION;
		char* szBuf = T2A(strMsg);
		dlg->m_chat->Send(szBuf, SEND_WAX_BUF, 0);

		dlg->m_list.AddString(strMsg);
		dlg->m_list.UpdateData(FALSE);
	}
	CAsyncSocket::OnReceive(nErrorCode);
	
}
