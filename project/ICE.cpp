#include <stdio.h>
#include <conio.h>

#include <string.h>
#include <stdlib.h>
#include <dos.h>


#define consttimerval 3600 // Edit this number to change default timer
#define loto 60 //Set a log-off timeout warning message interval
int timerval=consttimerval; //sets default timer value



void main()
{
/*---------------------------*/ //Sets a custom timer value
FILE *tas;
if ((tas=fopen("Datarecord\\Lentime.txt","r"))==0)
	{
   printf("DEFAULT TIME SET!");
   }
else
	fscanf(tas,"%d",&timerval);
fclose(tas);

//This prevents the user from setting timervalue below 10 minutes.
if (timerval<600)
{
timerval=600;
}
/*-----------------------------*/



void mid(char x[], int i, int j);
int change(char x[]);
int diffx(int a, int b, int c, int d, int e, int f);
void errormsg(int errorcode);
void verify(void);
void winmsgbox(int choice);

FILE *temp;

char time_a1[12],hrs_a1[12],min_a1[12],sec_a1[12];
char date_a1[15],yrs_a1[15],mth_a1[15],day_a1[15];
char time_a2[12],hrs_a2[12],min_a2[12],sec_a2[12];
char date_a2[15],yrs_a2[15],mth_a2[15],day_a2[15];
char time_a3[12],hrs_a3[12],min_a3[12],sec_a3[12];
char date_a3[15],yrs_a3[15],mth_a3[15],day_a3[15];

int nhrs_a1,nmin_a1,nsec_a1;
int nyrs_a1,nmth_a1,nday_a1;
int nhrs_a2,nmin_a2,nsec_a2;
int nyrs_a2,nmth_a2,nday_a2;
int nhrs_a3,nmin_a3,nsec_a3;
int nyrs_a3,nmth_a3,nday_a3;

int bln=0,timebln=0,diffa1a2=0,time_remains=0;


//S1: Section that checks the existence of file folder initially & then assigns a boolean value
/*--------------------------------*/  //S1:START

system("If exist Datarecord\\Date_a1.txt echo 01>Datarecord\\bln.txt"); //If file exists, boolean value 1 is set to a certain file

system("If not exist Datarecord\\Date_a1.txt md Datarecord");
system("If not exist Datarecord\\Date_a1.txt echo 00>Datarecord\\bln.txt"); //If file does not exist, boolean value 0 is set to a certain file

//Extracting boolean value from file
if((temp=fopen("Datarecord\\bln.txt","r"))==0)
	{
   printf("FILE OPEN ERROR!\n");
   errormsg(1);
   }
else
	fscanf(temp,"%d",&bln);
fclose(temp);

/*-----------------------------*/ //S1: STOP


//S2:Start normally or compare time depending upon boolean value
/*--------------------------------*/ //S2:START

printf("fileboolean=%d\n",bln);
if(bln==1)
goto timechecker;
else
goto start;

/*--------------------------------*/ //S2:STOP


//S3:Logs the initialization time and date every time
/*--------------------------------*/ //S3:START
start:

 	clrscr();
   printf("Logging Program start time and date\n");
   system("if not exist Datarecord md Datarecord");
   system("echo %time%>DataRecord\\Time_a1.txt");  //initialization time
   system("echo %date%>DataRecord\\Date_a1.txt");  //initialization date

/*--------------------------------*/ //S3:STOP


//S4: A section to extract time log info from file
/*-------------------------------------------------*/ //S4:START

//FOR TIME:

		if((temp=fopen("Datarecord\\Time_a1.txt","r"))==0)
      			{
					printf("FILE OPEN ERROR!\n");
               errormsg(2);
               }
		else
					fscanf(temp,"%[^\n]",time_a1);
		fclose(temp);

	//Creating a copy of the original time log
	strcpy(hrs_a1,time_a1);
	strcpy(min_a1,time_a1);
	strcpy(sec_a1,time_a1);

	//Extracts required string.
	mid(hrs_a1, 0, 2);
   mid(min_a1, 3, 2);
   mid(sec_a1, 6, 2);

	//Changes Extracted Strings to Numbers
	nhrs_a1=change(hrs_a1);
	nmin_a1=change(min_a1);
	nsec_a1=change(sec_a1);

//FOR DATE:

		if((temp=fopen("Datarecord\\Date_a1.txt","r"))==0)
					{
               printf("FILE OPEN ERROR!\n");
               errormsg(3);
               }
		else
					fscanf(temp,"%[^\n]",date_a1);
		fclose(temp);

	//Creating a copy of the original time log
	strcpy(yrs_a1,date_a1);
	strcpy(mth_a1,date_a1);
	strcpy(day_a1,date_a1);

	//Extracts required string.
	mid(yrs_a1, 10, 4);
   mid(mth_a1, 4, 2);
   mid(day_a1, 7, 2);

	//Changes Extracted Strings to Numbers
	nyrs_a1=change(yrs_a1);
	nmth_a1=change(mth_a1);
	nday_a1=change(day_a1);

// Here nhrs_a1, nmin_a1, nsec_a1 are time variables for a1
// Here nyrs_a1, nmth_a1, nday_a1 are date variables for a1
/*-------------------------------------------------*/ //S4:STOP





//S5: Section to log date and time in next file for comparision
/*---------------------------------*/ //S5:START

ptl:

   system("echo %time%>DataRecord\\Time_a2.txt");  //running time log
   system("echo %date%>DataRecord\\Date_a2.txt");  //running date log

   	if((temp=fopen("Datarecord\\Time_a2.txt","r"))==0)
      			{
					printf("FILE OPEN ERROR!\n");
               errormsg(4);
               }
		else
					fscanf(temp,"%[^\n]",time_a2);
		fclose(temp);

      if((temp=fopen("Datarecord\\Date_a2.txt","r"))==0)
					{
               printf("FILE OPEN ERROR!\n");
               errormsg(5);
               }
		else
					fscanf(temp,"%[^\n]",date_a2);
		fclose(temp);

//Creating a copy of the original log
	strcpy(hrs_a2,time_a2);
	strcpy(min_a2,time_a2);
	strcpy(sec_a2,time_a2);
   strcpy(yrs_a2,date_a2);
	strcpy(mth_a2,date_a2);
	strcpy(day_a2,date_a2);

	//Extracts required string.
	mid(hrs_a2, 0, 2);
   mid(min_a2, 3, 2);
   mid(sec_a2, 6, 2);
   mid(yrs_a2, 10, 4);
   mid(mth_a2, 4, 2);
   mid(day_a2, 7, 2);

	//Changes Extracted Strings to Numbers
	nhrs_a2=change(hrs_a2);
	nmin_a2=change(min_a2);
	nsec_a2=change(sec_a2);
   nyrs_a2=change(yrs_a2);
	nmth_a2=change(mth_a2);
	nday_a2=change(day_a2);

diffa1a2=diffx(nhrs_a2,nmin_a2,nsec_a2,nhrs_a1,nmin_a1,nsec_a1);

if (diffa1a2<timerval)
{
printf("ELAPSED TIME:%d "
		 " TOTAL TIME:%d "
       " TIME REMAINING:%d\n",diffa1a2,timerval,timerval-diffa1a2);
sleep(5);
		goto ptl;   //loop this sequence of recording a2 values
}
else
		printf("Loop Complete\n");
/*---------------------------------*/ //S5:STOP
goto endpoint;




//S6: This segment starts only if the program starts a second time in a single day. or if the datarecord folder has some previously undeleted data
/*-----------------------*/ //S6: START

	timechecker:

   system("echo %time%>DataRecord\\Time_a3.txt");  //restart time log
   system("echo %date%>DataRecord\\Date_a3.txt");  //restart date log

   	if((temp=fopen("Datarecord\\Time_a2.txt","r"))==0)
      					{
							printf("FILE OPEN ERROR!\n");
                     errormsg(4);
                     }
					else
							fscanf(temp,"%[^\n]",time_a2);
					fclose(temp);

      if((temp=fopen("Datarecord\\Time_a3.txt","r"))==0)
                     {
							printf("FILE OPEN ERROR!\n");
                     errormsg(6);
                     }
					else
							fscanf(temp,"%[^\n]",time_a3);
               fclose(temp);

      if((temp=fopen("Datarecord\\Date_a2.txt","r"))==0)
                     {
							printf("FILE OPEN ERROR!\n");
                     errormsg(5);
                     }
					else
							fscanf(temp,"%[^\n]",date_a2);
					fclose(temp);

      if((temp=fopen("Datarecord\\Date_a3.txt","r"))==0)
							{
                     printf("FILE OPEN ERROR!\n");
                     errormsg(7);
                     }
					else
							fscanf(temp,"%[^\n]",date_a3);
					fclose(temp);


//Creating a copy of the original log
	strcpy(hrs_a2,time_a2);
	strcpy(min_a2,time_a2);
	strcpy(sec_a2,time_a2);
   strcpy(yrs_a2,date_a2);
	strcpy(mth_a2,date_a2);
	strcpy(day_a2,date_a2);

   strcpy(hrs_a3,time_a3);
	strcpy(min_a3,time_a3);
	strcpy(sec_a3,time_a3);
   strcpy(yrs_a3,date_a3);
	strcpy(mth_a3,date_a3);
	strcpy(day_a3,date_a3);

	//Extracts required string.
	mid(hrs_a2, 0, 2);
   mid(min_a2, 3, 2);
   mid(sec_a2, 6, 2);
   mid(yrs_a2, 10, 4);
   mid(mth_a2, 4, 2);
   mid(day_a2, 7, 2);

   mid(hrs_a3, 0, 2);
   mid(min_a3, 3, 2);
   mid(sec_a3, 6, 2);
   mid(yrs_a3, 10, 4);
   mid(mth_a3, 4, 2);
   mid(day_a3, 7, 2);

	//Changes Extracted Strings to Numbers
	nhrs_a2=change(hrs_a2);
	nmin_a2=change(min_a2);
	nsec_a2=change(sec_a2);
   nyrs_a2=change(yrs_a2);
	nmth_a2=change(mth_a2);
	nday_a2=change(day_a2);

   nhrs_a3=change(hrs_a3);
	nmin_a3=change(min_a3);
	nsec_a3=change(sec_a3);
   nyrs_a3=change(yrs_a3);
	nmth_a3=change(mth_a3);
	nday_a3=change(day_a3);

// Here nhrs_a2, nmin_a2, nsec_a2 are time variables for a2
// Here nyrs_a2, nmth_a2, nday_a2 are date variables for a2
// Here nhrs_a3, nmin_a3, nsec_a3 are time variables for a3
// Here nyrs_a3, nmth_a3, nday_a3 are date variables for a3
/*-----------------------*/ //S6: STOP



//S7: This segment checks if a day has passed or not. If TRUE, the whole data is cleared or RESET. Then the program restarts itself. If FALSE, the program exits this checking sequence and starts checking if the USER has some time left of his/her alloted time
/*---------------------*/ //S7:START
/*Note: S7 Depends on S6. Keep in same order.*/

if(nyrs_a3>nyrs_a2)
	goto reset;
else
	{
		if(nmth_a3>nmth_a2)
   		goto reset;
   	else
   		{
      		if (nday_a3>nday_a2)
      			goto reset;
      		else
      			goto noaccess;
   		}
	}

/*-----------------------*/ //S7:STOP



//S8: Resets the datafile values if the date changes
/*----------------*/ //S8:START
 		reset:

		system("if exist Datarecord\ del/f Datarecord\\time*.txt ");
		system("if exist Datarecord\ del/f Datarecord\\date*.txt ");
		printf("Status: Datarecord has been cleared! RESET! "); // Status msg
		sleep(2);
		goto start;
/*----------------*/ //S8:STOP



//S9: This section checks if the user has remaining time left after it is confirmed that the USER is still operating in the same day.
/*---------------*/ //S9:START
	noaccess:
	printf("No RESET condition."
   		 "\nIt is the same day."
          "\nChecking remaining time if available...\n");



   	if((temp=fopen("Datarecord\\Time_a1.txt","r"))==0)
      					{
							printf("FILE OPEN ERROR!\n");
                     errormsg(2);
                     }
					else
							fscanf(temp,"%[^\n]",time_a1);
					fclose(temp);

      if((temp=fopen("Datarecord\\Time_a2.txt","r"))==0)
							{
                     printf("FILE OPEN ERROR!\n");
                     errormsg(4);
                     }
					else
							fscanf(temp,"%[^\n]",time_a2);
               fclose(temp);

      if((temp=fopen("Datarecord\\Date_a1.txt","r"))==0)
							{
                     printf("FILE OPEN ERROR!\n");
                     errormsg(3);
                     }
					else
							fscanf(temp,"%[^\n]",date_a1);
					fclose(temp);

      if((temp=fopen("Datarecord\\Date_a2.txt","r"))==0)
							{
                     printf("FILE OPEN ERROR!\n");
                     errormsg(5);
                     }
					else
							fscanf(temp,"%[^\n]",date_a2);
					fclose(temp);


//Creating a copy of the original log
	strcpy(hrs_a2,time_a2);
	strcpy(min_a2,time_a2);
	strcpy(sec_a2,time_a2);
   strcpy(yrs_a2,date_a2);
	strcpy(mth_a2,date_a2);
	strcpy(day_a2,date_a2);

   strcpy(hrs_a1,time_a1);
	strcpy(min_a1,time_a1);
	strcpy(sec_a1,time_a1);
   strcpy(yrs_a1,date_a1);
	strcpy(mth_a1,date_a1);
	strcpy(day_a1,date_a1);

	//Extracts required string.
	mid(hrs_a2, 0, 2);
   mid(min_a2, 3, 2);
   mid(sec_a2, 6, 2);
   mid(yrs_a2, 10, 4);
   mid(mth_a2, 4, 2);
   mid(day_a2, 7, 2);

   mid(hrs_a1, 0, 2);
   mid(min_a1, 3, 2);
   mid(sec_a1, 6, 2);
   mid(yrs_a1, 10, 4);
   mid(mth_a1, 4, 2);
   mid(day_a1, 7, 2);

	//Changes Extracted Strings to Numbers
	nhrs_a2=change(hrs_a2);
	nmin_a2=change(min_a2);
	nsec_a2=change(sec_a2);
   nyrs_a2=change(yrs_a2);
	nmth_a2=change(mth_a2);
	nday_a2=change(day_a2);

   nhrs_a1=change(hrs_a1);
	nmin_a1=change(min_a1);
	nsec_a1=change(sec_a1);
   nyrs_a1=change(yrs_a1);
	nmth_a1=change(mth_a1);
	nday_a1=change(day_a1);

// Here nhrs_a1, nmin_a1, nsec_a1 are time variables for a1
// Here nyrs_a1, nmth_a1, nday_a1 are date variables for a1
// Here nhrs_a2, nmin_a2, nsec_a2 are time variables for a2
// Here nyrs_a2, nmth_a2, nday_a2 are date variables for a2

diffa1a2=diffx(nhrs_a2,nmin_a2,nsec_a2,nhrs_a1,nmin_a1,nsec_a1);

printf("\n a1 HRS:%d MIN: %d SEC: %d\n",nhrs_a1,nmin_a1,nsec_a1);
printf("\n a2 HRS:%d MIN: %d SEC: %d\n",nhrs_a2,nmin_a2,nsec_a2);


	system("If exist Datarecord\\timerem.txt echo 01>Datarecord\\timebln.txt"); //If file exists, boolean value 1 is set to a certain file
	system("If not exist Datarecord\\Date_a1.txt md Datarecord");
	system("If not exist Datarecord\\timebln.txt echo 00>Datarecord/timebln.txt"); //If file does not exist, boolean value 0 is set to a certain file

//Extracting boolean value from file
if((temp=fopen("Datarecord\\timebln.txt","r"))==0)
   {
	printf("FILE OPEN ERROR!\n");
   errormsg(8);
   }
else
	fscanf(temp,"%d",&timebln);
fclose(temp);


/*------------------------------------------------------------*/


	if (timebln==0)
	{
			if (diffa1a2<timerval)
			{
			time_remains=timerval-diffa1a2;

			temp=fopen("Datarecord\\Timerem.txt","w");
			fprintf(temp,"%d",time_remains);
               printf("\nINVOKE POINT A: PROGRAM INITIATES AFTER FIRST INTERRUPTION\n");
			fclose(temp);
         }
   }
   else if (timebln==1)
	{

			if((temp=fopen("Datarecord\\Timerem.txt","r"))==0)
         {
         printf("FILE OPEN ERROR!");
         errormsg(9);
         }
         else
         {
					fscanf(temp,"%d",&time_remains);
               		printf("\nINVOKE POINT B: PROGRAM INITIATES AFTER SECOND OR MULTIPLE INTERRUPTION\n");
               diffa1a2=timerval-time_remains;
			 }
          fclose(temp);
   }

				printf("\n|TIMEBOOLEAN=%d |"
						 " |SERVICE USED TIME=%d |"
               	 " |TIME REMAINING=%d |",timebln,diffa1a2,time_remains);
            diffa1a2=diffa1a2+5;
			

/*------------------------------------------------------------*/

        while(time_remains>0)
			{
				sleep(5);

 		    /*------------*/
   	  	time_remains=time_remains-5;

					temp=fopen("Datarecord\\Timerem.txt","w");
					fprintf(temp,"%d",time_remains);
         		fclose(temp);

			printf("\n|TIMEBOOLEAN=%d |"
					 " |SERVICE USED TIME=%d |"
                " |TIME REMAINING=%d |",timebln,diffa1a2,time_remains);
                       diffa1a2=diffa1a2+5;
			/*------------*/

			};

/*------------------------------------------------------------*/



goto endpoint;
/*---------------*/ //S9:STOP



endpoint:

verify();

				printf("\n\nTERMINATING.."
            "\n\nThe original program will Shutdown the"
            " computer at this point");
            sleep(loto);
            system("shutdown/f -l");

}








