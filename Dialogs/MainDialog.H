static HWND MainDialog_hWnd;

//////////////////////////////////////////////////////////////////////

extern int InputBox (HWND hDlg, int Msg, int wParam, int lParam)
{
	for(;;)
	{
		if(Msg==WM_INITDIALOG)
		{
			MainDialog_hWnd=hDlg;
			SendMessage(MainDialog_hWnd,(UINT)WM_SETTEXT,(WPARAM)0,(LPARAM)TitleCaption);
			CenterWindow(MainDialog_hWnd);
			break;
		}
		if(Msg==WM_COMMAND)
		{
			if(wParam==102)
			{
				sprintf(F,"%s","*.*");
				OpenFileDialog(hDlg,TitleCaption,F,"","*.*","",0);

				if(strcmp(F,"*.*")==0)
				{
					//										MessageBox (NULL,"No Valad File Selected"," Data Encryption",16);
				}
				else
				{
					encr = 1;
					decr = 0;
					DialogBox(hInstance,MAKEINTRESOURCE(200),MainDialog_hWnd,PasswordDialog);
				}
			}

			if(wParam==103)
			{
				sprintf(F,"%s","*.*");
				OpenFileDialog(hDlg,TitleCaption,F,"","*.*","",0);

				if(strcmp(F,"*.*")==0)
				{
					//										MessageBox (NULL,"No Valad File Selected"," Data Encryption",16);
				}
				else
				{
					decr = 1;
					encr = 0;
					DialogBox(hInstance,MAKEINTRESOURCE(200),MainDialog_hWnd,PasswordDialog);
				}
			}

			if(wParam==104)
			{
				EndDialog(MainDialog_hWnd,0);
			}

			if(wParam==106)
			{
				DialogBox(hInstance,MAKEINTRESOURCE(300),MainDialog_hWnd,AboutDialog);
			}

			break;
		}

		if(Msg==WM_CLOSE)
		{
			EndDialog(hDlg,0);
		}

		break;
	}
	return 0;
}

