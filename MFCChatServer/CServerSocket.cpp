#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"


CServerSocket::CServerSocket(){

}

CServerSocket::~CServerSocket() {

}
// �ص�
void CServerSocket::OnAccept(int nErrorCode){
	TRACE("####OnAccept");
	TRACE("000000000000");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	
	//��������Ӿ��ٴ���һ���׽���
	dlg->m_chat = new CChatSocket;

	//���ӿͻ���
	Accept(*(dlg->m_chat));
	CString str;

	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X ");
	str += _T("�ͻ������ӳɹ�");
	dlg->m_list.AddString(str);
	dlg->m_list.UpdateData(FALSE);

	

	CAsyncSocket::OnAccept(nErrorCode);
}