/*-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-*/
//USER DEFINED FUNCTIONS BELOW THIS POINT
/*-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-*/


//This function converts string to number
int change(char x[])
{
int i,l=strlen(x),asc=0;
		for (i=0;i<l;i++)
			{
					if((int)x[i]>47 && (int)x[i]<58)
					asc=asc*10+((int)x[i]-48);
			}
return(asc);
}


//This function extracts substring
void mid(char x[], int i, int j)
{
	int l = strlen(x);
	char naya[15];
	int k=0;
	do{
		naya[k]=x[i+k];
		k++;
	}while(k<j);
	do{
		naya[k]=NULL;
		k++;
	}while(k<=l);
	strcpy(x,naya);
}






int diffx(int a, int b, int c, int d, int e, int f)
{
int diff;
diff=((a-d)*3600)+((b-e)*60)+(c-f);
return(diff);
}


void errormsg(int errorcode)
{
/*--------------------------------------------------*/ //ERRORLOGGING:START

FILE *temp;
char msg[150],time_e1[12], date_e1[15];


//BLOCK1: Extracts Date and time information from system
/*--x-x-x-x-x-x-x-x-xx-*/ //Block1:START
	system("if not exist Datarecord md Datarecord");
   system("echo %time%>DataRecord\\Time_e1.txt");  //initialization time
   system("echo %date%>DataRecord\\Date_e1.txt");  //initialization date
if((temp=fopen("Datarecord\\Time_e1.txt","r"))==0)
						printf("FILE OPEN ERROR!\n");
					else
						fscanf(temp,"%[^\n]",time_e1);
			fclose(temp);

if((temp=fopen("Datarecord\\Date_e1.txt","r"))==0)
						printf("FILE OPEN ERROR!\n");
					else
						fscanf(temp,"%[^\n]",date_e1);
			fclose(temp);
/*--x-x-x-x-x-x-x-x-xx-*/ //Block1:STOP


  switch(errorcode)
  {
  case 1:
  strcpy(msg,"||Error Type 1: The fileboolean 'bln.txt' was not found or corrupt!||");
  break;

  case 2:
  strcpy(msg,"||Error Type 2: The file Time_a1.txt was not found or corrupt!||");
  break;

  case 3:
  strcpy(msg,"||Error Type 3: The file Date_a1.txt was not found or corrupt!||");
  break;

  case 4:
  strcpy(msg,"||Error Type 4: The file Time_a2.txt was not found or corrupt!||");
  break;

  case 5:
  strcpy(msg,"||Error Type 5: The file Date_a2.txt was not found or corrupt!||");
  break;

  case 6:
  strcpy(msg,"||Error Type 6: The file Time_a3.txt was not found or corrupt!||");
  break;

  case 7:
  strcpy(msg,"||Error Type 7: The file Date_a3.txt was not found or corrupt!||");
  break;

  case 8:
  strcpy(msg,"||Error Type 8: The time boolean file timebln.txt was not found or corrupt!||");
  break;

  case 9:
  strcpy(msg,"||Error Type 9: The file timerem.txt was not found or corrupt!||");
  break;

  default:
  strcpy(msg,"||Error Type 0: Unexpected ERROR encountered!||");
  break;
  }

puts(msg);
system("If not exist Datarecord\\Error_Log md Datarecord\\Error_Log");

	temp=fopen("Datarecord\\Error_Log\\ERL.txt","w");
   fprintf(temp,"Date Log: %s\n",date_e1);
	fprintf(temp,"Time Log: %s\n",time_e1);
   fprintf(temp,"\nType of Error:\n%s\n",msg);
   fclose(temp);

system("If exist Datarecord\\Error_Log\\ERL.txt (ren Datarecord\\Error_Log\\ERL.txt Error%random%.txt)");


/*--------------------------------------------------*/ //ERRORLOGGING:STOP
}



