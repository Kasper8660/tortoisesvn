// TortoiseSVN - a Windows shell extension for easy version control

// Copyright (C) 2007-2008 - TortoiseSVN

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
#include "StdAfx.h"
#include "RepositoryBrowserCommand.h"

#include "RepositoryBrowser.h"
#include "URLDlg.h"
#include "SVN.h"

bool RepositoryBrowserCommand::Execute()
{
	CString url;
	BOOL bFile = FALSE;
	SVN svn;
	if (!cmdLinePath.IsEmpty())
	{
		if (cmdLinePath.GetSVNPathString().Left(4).CompareNoCase(_T("svn:"))==0)
		{
			// If the path starts with "svn:" and there is another protocol
			// found in the path (a "://" found after the "svn:") then
			// remove "svn:" from the beginning of the path.
			if (cmdLinePath.GetSVNPathString().Find(_T("://"), 4)>=0)
				cmdLinePath.SetFromSVN(cmdLinePath.GetSVNPathString().Mid(4));
		}

		url = svn.GetUIURLFromPath(cmdLinePath);

		if (url.IsEmpty())
		{
			if (SVN::PathIsURL(cmdLinePath.GetSVNPathString()))
				url = cmdLinePath.GetSVNPathString();
			else if (svn.IsRepository(cmdLinePath.GetWinPathString()))
			{
				// The path points to a local repository.
				// Add 'file:///' so the repository browser recognizes
				// it as an URL to the local repository.
				url = _T("file:///")+cmdLinePath.GetWinPathString();
				url.Replace('\\', '/');
			}
		}
	}
	if (cmdLinePath.GetUIPathString().Left(8).CompareNoCase(_T("file:///"))==0)
	{
		cmdLinePath.SetFromUnknown(cmdLinePath.GetUIPathString().Mid(8));
	}
	bFile = PathFileExists(cmdLinePath.GetWinPath()) ? !cmdLinePath.IsDirectory() : FALSE;

	if (url.IsEmpty())
	{
		CURLDlg urldlg;
		if (urldlg.DoModal() != IDOK)
		{
			return false;
		}
		url = urldlg.m_url;
	}

	CString val = parser.GetVal(_T("rev"));
	SVNRev rev(val);
	CRepositoryBrowser dlg(url, rev);
	dlg.m_ProjectProperties.ReadProps(cmdLinePath);
	dlg.m_path = cmdLinePath;
	dlg.DoModal();
	return true;
}