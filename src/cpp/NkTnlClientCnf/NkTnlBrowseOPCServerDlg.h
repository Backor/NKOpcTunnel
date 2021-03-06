/*	This file is part of NKOpcTunnel.
*
*	Copyright (c) Henryk Anschuetz 
*	Berlin, Germany
*
*	mailto:uzuul23@online.de
*
*	NKOpcTunnel is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   NKOpcTunnel is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with NKOpcTunnel.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class CNkTnlBrowseOPCServerDlg : public nkresize::CResizableDialog
{
	DECLARE_DYNAMIC(CNkTnlBrowseOPCServerDlg)

public:
	CNkTnlBrowseOPCServerDlg(CWnd* pParent = NULL);
	virtual ~CNkTnlBrowseOPCServerDlg();

	enum { IDD = IDD_NKTNLBROWSEOPCSERVERDLG };

	class CServerInfo
	{
	public:
		CServerInfo() : m_CLSID(GUID_NULL)
			, m_bOPCDAServer10(false)
			, m_bOPCDAServer20(false)
			, m_bOPCDAServer30(false)
		{
		}
		CServerInfo(GUID guid, LPOLESTR pszProgID, LPOLESTR pszUserType
			, bool* pbOPCDAServer10, bool* pbOPCDAServer20, bool* pbOPCDAServer30)
			: m_CLSID(guid)
			, m_strProgID(pszProgID)
			, m_strUserType(pszUserType)
			, m_bOPCDAServer10(false)
			, m_bOPCDAServer20(false)
			, m_bOPCDAServer30(false)
		{
			if (pbOPCDAServer10) {
				m_bOPCDAServer10 = *pbOPCDAServer10;
			}
			if (pbOPCDAServer20) {
				m_bOPCDAServer20 = *pbOPCDAServer20;
			}
			if (pbOPCDAServer30) {
				m_bOPCDAServer30 = *pbOPCDAServer30;
			}
		}
		CServerInfo(CServerInfo& d)
		{
			*this = d;
		}
		CServerInfo& operator=(const CServerInfo& d)
		{
			m_CLSID = d.m_CLSID;
			m_strProgID = d.m_strProgID;
			m_strUserType = d.m_strUserType;
			m_bOPCDAServer10 = d.m_bOPCDAServer10;
			m_bOPCDAServer20 = d.m_bOPCDAServer20;
			m_bOPCDAServer30 = d.m_bOPCDAServer30;
			return *this;
		}
		CLSID m_CLSID;
		CString m_strProgID;
		CString m_strUserType;
		bool m_bOPCDAServer10;
		bool m_bOPCDAServer20;
		bool m_bOPCDAServer30;
	};

	CStringA m_strServerAddr;
	BOOL m_bUseSSL = FALSE;
	BOOL m_bVerifyServer = FALSE;
	BOOL m_bClientCertificate = FALSE;
	std::vector<BYTE> *m_pvecPass = 0;
	CServerInfo* GetSelServerInfo();

private:
	
	CArray<CServerInfo> m_Servers;
	INT_PTR m_IndexSel;
	CImageList m_listImages;
	CTreeCtrl m_wndServerTree;
	CButton m_wndOKButton;
	LPARAM AddServer(GUID guid, LPOLESTR pszProgID, LPOLESTR pszUserType
		, bool* pbOPCDAServer10, bool* pbOPCDAServer20, bool* pbOPCDAServer30);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnTvnSelchangedServerTree(NMHDR *pNMHDR, LRESULT *pResult);
};