//FILECHECKING START
void verify(void)
{
void winmsgbox(int choice);
printf("\n\nChecking Chaabi...");
FILE *temp;
				char msg1[9],msg2[2],msg3[15],msg4[22],msg[50],mx[25];
				int i,f1=0,f2=0,foundx=0;
				system("if exist DATARECORD\\cdata.txt del DATARECORD\\cdata.txt");
				system("if exist DATARECORD\\test.txt del DATARECORD\\test.txt");
				  		for(i=65;i<91;i++)
		  					{
					 				temp=fopen("Datarecord\\TEST.txt","w");
				  				   fprintf(temp,"%c \n",i);
 					 				fclose(temp);
                     /*-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-*/
                           if((temp=fopen("Datarecord\\TEST.txt","r"))==0)
                           	printf("FILE OPENING ERROR!");
                           else
				  				   	fscanf(temp,"%s",msg2);
                           fclose(temp);
                     /*-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-*/
								strcpy(msg," "); //RESET THE CATENATION
                        strcpy(msg1,"if exist ");
							 	   strcat(msg,msg1);
			   				   strcat(msg,msg2);
                        strcpy(msg3,":\\\\ky.ice echo ");
   								strcat(msg,msg3);
									strcat(msg,msg2);
                        strcpy(msg4,">Datarecord\\cdata.txt");
								   strcat(msg,msg4);
						//puts(msg);
         			      system(msg);
	  			          }

									if((temp=fopen("Datarecord\\cdata.txt","r"))==0)
										printf("\nNo USB device detected with KEY");
                           else
                           {
				  				   	fscanf(temp,"%s",msg2);
                           printf("\n\n KEY detected in drive %s\n\n NOW VERIFYING MATCH..: ",msg2);
                           foundx=1;
                           }
                           fclose(temp);


				/*-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx*/
					if((temp=fopen("Datarecord\\ky.ice","r"))==0)
						printf("\nNo KEY Detected in DATARECORD \nPlease Generate a New one!");
				   else
				   	fscanf(temp,"%d",&f1);
				   fclose(temp);

				 /*-----------------------*/
				   strcpy(mx,msg2);
				   strcat(mx,":\\\\ky.ice");
				 /*-----------------------*/

   				if((temp=fopen(mx,"r"))==0)
						printf("\nNo KEY Detected in USB Drive!"
				      "\nPlease Insert a valid Memory Stick.");
				   else
				   	fscanf(temp,"%d",&f2);
				   fclose(temp);


				   					if(f1==f2 && foundx==1)
									   {
    	      				            printf("KEY MATCHED!"
                                    "\nSo, automatic Shutdown process will Abort");
                                    winmsgbox(1);
                                    abort(); //ABORT SHUTDOWN at KEY MATCH EVENT
									   }
                              else if(foundx==1 && f1!=f2)
                              {
                              foundx=0;
												printf("\nKEY MISMATCHED!"
                                    "\nYou must be using an older key");
                                    winmsgbox(2);
                              }
                              else if (foundx==0)
                              {
                              winmsgbox(3);
                              }

/*-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx*/
} //FILECHECKING STOP


