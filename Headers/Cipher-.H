int decode(char *, char *);
int full_decode(char *, int);
int flag, key_size, string_length, scan_locate;
int loopcount, break_loop, end_file;
FILE *working, *temp_file;
char char_buffer, offset_buffer;
char *temp_string, *header, *key;
char *total_query, *query, *key;

/////////////////////////////////////////////////////////////////////

int decode(char *input_query, char *input_key)
{

	//----------------------------------------------------------------------

	if(working)
	{
		fclose(working);
	}

	if(temp_file)
	{
		fclose(temp_file);
	}

	flag = 0;
	key_size = 0;
	string_length = 0;
	scan_locate = 0;
	loopcount = 0;
	break_loop = 0;
	end_file = 0;
	char_buffer = 0;
	offset_buffer = 0;
	temp_string = 0;
	header = 0;
	key = 0;
	total_query = 0;
	query = 0;
	key = 0;

	//----------------------------------------------------------------------

	end_file = 0;

	if((working = fopen(input_query,"rb")) == NULL)
	{
		Error("Could Not Open Source For Key Compare. Error:100.");

		if(working)
		{
			fclose(working);
		}

		if(temp_file)
		{
			fclose(temp_file);
		}

		return 0;
	}

	header = calloc(100, sizeof(char));

	//----------------------------------------------------------------

	while (end_file != EOF)
	{
		end_file = fscanf(working, "%c", &char_buffer);
		loopcount++;

		if(loopcount < 11)
		{
			if (end_file != EOF)
			{
				offset_buffer = char_buffer + 128;
				strcat(header, &offset_buffer);
			}
		}

		if(loopcount == 11)
		{
			if(strcmp("Åמדעשנפוה‏",header) != 0)
			{
				MessageBox(GetActiveWindow(), "Source File Not Encrypted." ,TitleCaption, 0);

				if(working)
				{
					fclose(working);
				}

				if(temp_file)
				{
					fclose(temp_file);
				}

				return 0;
			}

			header = NULL;
			header = calloc(100, sizeof(char));
			flag = 1;

		}

		if(flag == 1)
		{
			if (end_file != EOF)
			{
				offset_buffer = char_buffer + 128;
				strcat(header, &offset_buffer);
			}

			if(loopcount > 11)
			{
				flag = 2;
				key_size = CharInt(header);
				header = NULL;
				header = calloc(100, sizeof(char));
			}
		}

		if(flag == 2)
		{
			if(loopcount > 13)
			{
				if(loopcount < 14+key_size)
				{
					if (end_file != EOF)
					{
						offset_buffer = char_buffer + 128;
						strcat(header, &offset_buffer);
					}
				}
			}

			if(loopcount == 14+key_size)
			{
				key = header;
				header = NULL;
				break;
			}
		}
	}

	if(strcmp(input_key,key) != 0)
	{
		MessageBox (GetActiveWindow(), "Password Incorrect." ,TitleCaption, 0);

		if(working)
		{
			fclose(working);
		}

		if(temp_file)
		{
			fclose(temp_file);
		}

		return 0;
	}

	if(working)
	{
		fclose(working);
	}

	if(temp_file)
	{
		fclose(temp_file);
	}

	full_decode(input_query, loopcount - 1);
	return 0;

}

/////////////////////////////////////////////////////////////////////

int full_decode(char *decode_input, int start_length)
{
	temp_path = calloc(100, sizeof(char));
	strcat(temp_path, Get_TempDirectory());
	strcat(temp_path, "Data.Secure");

	if((working = fopen(decode_input,"rb")) == NULL)
	{
		Error("Could Not Open Source For Read. Error:103.");

		if(working)
		{
			fclose(working);
		}

		if(temp_file)
		{
			fclose(temp_file);
		}

		return 0;
	}

	if((temp_file = fopen(temp_path,"wb")) == NULL)
	{
		Error("Could Not Open Temp File For Write. Error:104.");

		if(working)
		{
			fclose(working);
		}

		if(temp_file)
		{
			fclose(temp_file);
		}

		unlink(temp_path);
		return 0;
	}

	end_file = 0;
	loopcount = 0;

	while (end_file != EOF)
	{
		loopcount++;
		end_file = fscanf(working, "%c", &char_buffer);

		if (end_file != EOF)
		{
			if(loopcount > start_length)
			{
				offset_buffer = char_buffer + 128;
				fprintf(temp_file, "%c", offset_buffer);
			}
		}
	}

	if(working)
	{
		fclose(working);
	}

	if(temp_file)
	{
		fclose(temp_file);
	}

	if((working = fopen(decode_input,"wb")) == NULL)
	{
		Error("Could Not Write Source For Transfer. Error:104.");

		if(working)
		{
			fclose(working);
		}

		if(temp_file)
		{
			fclose(temp_file);
		}

		unlink(temp_path);
		return 0;
	}

	if((temp_file = fopen(temp_path,"rb")) == NULL)
	{
		Error("Could Not Read Temp File For Transfer. Error:105.");

		if(working)
		{
			fclose(working);
		}

		if(temp_file)
		{
			fclose(temp_file);
		}

		unlink(temp_path);
		return 0;
	}

	//----------------------------------------------------------------------

	end_file = 0;

	while (end_file != EOF)
	{
		loopcount++;
		end_file = fscanf(temp_file, "%c", &char_buffer);

		if (end_file != EOF)
		{
			fprintf(working, "%c", char_buffer);
		}
	}

	//----------------------------------------------------------------------


	if(working)
	{
		fclose(working);
	}

	if(temp_file)
	{
		fclose(temp_file);
	}

	unlink(temp_path);
	MessageBox (GetActiveWindow(), "Data Successfully Decrypted." ,TitleCaption, 0);
	return 0;

}
/////////////////////////////////////////////////////////////////////

