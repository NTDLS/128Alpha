static HWND AboutDialog_hWnd;

//////////////////////////////////////////////////////////////////////

extern int AboutDialog (HWND hDlg, int Msg, int wParam, int lParam)
{

	for(;;)
	{
		if(Msg==WM_INITDIALOG)
		{
			AboutDialog_hWnd=hDlg;
			CenterWindow(AboutDialog_hWnd);
			break;
		}
		//----------------------------------------------------------------------

		if(Msg==WM_COMMAND)
		{
			EndDialog(AboutDialog_hWnd,0);
            AboutDialog_hWnd = 0;
			break;
		}

		break;
	}
	return 0;
}