//WINDOWS MESSAGE BOX START
/*----------------------------------------------------------------------*/
void winmsgbox(int choice)
{
FILE *temp;
char msg[200];
flushall();
int i=0;
for (i=0;i<200;i++)
{
msg[i]=' ';
}


switch(choice)
{
	case 1:
   strcpy(msg,"msgbox (\"A valid key was Detected! | STATUS: UNLOCKED\"&  chr(13) &\" \"& chr(13)&\"Remove it and logoff to re-initiate the I.C.E. LOCK anytime \")");
   break;

   case 2:
	strcpy(msg,"msgbox (\"An INVALID key was detected. You must be using an older key\"&  chr(13) &\" \"& chr(13)&\"This computer will log off in a few minutes \")");
   break;

	case 3:
	strcpy(msg,"msgbox (\"The time limit has finished \"&  chr(13) &\"Please save any open documents or files \"& chr(13)&\"This computer will log off in one minute \")");
   break;

   default:
   strcpy(msg,"msgbox(\"UNEXPECTED ERROR!\") ");
   break;
}

   system("if not exist Datarecord md Datarecord");

   temp=fopen("Datarecord\\usrmsg.vbs","w");
   fprintf(temp,"%s",msg);
   fclose(temp);

 system("start Datarecord\\usrmsg.vbs");
}
/*----------------------------------------------------------------------*/
//WINDOWS MESSAGE BOX STOP