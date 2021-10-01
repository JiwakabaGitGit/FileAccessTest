
// FileAccessTestDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "FileAccessTest.h"
#include "FileAccessTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileAccessTestDlg ダイアログ
#define FILE_EXT  _T("*.*")
#define FILE_EXT_ALL   _T("全て(*.*)|*.*||")

CFileAccessTestDlg::CFileAccessTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILEACCESSTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileAccessTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange ( pDX );
	DDX_Control ( pDX, IDC_EDIT_PATH, m_editPath );
	DDX_Control ( pDX, IDC_BUTTON_OPEN, m_open );
	DDX_Control ( pDX, IDC_BUTTON_CLOSE, m_close );
	DDX_Control ( pDX, IDC_EDIT_WRITETEXT, m_editWriteText );
	DDX_Control ( pDX, IDC_BUTTON_WRITE, m_write );
}

BEGIN_MESSAGE_MAP(CFileAccessTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED ( IDC_BUTTON_PATH, &CFileAccessTestDlg::OnBnClickedPath )
	ON_BN_CLICKED ( IDC_BUTTON_OPEN, &CFileAccessTestDlg::OnBnClickedButtonOpen )
	ON_BN_CLICKED ( IDC_BUTTON_CLOSE, &CFileAccessTestDlg::OnBnClickedButtonClose )
	ON_BN_CLICKED ( IDC_BUTTON_WRITE, &CFileAccessTestDlg::OnBnClickedButtonWrite )
END_MESSAGE_MAP()


// CFileAccessTestDlg メッセージ ハンドラー

BOOL CFileAccessTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	m_open.EnableWindow( TRUE );
	m_close.EnableWindow( FALSE );
	m_write.EnableWindow ( FALSE );

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CFileAccessTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CFileAccessTestDlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

void CFileAccessTestDlg::OnBnClickedPath()
{
	TCHAR szFile[ MAX_PATH * 256 ];
	int sz = sizeof( szFile ) / sizeof ( TCHAR );
	OPENFILENAME openFilename;
	szFile[ 0 ] = _T( '\0' );
	ZeroMemory ( &openFilename, sizeof( openFilename ) );
	openFilename.lStructSize = sizeof( openFilename );      // 構造体サイズ
	openFilename.hwndOwner = 0;								// 親ウィンドウのハンドル
	openFilename.lpstrInitialDir = _TEXT ( "C:\\" );		// 初期フォルダー
	openFilename.lpstrFile = szFile;						// 取得したファイル名を保存するバッファ
	openFilename.nMaxFile = sz;                             // 取得したファイル名を保存するバッファサイズ
	openFilename.lpstrFilter = FILE_EXT_ALL;
	openFilename.lpstrDefExt = FILE_EXT;
	openFilename.lpstrTitle = _TEXT( "ファイルPATHを指定" );
	openFilename.nFilterIndex = 1;
	GetOpenFileName ( &openFilename );

	m_editPath.SetWindowTextW( szFile );
}

void CFileAccessTestDlg::OnBnClickedButtonOpen()
{
	m_filePath.Empty();
	m_editPath.GetWindowTextW ( m_filePath );

	// オープンの仕方を指定します(読み取り専用)
	UINT nOpenFlags = CFile::modeReadWrite | CFile::modeNoTruncate | CStdioFile::modeCreate;
	CStdioFile ifp;
	try
	{
		//ファイルをオープンします。
		if ( m_fileHandle.Open( m_filePath, nOpenFlags ) != NULL )
		{
			m_open.EnableWindow( FALSE );
			m_close.EnableWindow( TRUE );
			m_write.EnableWindow ( TRUE );
			m_fileHandle.SeekToEnd();
		}
	}
	catch ( CFileException* exp )
	{
		TRACE( "CExp Catch %d\n", exp->m_cause );
		exp->Delete ();
	}
}


void CFileAccessTestDlg::OnBnClickedButtonClose()
{
	m_fileHandle.Close();

	m_open.EnableWindow ( TRUE );
	m_close.EnableWindow ( FALSE );
	m_write.EnableWindow( FALSE );
}


void CFileAccessTestDlg::OnBnClickedButtonWrite()
{
	CString writeText;
	m_editWriteText.GetWindowTextW ( writeText );
	
	m_fileHandle.WriteString( writeText );
	m_fileHandle.Write ( ( "\r\n" ), 2 );
	m_fileHandle.Flush();
}
