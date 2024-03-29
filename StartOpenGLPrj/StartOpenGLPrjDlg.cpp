
// StartOpenGLPrjDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StartOpenGLPrj.h"
#include "StartOpenGLPrjDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStartOpenGLPrjDlg dialog



CStartOpenGLPrjDlg::CStartOpenGLPrjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STARTOPENGLPRJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStartOpenGLPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStartOpenGLPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_X, &CStartOpenGLPrjDlg::OnDeltaposMoveX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_Y, &CStartOpenGLPrjDlg::OnDeltaposMoveY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MOVE_Z, &CStartOpenGLPrjDlg::OnDeltaposMoveZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_Rotate_X, &CStartOpenGLPrjDlg::OnDeltaposRotateX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_Rotate_Y, &CStartOpenGLPrjDlg::OnDeltaposRotateY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_Rotate_Z, &CStartOpenGLPrjDlg::OnDeltaposRotateZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, &CStartOpenGLPrjDlg::OnDeltaposSpin6)
	ON_BN_CLICKED(IDC_SEVIVON, &CStartOpenGLPrjDlg::OnBnClickedSevivon)
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_STOPTIMER, &CStartOpenGLPrjDlg::OnFileStoptimer)
END_MESSAGE_MAP()


// CStartOpenGLPrjDlg message handlers

BOOL CStartOpenGLPrjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//ptrView = new CGlView(this);

	//CWnd* ptrPicture = GetDlgItem(IDC_PICTURE);
	//ptrView = new CGlView(ptrPicture);

	ptrView = new CGlView(GetDlgItem(IDC_PICTURE));

	SetTimer(2, 200, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStartOpenGLPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStartOpenGLPrjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		ptrView->vDrawGLScene();
		
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStartOpenGLPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStartOpenGLPrjDlg::OnStnClickedCtrlpic()
{
	// TODO: Add your control notification handler code here

}



void CStartOpenGLPrjDlg::OnDeltaposMoveX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	// TODO: Add your control notification handler code here

	ptrView->setMoveX(ptrView->getMoveX() + (pNMUpDown->iDelta * -0.1f));

	//pNMUpDown->iDelta == -1 ? ptrView->setMoveX(ptrView->getMoveX() + 0.1f) : ptrView->setMoveX(ptrView->getMoveX() - 0.1f);

	/*
	if (pNMUpDown->iDelta == -1)
		ptrView->setMoveX(ptrView->getMoveX() + 0.1f);
	else
		ptrView->setMoveX(ptrView->getMoveX() - 0.1f);
	*/

	ptrView->vDrawGLScene();

	*pResult = 0;
}


void CStartOpenGLPrjDlg::OnDeltaposMoveY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	// TODO: Add your control notification handler code here
	ptrView->setMoveY(ptrView->getMoveY() + (pNMUpDown->iDelta * -0.1f));
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void CStartOpenGLPrjDlg::OnDeltaposMoveZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	// TODO: Add your control notification handler code here
	ptrView->setMoveZ(ptrView->getMoveZ() + (pNMUpDown->iDelta * -0.1f));
	ptrView->vDrawGLScene();

	*pResult = 0;
}


void CStartOpenGLPrjDlg::OnDeltaposRotateX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	ptrView->RotateX(ptrView->getRotX()+(15* (pNMUpDown->iDelta * (-1))));
	ptrView->vDrawGLScene();
	*pResult = 0;
}


void CStartOpenGLPrjDlg::OnDeltaposRotateY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	ptrView->RotateY(ptrView->getRotY() + (15 * pNMUpDown->iDelta));
	ptrView->vDrawGLScene();
	*pResult = 0;
}


void CStartOpenGLPrjDlg::OnDeltaposRotateZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	ptrView->RotateZ(ptrView->getRotZ() + (15 * pNMUpDown->iDelta));
	ptrView->vDrawGLScene();
	*pResult = 0;
}


void CStartOpenGLPrjDlg::OnDeltaposSpin6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	ptrView->RotHatX(ptrView->getHatX() + (15 * pNMUpDown->iDelta));
	ptrView->vDrawGLScene();
	*pResult = 0;
}


void CStartOpenGLPrjDlg::OnBnClickedSevivon()
{
	//ptrView->vDrawSevivonScene();

	static bool isSevivon = true;
	CButton* ptrSevivonBtn = (CButton*)GetDlgItem(IDC_SEVIVON);

	if (isSevivon)
	{
		KillTimer(2);
		SetTimer(1, 50, NULL);
		ptrSevivonBtn->SetWindowText(L"Robot");
	}
	else
	{
		KillTimer(1);
		SetTimer(2, 200, NULL);
		ptrSevivonBtn->SetWindowText(L"Sevivon");
	}
	isSevivon = !isSevivon;
	

	/*
	for (int i=0; i < 100; i++) 
	{
		ptrView->SevivonRot(ptrView->getSevivonRot() + 5);
		Sleep(100);
		ptrView->vDrawSevivonScene();
	}
	*/
}


void CStartOpenGLPrjDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);

	if (nIDEvent == 1)
	{
		ptrView->SevivonRot(ptrView->getSevivonRot() + 5);
		ptrView->vDrawSevivonScene();
	}
	else if (nIDEvent == 2)
	{
		ptrView->RotateX(ptrView->getRotX() + 15);
		ptrView->RotateY(ptrView->getRotY() + 15);
		ptrView->RotateZ(ptrView->getRotZ() + 15);
		ptrView->RotHatX(ptrView->getHatX() + 15);
		ptrView->vDrawGLScene();
	}
}


void CStartOpenGLPrjDlg::OnFileStoptimer()
{
	KillTimer(1);
	KillTimer(2);
}
