static HWND PasswordDialog_hWnd;

//////////////////////////////////////////////////////////////////////

extern int PasswordDialog (HWND hDlg, int Msg, int wParam, int lParam)
{
	for(;;)
	{
		if(Msg==WM_INITDIALOG)
		{
			PasswordDialog_hWnd=hDlg;
			SendMessage(PasswordDialog_hWnd,(UINT)WM_SETTEXT,(WPARAM)0,(LPARAM)TitleCaption);
			CenterWindow(PasswordDialog_hWnd);
			infotext_static=GetDlgItem(PasswordDialog_hWnd,101);
			password_edit=GetDlgItem(PasswordDialog_hWnd,102);
			if(encr || !decr)
			{
				SetText(infotext_static,"Enter A Password To Be Used To Encrypt This Data");
			}

			if(decr || !encr)
			{
				SetText(infotext_static,"Enter The Password That Was Used To Encrypt This Data.");
			}
			break;
		}
		//----------------------------------------------------------------------

		if(Msg==WM_COMMAND)
		{

			if(wParam==103)
			{

				if(encr || !decr)
				{
                    EndDialog(PasswordDialog_hWnd,0);
					incode(F,GetText(password_edit));
				}

				if(decr || !encr)
				{
                    EndDialog(PasswordDialog_hWnd,0);
            		decode(F,GetText(password_edit));
				}

				encr = 0;
				decr = 0;
				EndDialog(PasswordDialog_hWnd,0);
			}

			if(wParam==104)
			{
				encr = 0;
				decr = 0;
				EndDialog(PasswordDialog_hWnd,0);
			}

			break;
		}

		if(Msg==WM_CLOSE)
		{
			EndDialog(PasswordDialog_hWnd,0);
		}

		break;
	}
	return 0;
}

