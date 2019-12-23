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
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();

	
#if 0
	dig->m_tm = CTime::GetCurrentTime();
	str = dig->m_tm.Format("%X");
	str += _T("����������ӳɹ�");
#endif
	CString strInfo = _T(" ");
	CString strMsg = _T("����������ӳɹ�");
	CString str;
	str = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(str);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode){

	TRACE("####OnReceive");

	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();

	char szRecvre[SEND_WAX_BUF] = { 0 };

	Receive(szRecvre, SEND_WAX_BUF, 0);

	USES_CONVERSION;
	CString strRecver = A2W(szRecvre);

	CString strShow = _T("�����");
#if 0
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X:");

	strShow = strTime + strShow;
	strShow += strRecver;
#endif
	CString str;
	str = dlg->CatShowString(strShow, strRecver);
	dlg->m_list.AddString(str);

	CAsyncSocket::OnReceive(nErrorCode);


}