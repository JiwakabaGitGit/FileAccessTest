
// FileAccessTestDlg.h : ヘッダー ファイル
//

#pragma once


// CFileAccessTestDlg ダイアログ
class CFileAccessTestDlg : public CDialogEx
{
// コンストラクション
public:
	CFileAccessTestDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEACCESSTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	public:
	afx_msg void OnBnClickedPath ();

private:
	CEdit m_editPath;
	CString m_filePath;
	CStdioFile m_fileHandle;

public:
	afx_msg void OnBnClickedButtonOpen ();
	private:
	CButton m_open;
	CButton m_close;
	public:
	afx_msg void OnBnClickedButtonClose ();
	afx_msg void OnBnClickedButtonWrite ();
	private:
	CEdit m_editWriteText;
	CButton m_write;
	public:
	afx_msg void OnBnClickedButtonPathRename ();
	private:
	CEdit m_editPathRename;
	CButton m_copy;
	CButton m_rename;
	public:
	CButton m_delete;
	afx_msg void OnBnClickedButtonCopy ();
	afx_msg void OnBnClickedButtonDelete ();
	afx_msg void OnBnClickedButtonRename ();
};
