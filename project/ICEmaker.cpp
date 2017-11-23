#include <stdio.h>
#include <conio.h>

#include <stdlib.h>
#include <process.h>
#include <ctype.h>

void main()
{

void settimer(void);
void checktimer(void);

char ask;

system("title I.C.E. Setup");
printf("Welcome to the I.C.E Setup\n"
"\nThis setup file will guide you through the setup process."
"\nPlease follow the on-screen instructions to complete the setup.\n\n");
/*------------------------*/ //SHOWS POPUP MESSAGE
system("echo x=msgbox(\"Welcome to the I.C.E Setup\",0+64,\"ICE Setup Notifier\")>msg.vbs");
system("msg *");
/*------------------------*/
system("pause");

clrscr();
printf("\nSETUP PROCESS (1/3) : COPYING REQUIRED FILES....\n\n");
system("If not exist GENice md GENice");
system("If not exist GENice\\ICE md GENice\\ICE");

system("If not exist setup_resources\\ice.dat echo WARNING! ICE.dat file not found!");
system("If not exist setup_resources\\chaabi.dat echo WARNING! chaabi.dat file not found!");
system("If not exist setup_resources\\hice.dat echo WARNING! hICE.dat file not found!");
system("If not exist setup_resources\\p2s.dat echo WARNING! p2s.dat file not found!");

system("If exist setup_resources\\ice.dat copy setup_resources\\ice.dat GENice\\ICE\\ICE.exe");
system("If exist GENice\\ICE\\ICE.exe echo COPIED (1/5) FILES: ICE.EXE");
system("If exist setup_resources\\chaabi.dat copy setup_resources\\chaabi.dat GENice\\ICE\\chaabi.exe");
system("If exist GENice\\ICE\\chaabi.exe echo COPIED (2/5) FILES: CHAABI.EXE");
system("If exist setup_resources\\hice.dat copy setup_resources\\hice.dat GENice\\ICE\\hICE.vbs");
system("If exist GENice\\ICE\\hICE.vbs echo COPIED (3/5) FILES: hICE.VBS");
system("If exist setup_resources\\p2s.dat copy setup_resources\\p2s.dat GENice\\ICE\\patch2start.bat");
system("If exist GENice\\ICE\\patch2start.bat echo COPIED (4/5) FILES: Patch2Start.bat");
system("If exist setup_resources\\upc.dat copy setup_resources\\upc.dat GENice\\ICE\\Unpatcher.bat");
system("If exist GENice\\ICE\\unpatcher.bat echo COPIED (5/5) FILES: Unpatcher.bat");

system("pause");
clrscr();
printf("\nSETUP PROCESS (2/3) : SETTING UP LOGOFF TIMER....\n\n");
printf("\nThe default timer period is 1 hour (3600seconds)."
       "\nDo you wish to change that and enter your own timer period?");

askagain:
printf("\nYOUR OPTION(Y/N):");
ask=getche();

if(toupper(ask)=='N')
{
system("if exist GENice\\ICE\\Datarecord rd/s/q GENice\\ICE\\Datarecord");
system("if not exist GENice\\ICE\\Datarecord md GENice\\ICE\\Datarecord");
}
else if (toupper(ask)=='Y')
{
printf("\n|CUSTOMIZING VALUE OF LOGOFF TIMER|\n");
settimer();
}
else
{
printf ("\nINVALID SELECTION. PLEASE SELECT BETWEEN 'Y' or 'N'.\n");
goto askagain;
}

clrscr();
printf("\nSETUP PROCESS (3/3) : FINISHING UP....\n");
printf("\nPlease copy the generated folder 'ICE' to somewhere convenient in your drive\n");

system("if exist readme.txt del readme.txt");
system("echo Instructions:>>Readme.txt");
system("echo -Keep The main ICE folder somewhere convenient in your harddrive>>Readme.txt");
system("echo -Once placed in the desired path, open it and double click on Patch2start.bat>>Readme.txt");
system("echo -Patch2start.bat activates this program for intended use.>>Readme.txt");
system("echo -Double click on Unpatcher.bat to deactivate it. >>Readme.txt");
system("echo -To change the timer, set the key or other settings, open Chaabi.exe>>Readme.txt");
system("copy readme.txt GENice\\ICE\\README.TXT");

system("start GENice");

/*------------------------*/ //SHOWS POPUP MESSAGE
system("echo x=msgbox(\"Please copy the generated folder 'ICE' to somewhere convenient in your harddrive\",0+64,\"ICE Setup Notifier\")>msg.vbs");
system("msg *");
/*------------------------*/
system("start Readme.txt");

printf("\n\n\PRESS OK TO EXIT SETUP\n\n");

/*------------------------*/ //SHOWS POPUP MESSAGE
system("echo x=msgbox(\"SETUP HAS COMPLETED SUCCESSFULLY!\",0+64,\"ICE Setup Notifier\")>msg.vbs");
system("start/w msg");
/*------------------------*/
system("if exist readme.txt del readme.txt");
system("if exist msg.vbs del msg.vbs");

}


void checktimer(void)
{
int timerval;
FILE *tas;
if ((tas=fopen("GENice\\ICE\\Datarecord\\Lentime.txt","r"))==0)
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
   system("if not exist GENice\\ICE\\Datarecord md GENice\\ICE\\Datarecord");
   FILE *tmx;
   tmx=fopen("GENice\\ICE\\Datarecord\\Lentime.txt","w");
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

