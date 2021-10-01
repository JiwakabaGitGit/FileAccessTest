
// FileAccessTest.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CFileAccessTestApp:
// このクラスの実装については、FileAccessTest.cpp を参照してください
//

class CFileAccessTestApp : public CWinApp
{
public:
	CFileAccessTestApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CFileAccessTestApp theApp;
