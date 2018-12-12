#pragma once
//#include "com/interfaces.h"

class CNkTnlSrvService 
	: public NkService::CServiceBase
	, public NkCom::CServerEvent
	, public NkTrace::CTraceEvent
{
public:
	CNkTnlSrvService(LPCWSTR pszServiceName);
	~CNkTnlSrvService(void);

	//CTraceEvent
	virtual void TraceOut(NkTrace::CTrace::TraceClasses traceclass, const wchar_t* pszText);

	//CServiceBase
	virtual void OnStart(DWORD dwArgc, PWSTR *pszArgv);
	virtual void OnStop();

	//NkCom::CServerEvent
	virtual void on_shutdown(NkCom::CServer* p);

	//CSocketListener
	void on_accept(SOCKET so);

private:
	std::list<NkCom::CServer*> m_Servers;
	NkSocket::CSocketListener<CNkTnlSrvService> m_Listener;
	NkTrace::CLogFile *m_pLogFile = 0;
	NkThreading::CCriticalSection m_lock;
	bool m_shutdown;
	ULONG32 m_next_server_id = 0;

#if defined NK_USE_SSL
	NkSSL::CNKOpenSSLCtx m_ssl_ctx;
#endif
};