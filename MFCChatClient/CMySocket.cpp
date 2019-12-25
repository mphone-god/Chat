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

	CString strShow;
	
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


	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_RADIO))->GetCheck()) {
		//�Զ��ظ�

		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSEND_RADIO, strAutoSendMsg);
		//���+���ʽ
		CString strName;
		dlg->GetDlgItemText(IDC_NAME, strName);

		CString strMsg = _T("�Զ��ظ�:") + strAutoSendMsg;
		//CString strMsgMsg = dlg->CatShowString(strName, strMsg);
		USES_CONVERSION;
		char* szBuf = T2A(strMsg);
		dlg->m_client->Send(szBuf, SEND_WAX_BUF, 0);

		dlg->m_list.AddString(strMsg);
		dlg->m_list.UpdateData(FALSE);
	}

	CAsyncSocket::OnReceive(nErrorCode);


}