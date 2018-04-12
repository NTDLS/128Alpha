FILE *first, *temp;
char *temp_path;
int end_file = 0;
char char_buffer;
int loopcount = 0;
char *header;
int incode(char *, char *);

////////////////////////////////////////////////////////////////////////

int incode(char *working, char *input_key)
{
	//----------------------------------------------------------------------

	if(first)
	{
		fclose(first);
	}

	if(temp)
	{
		fclose(temp);
	}

	temp_path = 0;
	end_file = 0;
	char_buffer = 0;
	header = 0;
	loopcount = 0;

	//----------------------------------------------------------------------

	temp_path = calloc(100, sizeof(char));
	strcat(temp_path, Get_TempDirectory());
	strcat(temp_path, "Data.Secure");

	if((first = fopen(working,"rb")) == NULL)
	{
		Error("Could Not Open Source For Read. Error:106.");
		if(first)
		{
			fclose(first);
		}
		if(temp)
		{
			fclose(temp);
		}
		return 0;

	}
	if((temp = fopen(temp_path,"wb")) == NULL)
	{
		Error("Could Not Open Temp File For Write. Error:107.");
		if(first)
		{
			fclose(first);
		}

		if(temp)
		{
			fclose(temp);
		}

		return 0;
	}

	/*/(File Printing Start)/*/
	//----------------------------------------------------------------------
	/*/ Print Header, Key Length & Key /*/

	fprintf(temp,"Åמדעשנפוה‏");

	if(strlen(input_key) < 10)
	{
		fprintf(temp,"0");
	}

	fprintf(temp,"%d",strlen(input_key));
	fprintf(temp,"~%s",input_key);

	/*/Write Working File To Temporary Directory And Close Files/*/

	end_file = 0;

	header = calloc(100, sizeof(char));

	while (end_file != EOF)
	{
		end_file = fscanf(first, "%c", &char_buffer);

		if (end_file != EOF)
		{
			if(loopcount < 11)
			{
				loopcount++;
				strcat(header,&char_buffer);
			}

			if(loopcount == 10)
			{
				loopcount++;

            	if(strcmp("Encrypted~",header) == 0)
				{
					MessageBox (GetActiveWindow(), "Source File Already Encrypted." , TitleCaption, 0);

					if(first)
					{
						fclose(first);
					}

					if(temp)
					{
						fclose(temp);
					}

					unlink(temp_path);
					return 0;
				}

			}
			fprintf(temp, "%c", char_buffer);
		}
	}

	if(first)
	{
		fclose(first);
	}

	if(temp)
	{
		fclose(temp);
	}

	/*/Reset EOF. Open Temp As Read, & First As Write Then Incode From
	Temp File To Working File & Close File/*/

	end_file = 0;

	if((first = fopen(working,"wb")) == NULL)
	{
    	Error("Could Not Write Source For Transfer. Error:108.");

		if(first)
		{
			fclose(first);
		}

		if(temp)
		{
			fclose(temp);
		}

		unlink(temp_path);
		return 0;

	}

	if((temp = fopen(temp_path,"rb")) == NULL)
	{
		Error("Could Not Read Temp File For Transfer. Error:109.");

		if(first)
		{
			fclose(first);
		}

		if(temp)
		{
			fclose(temp);
		}

		unlink(temp_path);
		return 0;

	}

	while (end_file != EOF)
	{
		end_file = fscanf(temp, "%c", &char_buffer);

		if (end_file != EOF)
		{
			char_buffer = char_buffer + 128;
			fprintf(first, "%c", char_buffer);
		}

	}


	if(first)
	{
		fclose(first);
	}

	if(temp)
	{
		fclose(temp);
	}

	unlink(temp_path);
	MessageBox (GetActiveWindow(), "Data Successfully Encrypted." , TitleCaption, 0);
	//----------------------------------------------------------------------r
	/*/(File Printing End)/*/

	return 0;
}

