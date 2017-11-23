#include <stdio.h>
#include <conio.h>

#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <process.h>
#include <ctype.h>

void winmsgbox(int choice);

void main()
{
void genkey(void);
void killkey(void);
void verify(void);
void settimer(void);
void checktimer(void);

mm:
clrscr();
int choice=0;

system("title CHAABI - module of I.C.E.");
printf("\nCHAABI Main Menu"
		"\n\n1.Generate a KEY"
      "\n2.Invalidate Existing KEY"
      "\n3.Check your Key Pair/Match"
      "\n4.Customize the Timer Value for automatic Logoff"
      "\n5.Check the current value of timer"
      "\n6.Exit this program"
      "\n\nSELECT OPTION(1/2/3/4/5/6): "
);

scanf("%d",&choice);

switch (choice)
		{
      	case 1:
            genkey();
            getch();
         goto mm;

         case 2:
         	killkey();
            getch();
         goto mm;

         case 3:
         	verify();
            getch();
         goto mm;

         case 4:
         	settimer();
            getch();
         goto mm;

         case 5:
         	checktimer();
            getch();
         goto mm;
            
         case 6:
         printf("\nPress ANY KEY to terminate this program");
         getch();
         abort();

         default:
         printf("\n\nSorry, your entry cannot be accepted."
         "\nPlease input again(1/2/3/4/5/6)");
         sleep(2);
         goto mm;
      }

}


void checktimer(void)
{
int timerval;
FILE *tas;
if ((tas=fopen("Datarecord\\Lentime.txt","r"))==0)
	{
   printf("\n\nCurrently,DEFAULT TIME=1hour ie.3600s is SET!\n\n");
   }
else
   {
	fscanf(tas,"%d",&timerval);
   printf ("\n\nThe current timer value is : %d seconds\n\n",timerval);
   }
fclose(tas);
}

void settimer(void)
{
int h,m,s;
char opt;
printf("\nWelcome to the timer value customization module!\n|This module sets up a custom timer for the login controller|\n");

checktimer(); // To KNOW current timer value

reask:
printf("\n\nPlease enter the required time in \nhours, minutes and seconds respectively:\n");

		printf("HOURS:");
		scanf("%d",&h);

minask:
		printf("MINUTES:");
		scanf("%d",&m);
if (m>59 || m<0)
{
printf("INVALID ENTRY!, Value must be positive integer less than 60.\n");
goto minask;
}

secask:
		printf("SECONDS:");
		scanf("%d",&s);
if (s>59 || s<0)
{
printf("INVALID ENTRY!, Value must be positive integer less than 60.\n");
goto secask;
}

printf("\n\n The timer is about to be set at: \n%dhours:%dminutes:%dseconds i.e. %d seconds in total\n\n Do you want to save this change or input again?\n Press 'S' to save and proceed or 'R' to reset the changes: ",h,m,s,h*60*60+m*60+s);
optask:
printf("\nYOUR OPTION(R/S):");
opt=getche();
if (toupper(opt)=='R')
	goto reask;
else if (toupper(opt)=='S')
	{
   /*SETTING UP TIMER*/
   system("if not exist Datarecord md Datarecord");
   FILE *tmx;
   tmx=fopen("Datarecord\\Lentime.txt","w");
   fprintf(tmx,"%d",h*3600+m*60+s);
   fclose(tmx);

   printf("\n\nTimer is set at: %dhours:%dminutes:%dseconds i.e. %d seconds in total \n",h,m,s,h*3600+m*60+s);
	}
else
	{
   printf("\n\nINVALID INPUT. Please choose between 'R' or 'S'\n");
   goto optask;
   }
}

void genkey(void)
{

FILE *temp;
long int KEY;

 system("if not exist Datarecord md Datarecord");
 system("echo %random%>DataRecord\\ky.ice");  //initialization time

   if((temp=fopen("Datarecord\\ky.ice","r"))==0)
						printf("FILE OPEN ERROR!\n");
					else
						fscanf(temp,"%ld",&KEY);
			fclose(temp);

   system("if not exist Datarecord\\Temp md Datarecord\\Temp");
   system("copy Datarecord\\ky.ice Datarecord\\Temp\\ky.ice");
   clrscr();
   system("start/w Datarecord\\Temp\\");


printf("\nA KEY has been generated"
		"\nPlease copy ky.ice patch file"
      "\ninto root path of a memory stick"
      "\nor pendrive");
      sleep(1);winmsgbox(1);


}


void killkey(void)
{
 system("if not exist Datarecord md Datarecord");
 system("if exist Datarecord\\ky.ice del/q/f/s Datarecord\\ky.ice ");
 system("if exist Datarecord\\Temp rd Datarecord\\Temp");
 clrscr();
 printf("The previous KEY has been invalidated"
 "\nIt will no longer work!"
 "\n\nThere is currently no KEY assigned"
 "\nPlease generate a new KEY on the next screen."
 );

 winmsgbox(2);

}

void winmsgbox(int choice)
{
FILE *temp;
char msg[200];

switch(choice)
{
	case 1:
   strcpy(msg,"msgbox (\"A KEY has been generated. \"&  chr(13) &\" \"& chr(13)&\"Please copy 'ky.ice' file into root path of a memory stick \")");
   break;

	case 2:
	strcpy(msg,"msgbox (\"The previous KEY has been invalidated. It will no longer work! \"&  chr(13) &\" \"& chr(13)&\"Please generate a new KEY from CHAABI - Main Menu \")");
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


void verify(void)
{
printf("Checking......");
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
										printf("\nNo KEY Detected in Datarecord! \nPlease run Chaabi application to create one!\n");
                           else
                           {
				  				   	fscanf(temp,"%s",msg2);
                           printf("KEY detected in drive %s\n\n NOW VERIFYING MATCH..: ",msg2);
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
                                    "\nThis KEY can be used to avoid shutting down");
									   }
                              else if(foundx==1 && f1!=f2)
                              {
                              foundx=0;
                                    printf("KEY MISMATCHED!"
                                    "\nYou must be using an older key");
                              }

/*-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx-xx*/
}
