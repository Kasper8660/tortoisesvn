// TortoiseSVN - a Windows shell extension for easy version control

// Copyright (C) 2010 - TortoiseSVN

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
#pragma once
#include "EditPropBase.h"
#include "StandAloneDlg.h"

class CEditPropTSVNSizes : public CStandAloneDialog, public EditPropBase
{
    DECLARE_DYNAMIC(CEditPropTSVNSizes)

public:
    CEditPropTSVNSizes(CWnd* pParent = NULL);   // standard constructor
    virtual ~CEditPropTSVNSizes();

    enum { IDD = IDD_EDITPROPTSVNSIZES };

    virtual bool            HasMultipleProperties() { return true; }

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedHelp();

    DECLARE_MESSAGE_MAP()

    INT_PTR DoModal() { return CStandAloneDialog::DoModal(); }

private:
    int         m_LogMinSize;
    int         m_LockMinSize;
    int         m_Border;
};
