#pragma once
#include <afxsock.h>
class CMySocket :
	public CAsyncSocket
{
public:
	CMySocket();
	virtual ~CMySocket();//Îö¹¹º¯Êý
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

