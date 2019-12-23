#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"

CMySocket::CMySocket(){


}
CMySocket::~CMySocket() {
	//��������
}

void CMySocket::OnConnect(int nErrorCode){

	TRACE("####OnConnect");
	CMFCChatClientDlg* dig = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString str;
	dig->m_tm = CTime::GetCurrentTime();
	str = dig->m_tm.Format("%X");
	str += _T("����������ӳɹ�");
	dig->m_list.AddString(str);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode){

	TRACE("####OnReceive");

	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();

	char szRecvre[200] = { 0 };

	Receive(szRecvre, 200, 0);

	USES_CONVERSION;
	CString strRecver = A2W(szRecvre);
	CString strShow = _T("�����: ");
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X:");

	strShow = strTime + strShow;
	strShow += strRecver;
	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnReceive(nErrorCode);


}