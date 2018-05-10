		 /***************************************************/
		 /*            COMPUTER STORE MANAGEMENT            */
		 /*                    SOFTWARE                     */
		 /*                                                 */
		 /*PROGRAM TO MANAGE PURCHASE OF HARDWARE COMPONENTS*/
		 /* AND NEW BRANDED PCS GIVE ANNUAL MAINTAINENCE    */
		 /*					     CONTRACT                     */
		 /*               _________          _____          */
		 /*              |         |        |-----|         */
		 /*              |   C++   |        |-----|         */
		 /*              |         |        | ___ |         */
		 /*              |_________|        |     |         */
		 /*           _________________     |  �  |         */
		 /*          |                 |    |_____|         */
		 /*          |_________________|                    */
		 /***************************************************/


#include<conio.h>              // FOR CLRSCR(),GETCH(),GOTOXY(),TEXTCOLOR()
#include<graphics.h>           // FOR CIRCLE(),RECTANGLE(),SETCOLOR(),BAR3D()
#include<stdio.h>              // FOR PUTS(),GETS(),REMOVE(),RENAME()
#include<dos.h>                // FOR DELAY(),SOUND()
#include<string.h>             // FOR STRCMPI(),STRLEN()
#include<fstream.h>            // FOR HANDLING FILES AND STREAM FUNCTIONS
#include<stdlib.h>             // FOR RANDOM() FUNCTION



		 /***************************************************/
		 /*    STRUCTURE DEFINITION FOR DATE STRUCTURE      */
		 /***************************************************/

struct d
{
			short int dd,mm;
			int yy;
}due;

struct date current;              //TO DECLARE OBJECT OF DATE CLASS TO OBTAIN THE CURRENT SYSTEM DATE (A CLASS DEFINED IN DOS.H)
struct  time ti;                  //TO DECLARE OBJECT OF TIME CLASS TO OBTAIN THE CURRENT SYSTEM TIME (A CLASS DEFINED IN DOS.H)

int check=0,found=0;


		 /************************************************************/
		 /* FUNCTION DEFINITION TO DRAW LINES, DISPLAY DATE AND TIME */
		 /************************************************************/


/*THE FUNCTION USES OBJECTS OF DATE AND TIME CLASS TO DISPLAY CURRENT
  SYSTEM DATE AND TIME USING getdate() and gettime() RESPECTIVELY.THE
  FUNTION gotoxy() IS USED THE SET THE COORDIANTES WHILE DISPLAYING
  TIME/DATE OR FOR DRAWING LINES */

void mline(void)
 {
	 gotoxy(62,3);                     //TO SET THE CURSOR POSITION
	 gettime(&ti);                     //TO GET THE CURRENT TIME
	 printf("Time:%2d:%02d:%02d.%02d\n",ti.ti_hour, ti.ti_min, ti.ti_sec, ti.ti_hund);
	 gotoxy(2,3);
	 getdate(&current);               //TO GET THE CURRENT DATE
	 cprintf("Date: ");               // PRINTS DATE ON THE SCREEN
	 cprintf("%d",current.da_day);
	 cout<<"/";
	 cprintf("%d",current.da_mon);
	 cout<<"/";
	 cprintf("%d",current.da_year);
	 gotoxy(29,1);
	 textcolor(RED);                  // TO SET THE TEXT COLOR AS RED
	 cprintf("   COMPUTER STORE");
	 textcolor(BLUE);
	 for(int i=1;i<80;i++)            // STARTING OF FOR LOOP
	 {
		gotoxy(i,2);
		cprintf("-");
		gotoxy(i,4);
		cprintf("-");
		gotoxy(i,21);
		cprintf("_");
	 }                                // END OF THE FOR LOOP
 }


		 /****************************************************/
		 /* FUNCTION DEFINITION TO DISPLAY STATUS BELOW MENUS*/
		 /****************************************************/

/*THIS FUNCTION WHEN CALLED DISPLAYS THE STATUS OF THE SYSTEM ,i.e, WHEN WAITING
  FOR THE USER'S REPLY. FUNCTION MAINLY USES gotoxy(), textcolor() (FOR SETTING
  A PARTICULAR TEXT COLOUR AND BLINK UTILITY */

void status(void)
{
	gotoxy(20,23);
	textcolor(CYAN+BLINK);      //TO SET COLOR AS CYAN AND MAKE TEXT TO BLINK
	cprintf("STATUS");
	textcolor(RED+BLINK);       //TO SET COLOR AS RED AND MAKE TEXT TO BLINK
	cprintf(" : ");
	textcolor(GREEN+BLINK);
	cprintf("WAITING FOR CHOICE TO BE ENTERED...");
	textcolor(WHITE);          // TO SET THE COLOR OF TEXT AS WHITE
}
								 /* CLASS I - amcmem */

		 /***********************************************************/
		 /* CLASS DEFINITION TO CONTROL FUNCTIONS RELATED TO MEMBERS*/
		 /***********************************************************/

/*THIS CLASS BASICALLY CONTAINS ALL THE VARIABLES AND FUNCTIONS REQUIRED TO
  HANDLE THE member.dat DATABASE AND TO PERFORM ALL MEMBER RELATED OPERATIONS -
  LIKE, CREATING A NEW MEMBER ACCOUNT, DELETING AN EXISTING MEMBER,RENEWING MEMBERSHIP
  OF AN EXISTING MEMBER, MODIFYING INFORMATION OF A MEMBER, SEARCHING A MEMBER,
  LISTING ALL THE MEMBERS,GENERATING A CARD FOR THE USER. */

class amcmem
{ 																	 //PRIVATE MEMBERS
			unsigned long code;
			float amount;
			char name[20];
			d joining;                                //VARIABLE OF STRUCTURE d TO
																	//OBTAIN THE DATE OF JOINING
																	//OF THE MEMBER.
			char address[30];
			long int phoneno;
			d vdate;                                  //VARIABLE OF STRUCTURE d FOR
																	//SAVING DATE TILL WHICH AMC IS
																	//VALID.
			char email[50];

	public:
			amcmem(void)                					// CONSTRUCTOR FUNCTION
			{
				amount=1000.00;
			}
			~amcmem()                  					// DESTRUCTOR FUNCTION
			{}
			char ch;
																	//MEMBER FUNCTIONS
			unsigned long getno();
			void getdata();
			void showdata();
			void add();
			void showall();
			void del();
			void change();
			void search();
			void card();
			void renew();
}mem; 										               // END OF CLASS DEFINITION


		 /************************************************************/
		 /* FUNCTION DEFINITION TO AUTOMATICALLY GENERATE MEMBER CODE*/
		 /************************************************************/

/*THIS FUNCTION STARTS READING ALL RECORDS OF THE DATABASE "members.dat" TILL
  THE  END OF THE FILE. IT THEN AUTOMATICALLY PRODUCES THE MEMBERSHIP CODE
  BY INCREMENTING THE LAST RECORD'S CODE BY 1. */

unsigned long amcmem::getno()
{
			 fstream fin;
			 fin.open("member.dat",ios::in);       /* OPENING THE FILE IN INPUT MODE
																	 TO READ FROM FILE*/
			 int i=1;
			 fin.seekg(0,ios::beg);                 /* TO SET THE POSITION OF FILE POINTER
																	 AT THE 1st RECORD FROM THE BEGINNING*/

			 fin.read((char*)&mem,sizeof(amcmem));  /*READING EACH RECORD FROM FILE ONE BY ONE*/

			 while(!fin.eof())                      // TO DETECT THE END OF THE FILE
			 {
				if(i!=mem.code)
				return i;
				fin.read((char*)&mem,sizeof(amcmem)); //READING FOLLOWING RECORDS FROM FILE
				i++;
			 }
			 fin.close();              				  // CLOSING THE FILE
			 return i;                               //RETURNING THE GENERATED CODE FOR NEXT RECORD.
}

		  /************************************************************/
		  /* FUNCTION DEFINITION TO RENEW MEMBERSHIP OF A MEMBER      */
		  /************************************************************/

/*THIS FUNCTION OPENS THE FILE IN BOTH INPUT AND OUTPUT MODE. IT READS THE
 CODE OF THE MEMBER WHOSE MEMBERSHIP IS TO BE RENEWED FROM THE USER. IT THEN
 SEARCHES FOR THE PARTICULAR RECORD ASSOCIATED WITH THE CODE AND EXTENDS THE
 DATE OF VALIDITY BY 1 YEAR. IT REWRITES THAT DATE TO THE FILE */

void amcmem::renew(void)
{
			 fstream f;                    /*CREATING OBJECT OF FSTREAM CLASS */
			 int fl=0,t;
			 unsigned long c;
			 gotoxy(15,12);
			 x:
			 clrscr();            			//TO CLEAR THE SCREEN
			 cout<<"Please enter the membership code of member whose membership"
				  <<" you want to renew(Enter 0 to exit):";
			 cin>>c;
			 if(c==0)
			 {
			  return;
			 }
			 f.open("member.dat",ios::in|ios::out);  /* OPENING FILE IN INPUT AND
																		OUTPUT MODE FOR READING
																		AND WRITING THE DATE.*/

			 f.seekg(0,ios::beg);                     /* TO SET THE POSITION OF FILE POINTER*/

			 f.read((char*)&mem,sizeof(mem));  			/* READING 1st RECORD FROM THE FILE*/
			 t=f.tellg();
			 while(!f.eof())           					// START OF WHILE LOOP
			 {
				  if(c==mem.code)                      /*COMPARING THE CODE READ FROM THE USER
																	  CODE OF RECORD READ FROM THE FILE */

				  {
					 fl=1;
					 mem.vdate.yy+=1;
																	//SET FILE POINTER TO OVERWRITE RECORD
					 f.seekg(t-sizeof(mem));
					 f.write((char*)&mem,sizeof(mem));  //WRITING IN THE FILE
					 clrscr();          						// CLEAR SCREEN
					 gotoxy(15,12);     						// SET CURSOR POSITION
					 cout<<"\nTHANKYOU FOR RENEWING YOUR RELATIONSHIP WITH US FOR YET ANOTHER YEAR";
					 cout<<"\nPress any key to coninue........";
					 getch();
				  }
				  f.read((char*)&mem,sizeof(mem));  	// READING NEXT RECORD FROM THE FILE
				  t=f.tellg();
			 }

/*TO CHECK IF A WRONG CODE HAS BEEN ENTERED*/
				  if(fl==0)
				  {
						  gotoxy(30,8);
						  cout<<"SORRY !! YOU HAVE ENTERED A WRONG CODE";
						  gotoxy(40,10);
						  cout<<"PLEASE RE-ENTER";
						  gotoxy(25,23);
						  textcolor(CYAN);
						  cprintf("Press any key to continue......");
						  getch();
						  clrscr();  							// CLEAR SCREEN
						  goto x;
				  }
				 f.close();     								// CLOSING OF THE FILE

}
		 /************************************************************/
		 /* FUNCTION DEFINITION TO GET MEMBER RELATED DATA           */
		 /************************************************************/

/*THIS FUNCTION READS MEMBER'S INFORMATION - NAME, ADDRESS,PHONE NO,E-MAIL ID*/

void amcmem::getdata(void)
{
			char c;
			x:
			clrscr();                 // FOR CLEAR SCREEN
			gotoxy(30,8);
			cout<<"      MEMBER'S ENTRY";
			code=getno();
			cout<<"\n\nEnter name: ";
			gets(name);
										  /*AUTOMATICALLY GET DATE OF JOINING*/
			joining.dd=current.da_day;
			joining.mm=current.da_mon;
			joining.yy=current.da_year;
			cout<<"\nEnter member's address: ";
			gets(address);
			cout<<"\nEnter member's phone no.: ";
			cin>>phoneno;
			cout<<"\nEnter member's E-mail I.D.: ";
			gets(email);
													/*AUTOMATICALLY GET VALID TILL DATE*/
			vdate.dd=joining.dd;
			vdate.mm=joining.mm;
			vdate.yy=joining.yy+1;
			cout<<"\n\nConfirmed Information ? (y/n) : ";
			c=getch();
			if(c!='y'&&c!='Y')
			goto x;
}

		 /************************************************************/
		 /* FUNCTION DEFINITION TO DISPLAY MEMBER RELATED DATA       */
		 /************************************************************/

/*THIS FUNCTION DISPLAYS THE DETAILS OF AN INDIVIDUAL MEMBER. THIS FUNCTION IS CALLED
  BY showall().*/

void amcmem::showdata(void)
{
			 clrscr();
			 mline();
			 gotoxy(25,6);
			 textcolor(YELLOW);        // SET THE COLOUR OF TEXT AS YELLOW
			 cprintf("\n        MEMBERSHIP DATA");
			 textcolor(WHITE);         // SET THE COLOR OF TEXT AS WHITE
			 cout<<"\n\n\tMembership code: "<<code;
			 cout<<"\n\n\tName: ";
			 cputs(name);
			 cout<<"\n\n\tDate of joining(dd mm yyyy): "
				 <<joining.dd<<"/"<<joining.mm<<"/"<<joining.yy;
			 cout<<"\n\n\tAddress: ";
			 puts(address);
			 cout<<"\n\n\tPhone no.: "<<phoneno;
			 cout<<"\n\n\tE-mail address: ";
			 cputs(email);
			 cout<<"\n\n\tDATE TILL WHICH THE MEMBERSHIP IS VALID (dd mm yyyy): "<<vdate.dd<<"/"<<vdate.mm<<"/"<<vdate.yy;
			 textcolor(CYAN);
			 gotoxy(25,23);
			 cprintf("Press any key to continue.......");
			 textcolor(WHITE);   	// SET THE COLOR OF TEXT AS WHITE
			 getch();
}

		 /************************************************************/
		 /* FUNCTION DEFINITION TO SIGN UP NEW MEMBER FOR AMC        */
		 /************************************************************/

/*THIS FUNCTION ADDS A NEW MEMBER TO THE STORE. IT CALLS THE getdata() FOR EACH NEW MEMBER
  BEING ADDED. IT THEN IMMEDIATELY DISPLAYS THE ENTERED INFORMATION */

void amcmem::add(void)
{
		  fstream f;
		  mem.getdata();					    		//CALLING FUNCTION TO READ INFORMATION
		  f.open("member.dat",ios::app);         // OPENING THE FILE IN APPEND MODE
		  f.write((char*)&mem,sizeof(amcmem)); // WRITING TO THE FILE
		  clrscr();
		  gotoxy(25,6);
		  textcolor(RED);
		  cprintf("      NEW MEMBERSHIP DETAILS!!!!");
		  cout<<"\n\n\t\tMembership Code is: "<<code;
		  cout<<"\n\n\t\tContract charges are: "<<amount;
		  cout<<"\n\n\t\tValid Till(dd mm yyyy): ";
		  cout<<vdate.dd<<"/"<<vdate.mm<<"/"<<vdate.yy;
		  gotoxy(30,18);
		  textcolor(RED);
		  cprintf("    IMPORTANT!!!");
		  cout<<"\n\n\t\tMembership code should be remembered for future correspondence\n";
		  textcolor(WHITE);
		  f.close();
															 // CLOSING THE FILE
		  textcolor(CYAN);
		  gotoxy(25,23);
		  cprintf("Press any key to continue.......");
		  textcolor(WHITE);
		  getch();
}

		 /************************************************************/
		 /* FUNCTION DEFINITION TO DISPLAY DATA OF ALL THE MEMBERS   */
		 /************************************************************/

/* THIS FUNCTION DISPLAYS ALL THE ENTRIES OF THE member.dat DATABASE. THIS FUNCTION CALLS
	showdata() TO DISPLAY INDIVIDUAL RECORDS */

void amcmem::showall(void)
{
			fstream fi;
			fi.open("member.dat",ios::in); // OPENING THE FILE IN INPUT MODE
			fi.seekg(0,ios::beg);
			fi.read((char*)&mem,sizeof(mem));
													  //TO CHECK IF FILE IS EMPTY
			if((!fi)||(fi.eof()))
			{
			  gotoxy(25,10);
			  textcolor(RED);
			  cprintf("\nSORRY , NO MEMBERS IN RECORD!");
			  gotoxy(25,23);
			  textcolor(CYAN);
			  cprintf("\n\nPress any key to continue......... ");
			  getch();
			  fi.close();
			  return;
			}

			while(!fi.eof())
			{
				mem.showdata();
				fi.read((char*)&mem,sizeof(mem));
			}
			fi.close();
}

		 /************************************************************/
		 /* FUNCTION DEFINITION TO WITHDRAW MEMBERSHIP OF A MEMBER   */
		 /************************************************************/

/*THIS FUNCTION DELETS THE RECORD OF A PARTICULAR MEMBER WHOSE CODE IS ENTERED
  THE FUNCTION PROMPTS TO THE USER ON ENTERING AN INVALID CODE. THIS FUNCTION
  USES A TEMPORARY DATABASE temp.dat AND THEN COPIES THE ENTIRE DATABASE member.dat
  EXCEPT THE RECORD TO BE DELETED. IT THEN RENAMES THE DATABASE temp.dat TO
  member.dat TO RESTORE THE DATABASE */


void amcmem::del(void)
		 { unsigned long c;
			int fl=0;
			fstream fi,fo;
			x:
			clrscr();
			gotoxy(15,12);                   //TO SET CURSOR POSITION
			cout<<"\nEnter the membership code of the member who wants to withdraw ";
			cout<<"\n\t\t\tEnter 0 to exit): ";
			cin>>c;
			if(c==0)
			return;
			fo.open("temp.dat",ios::app);    /*TO OPEN TEMP FILE FOR COPYING RECORDS
														  FROM member.dat*/
			fi.open("member.dat",ios::in);  //TO OPEN MEMBERS FILE FOR READING
			fi.seekg(0,ios::beg);            //TO SET FILE POINTER AT BEGINNING
			fi.read((char*)&mem,sizeof(mem));//TO READ IN OBJECT
			while(!fi.eof())                 //TO DETECT THE END OF FILE
			{
			  if(c==mem.code)
			  fl=1;
			  if(mem.code!=c)
			  fo.write((char*)&mem,sizeof(mem));
			  fi.read((char*)&mem,sizeof(mem));
			}
			fi.close();
			fo.close();
			rename("temp.dat","member.dat"); //TO RENAME TEMP AS MEMBERS
			//TO PROMPT FOR INVALID MEMBER CODE
			if(fl==0)
			{
			  gotoxy(25,6);
			  textcolor(RED);
			  cprintf("\nSORRY !!! INVALID MEMBER CODE");
			  cout<<"\n\n\n\n\t\tReneter.....Press any key to continue...";
			  textcolor(WHITE);
			  getch();
			  clrscr();
			  goto x;
			}
			cout<<"\n\t\t\tThe membership has been withdrawn.";
			gotoxy(25,23);
			textcolor(CYAN);
			cprintf("Press any key to continue......");
			textcolor(WHITE);
			getch();
 }

		 /************************************************************/
		 /* FUNCTION DEFINITION TO MODIFY MEMBER'S DATA              */
		 /************************************************************/

/* THIS FUNCTION ENABLES CHANGES IN THE DETAILS OF THE MEMBER. OPTIONS AVAILABLE
	ARE : CHANGE OF - ADDRESS, PHONE-NO, E-MAIL ADDRESS. */

void amcmem::change(void)
{
			fstream f;
			f.open("member.dat",ios::in|ios::out); //OPENING THE FILE
			int ch,fl=0,t=0;
			unsigned long c;
			do
			{
				 clrscr();
				 mline();             //TO DRAW LINES
				 gotoxy(25,6);
				 textcolor(YELLOW);  //SET THE TEXT COLOR AS YELLOW
				 cprintf("What modifications do you want to do??");
				 cout<<"\n\n\t\t\t\t1.Modify address\n\t\t\t\t2.Modify phone no."
					  <<"\n\t\t\t\t3.Modify email address\n\t\t\t\t4.Go back";
				 cout<<"\n\n\t\t\tEnter the choice(1,2,3,4)    ";
				 status();
				 gotoxy(54,11);
				 cin>>ch;
				 if(ch==1||ch==2||ch==3)
				 { x:
					cout<<"\nEnter code of member whose information you want"
						 <<" to modify (Enter 0 to exit): ";
					cin>>c;
					if(c==0)
					{
					  break;
					}
					f.seekg(0,ios::beg);
					f.read((char*)&mem,sizeof(mem)); // READING FROM FILE
					t=f.tellg();
					while(!f.eof())                 // TO DETECT THE END OF THE FILE
					{
						 if(c==mem.code)
						 {
							fl=1;
							switch(ch)                // START OF SWITCH CASE
							{
								  case 0: ch=4;
											 break;

								  case 1: clrscr();
											cout<<"\nEnter the new address: ";
											gets(mem.address);
																	 //OVERWRITING RECORD
											f.seekg(t-sizeof(mem));
											f.write((char*)&mem,sizeof(mem));
											break;

								  case 2: clrscr();
											cout<<"\nEnter the new phone no.: ";
											cin>>mem.phoneno;
																		//OVERWRITING RECORD
											f.seekg(t-sizeof(mem));
											f.write((char*)&mem,sizeof(mem));
											break;

								 case 3: clrscr();
											cout<<"\nEnter the new e-mail address: ";
											gets(mem.email);
																	 //OVERWRITING RECORD
											f.seekg(t-sizeof(mem));
											f.write((char*)&mem,sizeof(mem));
											break;
								 default:break;
							 }
						  }
						  f.read((char*)&mem,sizeof(mem));
						  t=f.tellg();
						}
						if(fl==0)
						{
						  gotoxy(25,8);
						  clrscr();
						  textcolor(RED);
						  cprintf("SORRY !!! INVALID MEMBERSHIP CODE");
						  cout<<"\n\nReneter.....Press any key to continue...";
						  getch();
						  clrscr();                     // CLEAR SCREEN
						  goto x;
						}
				  }
				 }while(ch!=4);      //END OF WHILE
				 f.close();         // CLOSING THE FILE
				 gotoxy(40,10);     // PLACES THE CURSOR AT DESIRED POSITION
				 textcolor(YELLOW);
				 cprintf("Thank you!!!!!!!!!");
				 textcolor(WHITE);
			}

		 /************************************************************/
		 /* FUNCTION DEFINITION TO SEARCH FOR MEMBER'S DATA          */
		 /************************************************************/

/*THIS FUNCTION DISPLAYS THE MEMBER'S DETAILS ON PROVIDING EITHER OF THE FOLLOWING
  -MEMBER'S NAME, MEMBER'S CODE, MEMBER'S PHONE-NO BY CALLING showdata()
  IN EACH CASE */

void amcmem::search(void)
{
			fstream f;
			int ch;
			unsigned long pno,c;
			char name[40];
			do                      // START OF DO WHILE LOOP
			{
			  int co=0;
			  clrscr();
			  mline();
			  gotoxy(30,8);
			  textcolor(YELLOW);    //SET THE TEXT COLOR AS YELLOW
			  cprintf("SEARCH MENU");
			  cout<<"\n\t\t\t1.Search by name"
					<<"\n\t\t\t2.Search by code"
					<<"\n\t\t\t3.Search by phone no."
					<<"\n\t\t\t4.Exit";
			  cout<<"\n\n\t\t\tEnter your choice   ";
			  status();
			  gotoxy(48,14);
			  cin>>ch;
			  switch(ch)                  // START OF SWITCH CASE
			  {
					  case 1: clrscr();
								 cout<<"\nEnter the name you want to search for: ";
								 gets(name);
								 f.open("member.dat",ios::in);  //OPENING FILE
								 f.seekg(0,ios::beg);
								 f.read((char*)&mem,sizeof(mem));
								 while(!f.eof())   // TO DETECT END OF FILE
								 {                //COMPARE TWO STRINGS
								  if(strcmpi(mem.name,name)==0)
									 {
									  co++;
									  mem.showdata();
									 }
									f.read((char*)&mem,sizeof(mem));
								 }
								 f.close();
								 cout<<"\nNo. of records found="<<co;
								 getch();
								 break;

					 case 2:  clrscr();
								 cout<<"\nEnter the member code you want to search for: ";
								 cin>>c;
								 f.open("member.dat",ios::in);  // OPENING THE FILE
								 f.seekg(0,ios::beg);
								 f.read((char*)&mem,sizeof(mem));
								 while(!f.eof())   // TO DETECT THE END OF THE FILE
								 {
									 if(mem.code==c)
									 {
									  co++;
									  mem.showdata();
									 }
									f.read((char*)&mem,sizeof(mem));
								 }
								 f.close();     // CLOSING THE FILE
								 cout<<"\nNo. of records found="<<co;
								 getch();
								 break;

					 case 3:  clrscr();     // CLEAR SCREEN
								 cout<<"\nEnter the phone no. you want to search for: ";
								 cin>>pno;
								 f.open("member.dat",ios::in);
								 f.seekg(0,ios::beg);
								 f.read((char*)&mem,sizeof(mem));
								 while(!f.eof())
								 {
									if(mem.phoneno==pno)
									{
									  co++;
									  mem.showdata();
									 }
									f.read((char*)&mem,sizeof(mem));
								 }
								 f.close();
								 cout<<"\nNo. of records found="<<co;
								 getch();
								 break;

					  case 4: clrscr();
								 gotoxy(25,23);
								 textcolor(YELLOW);
								 cprintf("Thank you!!!!!!!!");
								 textcolor(WHITE);
								 break;
				  }
				}while(ch!=4);
			f.close();
}

		 /************************************************************/
		 /* FUNCTION DEFINITION TO GENERATE MEMBER'S CARD            */
		 /************************************************************/

/*THIS FUNCTION GENERATES A CARD FOR EACH MEMBER. THIS CONTAINS THE INFORMATION OF THE
  MEMBER AND THE DATE TILL WHICH HIS MEMBERSHIP IS VALID. */

void amcmem::card(void)
{
			unsigned long c;
													/* request auto detection */
			int gdriver = DETECT, gmode;
													/* initialize graphics mode */
			initgraph(&gdriver, &gmode, " ");
			cleardevice();
			gotoxy(11,12);
			cout<<"Enter the membership code for which card is to be generated ";
			gotoxy(31,13);
			cout<<"(Enter 0 to exit): ";
			cin>>c;
			fstream f;
			if(c==0)
			closegraph();
			f.open("member.dat",ios::in);           //OPENING FILE
			f.seekg(0,ios::beg);
			f.read((char*)&mem,sizeof(mem));
			while(!f.eof())
			{
				 if(mem.code==c)
				 {
					cleardevice();     					// CLEAR SCREEN
					setcolor(RED);     					// SET THE COLOR AS RED
																// TO DRAW RECTANGLE
					rectangle(24,32,600,300);
					setcolor(CYAN);
																//TO DISPLAY TEXT AT DESIRED POSITION
					outtextxy(250,48,"COMPUTER");
					outtextxy(325,48,"STORE");
					setcolor(YELLOW);
					outtextxy(280,64,"AMC");
					outtextxy(310,64,"CARD");
					setcolor(BLUE);    					 // SET THE COLOR AS BLUE
					outtextxy(72,98,"NAME");
					rectangle(120,92,550,115);
					outtextxy(50,135,"ADDRESS");
					rectangle(120,124,550,161);
					outtextxy(45,181,"PHONE");
					outtextxy(90,181,"NO");
					rectangle(120,169,260,198);
					outtextxy(275,181,"EMAIL");
					rectangle(325,169,550,198);
					outtextxy(80,235,"Date");
					outtextxy(120,235,"of");
					outtextxy(140,235,"Joining");
					rectangle(82,249,196,276);
					setcolor(13);
					outtextxy(243,235,"MEMBERSHIP");
					outtextxy(335,235,"CODE");
					setcolor(BLUE);
					rectangle(245,249,359,276);
					outtextxy(430,235,"Valid");
					outtextxy(475,235,"Till");
					rectangle(407,249,519,276);
					gotoxy(17,12);
					cout<<mem.phoneno;
					gotoxy(17,7);
					cout<<mem.name;
					gotoxy(17,9);
					cout<<mem.address;
					gotoxy(43,12);
					cout<<email;
					gotoxy(14,17);
					cout<<joining.dd<<"/"<<joining.mm<<"/"<<joining.yy;
					gotoxy(38,17);
					cout<<code;
					gotoxy(55,17);
					cout<<vdate.dd<<"/"<<vdate.mm<<"/"<<vdate.yy;
					setcolor(GREEN);
					outtextxy(200,359,"Press");
					outtextxy(250,359,"any");
					outtextxy(280,359,"key");
					outtextxy(305,359,"to");
					outtextxy(325,359,"continue");
					setcolor(CYAN+BLINK);
				 }
			  f.read((char*)&mem,sizeof(mem));  		// READING FROM FILE
			}
			getch();
			f.close();                         			// CLOSING THE FILE
			closegraph();                      			//CLOSE GRAPHICS MODE
}

/******************END OF DEFINTIONS FOR CLASS amcmem***********************/

								/*CLASS II - hware */

		 /************************************************************/
		 /*CLASS DEFINITION TO CONTROL FUNCTIONS RELATED TO HARDWARE */
		 /************************************************************/

/*THIS CLASS INCLUDES ALL THE NECCESSARY FIELDS AND FUNCTIONS REQUIRED
  TO MAINTAIN THE hard.dat DATABASE. THE FUNCTIONS INCLUDED PERFORM THE
  FOLLOWING - MAINTAINING A STOCK OF HARDWARE COMPONENTS, ADDING HARDWARE
  TO STOCK , DISPLAYING THE LIST OF AVIALABLE HARDARE COMPONENTS */

class hware
{
			char obj[30];
			float price;
			int ccode;                // PRIVATE MEMBERS
			char comp[30];
			char spec[30];
			int no;
	  public:
			hware(void)               // CONSTRUCTOR FUNCTION
			{ ccode=no=1;
			  price=0;
			}
			~hware()                  // DESTRUCTOR FUNCTION
			{ }
			void showall(void);
			void get(void);
			void display(void);       // MEMBER FUNCTIONS
			void purchase(void);
			void add(void);
}hw,hw1;    					       // OBJECTS OF THE CLASS

int i=4;                         /*VARIABLE TO CONTROL y-COORDINATE WHILE DISPLAYING
											  EACH RECORD*/

		 /************************************************************/
		 /* FUNCTION DEFINITION TO DISPLAY ALL HARDWARE COMPONENTS   */
		 /************************************************************/

/*THIS FUNCTION DISPLAYS THE ENTIRE DATABASE hard.dat BY CALLING display()
  FOR DISPLAYING INDIVIDUAL RECORDS OF THE DATABASE. */

void hware::showall(void)
{        clrscr();                      // CLEAR SCREEN
			fstream fi;
			fi.open("hard.dat",ios::in);   // OPENING THE FILE IN INPUT MODE
			if((!fi)||(fi.eof()))
			{
			  gotoxy(25,8);
			  textcolor(RED);
			  cprintf("SORRY !!! NO HARDWARE COMPONENTS AVAILABLE");
			  gotoxy(25,23);
			  textcolor(CYAN);
			  cprintf("Press any key to continue......... ");
			  getch();
			  fi.close();
			  return;
			}
			gotoxy(4,3);
			textcolor(RED);
			cprintf("CODE");
			cprintf("    COMPONENT    MANUFACTURER    PRICE    QUANTITY"
					  "    SPECIFICATION");
			textcolor(WHITE);                       // SET THE TEXT COLOR AS WHITE
			fi.seekg(0,ios::beg);
			fi.read((char*)&hw,sizeof(hw));
			while(!fi.eof())                        // TO DETECT THE END OF FILE
					{
					  hw.display();
					  fi.read((char*)&hw,sizeof(hw));  // READ FROM THE FILE
					  found=1;
					}
					i=4;
					if(found==0)
					{
						clrscr();
						gotoxy(25,10);
						textcolor(RED);
						cprintf("SORRY...RECORD NOT FOUND");
					}
			textcolor(CYAN);
			gotoxy(25,23);
			cprintf("Press any key to continue...........");
			textcolor(WHITE);
			getch();
			fi.close();
}

		 /************************************************************/
		 /* FUNCTION DEFINITION TO GET DATA RELATED TO HARDWARE      */
		 /************************************************************/

/*THIS FUNCTION READS THE DATA OF THE HARDWARE TO BE ADDED TO THE STOCK. IT ENABLES
  ADMINISTRATOR TO ENTER THE FOLLOWING DETAILS OF THE HARDWARE COMPONENTS - CODE,
  COMPONENT NAME, MANUFACTURER,PRICE, QUANTITY OF COMPONENTS & SPECIFICATION*/

void hware::get(void)
{
			char c;
			do
			{
			clrscr();                                // CLEAR SCREEN
			cout<<"\n\nEnter the code of the component: ";
			cin>>ccode;
			cout<<"\nEnter the name of hardware component: ";
			gets(obj);
			cout<<"\nEnter the name of manufacturing company: ";
			gets(comp);
			cout<<"\nEnter specifications like capacity,etc. (if any). ";
			cout<<"\n(Enter NA if there are no specifications):";
			gets(spec);
			cout<<"\nEnter the price of the component: ";
			cin>>price;
			cout<<"\nEnter the no. of components: ";
			cin>>no;
			cout<<"\nIs the entered data correct(y/n) : ";
			c=getch();
			}while(c=='n'||c=='N');

}

		 /************************************************************/
		 /* FUNCTION DEFINITION TO DISPLAY DATA RELATED TO HARDWARE  */
		 /************************************************************/


/*THIS FUNCTION DISPLAYS EACH INDIVIDUAL RECORD OF THE DATABASE hard.dat WHEN CALLED
  BY showall() */

void hware::display(void)
{
			gotoxy(4,i);
			cout<<ccode;
			gotoxy(12,i);
			cputs(obj);
			gotoxy(25,i);
			cputs(comp);
			gotoxy(44,i);
			cout<<price;
			gotoxy(55,i);
			cout<<no;
			gotoxy(65,i);
			cputs(spec);
			i++;
}

		 /************************************************************/
		 /*   FUNCTION DEFINITION TO CONTROL PURCHASE OF HARDWARE    */
		 /************************************************************/

/*THIS FUNCTION ENABLES THE OPERATOR TO SELL A HARDWARE COMPONENT TO A CUSTOMER.
	IT DISPLAYS THE LIST OF ALL AVAILABLE HARDWARE COMPONENTS BEFORE TAKING THE
	ORDER*/

void hware::purchase(void)
{
			clrscr();
			fstream f;
			f.open("hard.dat",ios::in|ios::out);  // OPENING THE FILE
			f.seekg(0,ios::beg);
			f.read((char*)&hw,sizeof(hw));  // READING FROM THE FILE
			a:
													/*DISPLAYING THE AVAILABLE HARDWARE COMPONENTS*/
			cout<<"\nLIST OF HARDWARE COMPONENTS THAT ARE AVAILABLE   \n";
			hw.showall();
			int i,co,c=0,t;
			clrscr();           // CLEAR SCREEN
			gotoxy(18,12);
			cout<<"Enter the code of the component to be sold : ";
			cout<<"\n\t\t\t(Enter 0 to go back): ";
			cin>>co;
			if(co==0)
			{
			 f.close();
			 return;
			}
			f.seekg(0,ios::beg);
			f.read((char*)&hw,sizeof(hw));
			t=f.tellp();
			 while(!f.eof())
			{
			  if(co==hw.ccode)
			  {
					  cout<<"\n\t\t\tHow many units to be sold: ";
					  cin>>i;
							  /*TO CHECK IF ENOUGH UNITS ARE AVAILABLE*/
					  if(i>hw.no)
					  {
						 clrscr();
						 gotoxy(25,8);
						 textcolor(RED);
						 cprintf("SORRY !!! Only ");
						 cout<<hw.no;
						 textcolor(RED);
						 cprintf(" units available");
						 gotoxy(25,15);
						 textcolor(YELLOW);
						 cprintf("The list would be shown again");
						 gotoxy(27,17);
						 cprintf("Renter your choice then");
						 textcolor(WHITE);
						 getch();
						 goto a;
					  }
					  else if(i<=hw.no)
					  {
						 hw.no=hw.no-i;
															  /*OVERWRITING RECORD IN FILE*/
						 f.seekg(t-sizeof(hware));
						 f.write((char*)&hw,sizeof(hware));
						 gotoxy(25,20);
						 textcolor(YELLOW);
						 cprintf("Thank you for purchasing!!!!");
						 cout<<"\n\n\t\t\t\tAmount    "<<i*hw.price;
						 textcolor(WHITE);
						 getch();
					  }
					  c=1;
					 }
			  f.read((char*)&hw,sizeof(hw));
			  t=f.tellp();
			  }
			  if(c==0)
			  {
				 clrscr();
				 gotoxy(25,8);
				 textcolor(YELLOW);
				 cprintf("The name of the component you entered could not");
				 gotoxy(25,10);
				 cprintf("    match any of those available our list");
				 gotoxy(25,12);
				 cprintf("    The list would be shown again to you");
				 textcolor(WHITE);
				 getch();
				 goto a;
			  }
				 f.close();
}

		 /************************************************************/
		 /*     FUNCTION DEFINITION TO ADD NEW HARDWARE COMPONENT    */
		 /************************************************************/

/*THIS FUNCTION ENABLES THE ADMINISTRATOR TO ADD NEW HARDWARE COMPONENT
  TO THE STOCK. IT CAN EITHER ADD A NEW COMPONENT OR INCREMENT NO. OF UNITS OF
  AN EXISTING HARDWARE */

void hware::add(void)
{
			fstream f;
			a2:
			int ch=0,fl=0;
			while (ch!=3)
			{ clrscr();
			  mline();
			  gotoxy(25,6);
			  textcolor(YELLOW);
			  cprintf("WHAT DO YOU WANT TO DO.......");
			  cout<<"\n\t\t1.Add to existing components\n"
					<<"\t\t2.Add a new component\n"
					<<"\t\t3.Exit";
			  cout<<"\n\t\t\tEnter your choice: ";
			  status();
			  gotoxy(44,10);
			  cin>>ch;
			  switch(ch)
			  {
				 case 1:gotoxy(10,10);
												 /*DISPLAYING ALL HARDWARE COMPONENTS*/
						  cprintf("First you will be shown the list of available components  ");
						  clrscr();
						  showall();                  //FUNCTION CALLED TO DISPLAY THE ENTIRE DATABASE
															  //TO CHECK IF FILE IS EMPTY
						  if(found==0)
						  break;
						  clrscr();                   // CLEAR SCREEN
						  int c,i;
						  cout<<"\nEnter the code of component you want"
							  <<" to add to stock: ";
						  cin>>c;
						  f.open("hard.dat",ios::in|ios::out); // OPENING FILE
						  f.seekg(0,ios::beg);
						  f.read((char*)&hw,sizeof(hware));
						  int tell=f.tellp();
						  while(!f.eof())
						  {                                  //CHECK IF CODE MATCHES
							if(c==hw.ccode)
							{
							  cout<<"\nHow many units do you want to add: ";
							  cin>>i;
							  hw.no=hw.no+i;
							  fl=1;
							  f.seekg(tell-sizeof(hware));
							  f.write((char*)&hw,sizeof(hware));
							  break;
							}
						  f.read((char*)&hw,sizeof(hware)); // READING FROM FILE
						  tell=f.tellp();
						 }
						 if(fl==0)
						 {
						  gotoxy(25,8);
						  textcolor(RED);
						  cprintf("The code of the component you entered could ");
						  gotoxy(25,10);
						  cprintf("not match any of those available in our list");
						  gotoxy(25,12);
						  cprintf("  The list would be shown again to you ");
						  textcolor(WHITE);
						  getch();
						  goto a2;
						 }
						 f.close();      // CLOSING THE FILE
						 break;

			 case 2: f.open("hard.dat",ios::app|ios::in|ios::out);
						abc:
						hw1.get();             // CALLING FUNCTION GET()

						f.seekg(0,ios::beg);   // TO SET THE POSTION OF
													  // FILE POINTER
						f.read((char*)&hw,sizeof(hware)); // READING FROM FILE

						while(!f.eof())         // TO DETECT THE END OF FILE
						{     //TO CHECK UNIQUENESS OF CODE
							if(hw1.ccode==hw.ccode)
							{
								clrscr();
								gotoxy(25,8);
								textcolor(RED);
								cprintf("This code has already been assigned to another component");
								gotoxy(25,10);
								cprintf("             Please renter the code");
								gotoxy(25,23);
								textcolor(CYAN);
								cprintf("Press any key to continue..........................");
								textcolor(WHITE);
								getch();
								goto abc;
							}
						f.read((char*)&hw,sizeof(hware));  // READING FROM FILE
					  }
						f.close();
						f.open("hard.dat",ios::app|ios::in|ios::out);
						f.write((char*)&hw1,sizeof(hw1));
						f.close();                         // CLOSING THE FILE
						clrscr();
						gotoxy(25,8);
						textcolor(YELLOW);
						cprintf("The record has been successfully added!!");
						gotoxy(25,10);
						cprintf("  The component file after addition is  ");
						gotoxy(25,23);
						textcolor(CYAN);
						cprintf("Press any key to continue..........");
						textcolor(WHITE);
						getch();
						showall();
						break;
			 case 3: break;
			default:
						 clrscr();
						 gotoxy(25,8);
						 textcolor(RED);
						 cprintf("Sorry wrong choice entered!!!!!!!!!!!");
						 gotoxy(25,16);
						 cprintf("Re-enter!!");
						 gotoxy(25,23);
						 textcolor(CYAN);
						 cprintf("Press any key to continue..........");
						 textcolor(WHITE);
						 getch();
						 break;
			}                          // END OF SWITCH
		}
f.close();                         // CLOSING THE FILE
}

/**********END OF DEFINITIONS OF FUNCTIONS OF CLASS hware********/


								/* CLASS I - newpc */

		 /************************************************************/
		 /* CLASS DEFINITION TO CONTROL FUNCTIONS RELATED TO NEW PCS */
		 /************************************************************/


/*THIS CLASS INCLUDES ALL NECESSARY FIELDS AND FUNCTIONS REQUIRED TO MAINTAIN
  pcs.dat DATABASE. THE FUNCTIONS INCLUDED PERFORM THE FOLLOWING TASKS -
  MAINTAINING A STOCK OF PC's , ADDING NEW PC's TO STOCK, DISPLAYING LIST OF
  AVAILABLE PC's */

class newpc
{
			int no;
			char config[250];
			char comp[20];           // PRIVATE MEMBERS
			double price;
			int ncode;
			public:
			newpc(void)               // CONSTRUCTOR FUNCTION
			{
			  ncode=no=1;
			  price=0;
			}
			~newpc()                  // DESTRUCTOR FUNCTION
			{ }
			void showall(void);
			void get(void);          // MEMBER FUNCTIONS
			void display(void);
			void purchase(void);
			void add(void);
}pc,pc1;                         // OBJECTS OF CLASS

int i1=4;

		 /************************************************************/
		 /*     FUNCTION DEFINITION TO DISPLAY ALL AVAILABLE PCS     */
		 /************************************************************/

/*THIS FUNCTION DISPLAYS THE ENTIRE DATABASE pcs.dat BY CALLING display()
  FOR DISPLAYING INDIVIDUAL RECORDS OF THE FILE */

void newpc::showall(void)
{
			clrscr();
			fstream fi;
			fi.open("pcs.dat",ios::in);    // OPENING THE FILE
													//CHECK IF FILE IS EMPTY
			if((!fi)||(fi.eof()))
			{
			  clrscr();
			  gotoxy(25,8);
			  textcolor(RED);
			  cprintf("SORRY !!! NO PCs AVAILABLE ");
			  gotoxy(25,23);
			  textcolor(CYAN);
			  cprintf("Press any key to continue......... ");
			  getch();
			  fi.close();
			  return;
			}
			gotoxy(4,2);
			textcolor(RED);
			cprintf("CODE");     // PRINT CODE ON THE SCRREN

			cprintf("    CONFIGURATION             MANUFACTURER      "
					  "PRICE   QUANTITY");

			textcolor(WHITE);                // SET THE TEXT COLOR AS WHITE

			fi.seekg(0,ios::beg);             // TO SET THE FILE POINTER AT THE BEGINNING
			fi.read((char*)&pc,sizeof(pc));
			while(!fi.eof())
					{
					  pc.display();              // CALLING FUNCTION DISPLAY()

					  fi.read((char*)&pc,sizeof(pc));  // READING FROM THE FILE

					  found=1;
					}
					i1=4;
					if(found==0)
					{
					  clrscr();
					  gotoxy(25,10);
					  textcolor(YELLOW);
					  cprintf("SORRY !! Record not found");
					}
		  gotoxy(25,23);
		  textcolor(CYAN);
		  cprintf("Press any key to continue...........");
		  textcolor(WHITE);
		  getch();
		  fi.close();    //DELINK THE FILE
}

		 /***************************************************************/
		 /* FUNCTION DEFINITION TO INPUT INFORMATION RELATED TO NEW PCS */
		 /***************************************************************/

/*THIS FUNCTION READS THE DATA OF THE PC TO BE ADDED TO THE STOCK. IT ENABLES
  THE ADMINISTRATOR TO ENTER THE FOLLOWING DETAILS OF THE PCs - CODE, CONFIGURATION,
  MANUFACTURER, PRICE & QUANTITY */

void newpc::get(void)
{
			char c;
			do
			{
			clrscr();                     // CLEAR SCREEN
			cout<<"\n\nEnter the item code of the computer: ";
			cin>>ncode;
			cout<<"\nEnter the configuration of the pc:\n ";
			gets(config);
			cout<<"\nEnter the name of manufacturing company: ";
			gets(comp);
			cout<<"\nEnter the price of the pc: ";
			cin>>price;
			cout<<"\nEnter the no. of pcs: ";
			cin>>no;
					//CONFIRMING IF ENTERED DATA IS CORRECT
			cout<<"\nIs the entered data correct(y/n) : ";
			c=getch();
			}
			while(c=='n'||c=='N');

}

		 /*****************************************************************/
		 /* FUNCTION DEFINITION TO DISPLAY INFORMATION RELATED TO NEW PCS */
		 /*****************************************************************/


/*THIS FUNCTION DISPLAYS EACH INDIVIDUAL RECORD OF THE DATABASE pcs.dat WHEN
	CALLED BY showall() */

void newpc::display(void)
		 {
			gotoxy(4,i1);
			cout<<ncode;
			gotoxy(12,i1);
								//LOOP TO DISPLAY CONFIGURATION OF PC WITHIN DEFINED WIDTH
			for(int j=0;j<strlen(config);j++)
			{ cout<<config[j];
			  if((j%23==0)&&(j!=0))
			  cout<<"\n\t   ";
			}
			gotoxy(42,i1);
			cputs(comp);
			gotoxy(56,i1);
			cout<<price;
			gotoxy(68,i1);
			cout<<no;
							  //DETERMINING NO. OF LINES(=i1) REQUIRED TO
							  //DISPLAY THE CONFIGURATION
			int k=strlen(config)/23;
			i1=i1+k+1;
		 }

		 /******************************************************/
		 /* FUNCTION DEFINITION TO CONTROL PURCHASE OF NEW PCS */
		 /******************************************************/

/*THIS FUNCTION ENABLES THE OPERATOR TO SELL A PC TO A CUSTOMER. IT DISPLAYS
  THE LIST OF ALL AVAILABLE PCs BEFORE TAKING THE ORDER */

void newpc::purchase(void)
{
			clrscr();                            // CLEAR SCREEN()
			fstream f;
			f.open("pcs.dat",ios::in|ios::out);  // OPENING THE FILE

			f.seekg(0,ios::beg);                 // TO SET THE POSITION OF FILE POINTER

			f.read((char*)&pc,sizeof(pc));       // READING FROM THE FILE
			a:
			cout<<"\nLIST OF PERSONAL COMPUTERS THAT ARE AVAILABLE   \n";
			pc.showall();
			int i,co,c=0,t;
			clrscr();                          // CLEAR SCREEN()
			gotoxy(18,12);
			cout<<"Enter the code of the pc you want to purchase.";
			cout<<"\n\t\t(Enter 0 to go back): ";
			cin>>co;
			if(co==0)
			{
			  f.close();
			  return;
			}
			f.seekg(0,ios::beg);             // TO GET THE CURRENT POSITION OF FILE POINTER

			f.read((char*)&pc,sizeof(pc));   // READING FROM THE FILE
			t=f.tellp();
			 while(!f.eof())
			{     //CHECKING IF CODE MATCHES
			  if(co==pc.ncode)
					{ cout<<"\nHow many units do you want to purchase: ";
					  cin>>i;
							  //IF NOT ENOUGH COMPONENTS ARE AVILABLE
					  if(i>=pc.no)
					  { clrscr();
						 gotoxy(25,8);
						 textcolor(RED);
						 cprintf("Sorry !! only ");
						 cout<<pc.no;
						 textcolor(RED);
						 cprintf("units available.");
						 gotoxy(25,15);
						 textcolor(YELLOW);
						 cprintf("The list would be shown again");
						 gotoxy(27,17);
						 cprintf("Re-enter your choice then");
						 textcolor(WHITE);
						 getch();
						 goto a;
					  }
					  else if(i<=pc.no)
					  {
						 pc.no=pc.no-i;
										  //OVERWRITING RECORD TO UPDATE QUANTITY
						 f.seekg(t-sizeof(newpc));
						 f.write((char*)&pc,sizeof(newpc)); // WRITING IN FILE
						 gotoxy(25,20);
						 textcolor(YELLOW);
						 cprintf("Thank you for purchasing!!!!");
						 cout<<"\n\nAmount    "<<i*pc.price;
						 textcolor(WHITE);
						 getch();
					  }
					  c=1;
					 }
			  f.read((char*)&pc,sizeof(pc));    // READING FROM THE FILE
			  t=f.tellp();      // TO GET THE CURRENT POSITION OF FILE POINTER
			  }
			  if(c==0)
			  {
				 clrscr();
				 gotoxy(25,8);
				 textcolor(YELLOW);
				 cprintf("The name of the PC  you entered could not match ");
				 gotoxy(25,10);
				 cprintf("     any of those available our list.");
				 gotoxy(25,12);
				 cprintf("  The list would be shown again to you ");
				 textcolor(WHITE);
				 getch();
				 goto a;
			  }
f.close();    							   // DELINKING THE FILE
}

		 /*****************************************************/
		 /* FUNCTION DEFINITION TO ADD TO NEW PCS IN THE FILE */
		 /*****************************************************/


/*THIS FUNCTION ENABLES THE ADMINISTARTOR TO ADD NEW PC TO THE STOCK. IT CAN
  EITHER ADD A NEW PC OR INCREMENT THE NO. OF UNITS OF THE PC */
void newpc::add(void)
		 { fstream f;
			a2:
			int ch=0,fl=0;
			while (ch!=3)
			{ clrscr();              // CLEAR SCREEN
			  mline();               // DRAW LINES
			  gotoxy(25,6);
			  textcolor(YELLOW);    // TO SET THE TEXT COLOR AS YELLOW
			  cprintf("WHAT DO YOU WANT TO DO.......");
			  cout<<"\n\t\t1.Add to existing computers\n"
					<<"\t\t2.Add a new computer\n"
					<<"\t\t3.Exit";
			cout<<"\n\t\t\tEnter your choice: ";
			status();
			gotoxy(44,11);
			cin>>ch;
			switch(ch)
			{ case 1:     //DISPLAYING LIST OF ALREADY AVAILABLE PCS
						 gotoxy(10,10);
						 cprintf("First you will be shown the list"
									" of available computers  ");
				  /*		 for(int j=15;j<60;j++)
						 { gotoxy(j,11);
							cout<<"*";
							delay(20);
						 }*/
						 clrscr();
						 showall();
						 if(found==0)
						 break;
						 clrscr();        // CLEAR SCREEN
						 int c,i;
						 cout<<"\nEnter the code of computer you want"
							  <<" to add to stock: ";
						 cin>>c;
						 f.open("pcs.dat",ios::in|ios::out);

						 f.seekg(0,ios::beg);   // TO SET POSITION OF FILE POINTER

						 f.read((char*)&pc,sizeof(newpc));
						 int tell=f.tellp();
						 while(!f.eof())    // AS LONG AS EOF() IS NOT REACHED
						 {
							if(c==pc.ncode)
							{
							  cout<<"\nHow many units do you want to add: ";
							  cin>>i;
							  pc.no=pc.no+i;
							  fl=1;
												//TO PLACE THE FILE POINTER AT THE START OF
												//RECORD SO AS TO OVERWRITE IT
							  f.seekg(tell-sizeof(newpc));
							  f.write((char*)&pc,sizeof(newpc));
							  break;
							}
						  f.read((char*)&pc,sizeof(newpc));  // READING FROM FILE
						  tell=f.tellp();  // TO GET CURRENT POSITION OF POINTER
						 }
						 if(fl==0)
						 { gotoxy(25,8);
							textcolor(YELLOW);
							cprintf("The code of the computer you entered could not match ");
							gotoxy(25,10);
							cprintf("         available in our list.");
							gotoxy(25,15);
							textcolor(CYAN);
							cout<<" The list would be shown again to you ";
							textcolor(WHITE);
							getch();
							goto a2;
							}
						  f.close();    // CLOSING THE FILE
						 break;

			 case 2: f.open("pcs.dat",ios::app|ios::in|ios::out);
						abc:
						pc1.get();
						f.seekg(0,ios::beg); // TO SET POSITION OF FILE POINTER

						f.read((char*)&pc,sizeof(newpc)); // READING FROM FILE

						while(!f.eof())     // TO DETECT THE END OF THE FILE
						{    //TO CHECK UNIQUENESS OF CODE
						  if(pc1.ncode==pc.ncode)
							{
							  clrscr();
							  gotoxy(15,8);
							  textcolor(RED);
							  cprintf("This code has already been assigned to another component!! ");
							  gotoxy(15,10);
							  cout<<"                  Please re-enter the code";
							  gotoxy(25,23);
							  textcolor(CYAN);
							  cprintf("Press any key to continue......");
							  textcolor(WHITE);
							  getch();
							  goto abc;
							}
						f.read((char*)&pc,sizeof(newpc)); // READING FROM THE FILE
					  }
						f.close();
						f.open("pcs.dat",ios::app|ios::in|ios::out);
						f.write((char*)&pc1,sizeof(pc1)); //WRITING IN THE FILE
						f.close();  // CLOSING THE FILE
						clrscr();
						gotoxy(25,8);
						textcolor(RED);
						cprintf("The record has been successfully added!!");
						gotoxy(25,10);
						cprintf("   The pc file after addition is  ");
						gotoxy(25,23);
						textcolor(CYAN);
						cprintf("Press any key to continue...............");
						textcolor(WHITE);
						getch();
						showall();               //DISPLAYING NEW LIST
						break;
			 case 3:break;

			default:clrscr();
					  gotoxy(25,8);
					  cout<<"\nSORRY WRONG CHOICE ENETRED - RE-ENTER";
					  gotoxy(25,23);
					  textcolor(CYAN);
					  cprintf("Press any key to continue..........");
					  textcolor(WHITE);
					  getch();
					  break;
			}
		}
		f.close();       								// DELINKING THE FILE
}

		 /******************************************************/
		 /* FUNCTION DEFINITION TO DISPLAY THE STARTING SCREEN */
		 /******************************************************/

/*THIS FUNCTION IS USED FOR DISPLAYING THE STARTING SCREEN. IT ENABLES THE
  initgraph(), which inturn initialises the GRPHIPCS SYSTEM by loading the
  GRPAHICS DRIVER from disk and then putting the system to GRAPHICS MODE.
  OTHER FUNCTIONS USED- sound(), delay(),settextstyle(), outtextxy(),setcolor()
  setfillstyle() */

void startscr(void)
{

	 int gdriver = DETECT,  gmode;         /* request auto detection fora graphics driver */

	 initgraph(&gdriver, &gmode, "");      /* initialize graphics mode */

	 for(int i=1,j=1;i<625||j<470;i+=8)    //FOR CREATING A BORDER ON THE SCREEN
	 {
		outtextxy(i,1,"�");                //HORIZONTAL BORDER ON THE TOP AND BOTTOM
		outtextxy(i,470,"�");
		setcolor(i);
		delay(50);                        //SUSPENDS EXECUTION FOR 50 MILLISECONDS
		if(i>616)
		{
		 j+=8;                            //VERTICAL BORDERS ON LEFT AND RIGHT
		 outtextxy(2,j,"�");
		 outtextxy(625,j,"�");
		}
	 }
													/*TO SET THE STYLE OF THE TEXT*/

	 settextstyle(4,0,5);              //4==font,0==direction,6==size
	 for(i=0;i<=10;i++)
	 {
	  sound(i*100);                    //TO EMIT SOUND OF GIVEN FREQUENCY
	  delay(200);
	  setcolor(i);
	  outtextxy(80,80,"  COMPUTER STORE"); //TO DISPLAY TEXT AT 210,70
													  //  IN GRAPHICS MODE
	  outtextxy(60,150,"MANAGEMENT SYSTEM");
	  delay(50);
	 }
	 nosound();
	 setcolor(13);
	 settextstyle(7,0,5);               //TO SET THE STYLE OF TEXT
	 outtextxy(350,370,"LOADING.....");
	 delay(50);
	 setfillstyle(5,RED);                //USED TO SET THE STYLE OF FILL IN BAR
	 delay(150 );
	 for(int s=1;s<505;s+=5)
	 {
			setfillstyle(2,1);
			bar3d(50+s,310,50,350,15,2);    //TO DRAW A 3-D BAR
			delay(50);
	  }
	 delay(1000);
	 cleardevice();                      //TO CLEAR THE SCREEN

													 //LOOP TO DRAW CONVERGING CIRCLES

	for(int l=1,z=470,u=1,v=625;l<235||u<313;l++,z--,u++,v--)
	 {
		 setcolor(LIGHTBLUE);
		 circle(u,235,5);
		 delay(3);
		 setcolor(BLACK);
		 circle(u,235,5);              //TO DRAW A CIRCLE OF RADIUS 'u'
		 setcolor(LIGHTBLUE);          // TO SET THE COLOR AS LIGHT BLUE
		 circle(v,235,5);
		 delay(3);
		 setcolor(BLACK);
		 circle(v,235,5);
		 if(l<235)
		 {setcolor(LIGHTBLUE);
		 circle(312,l,5);
		 delay(3);
		setcolor(BLACK);
		circle(312,l,5);
		setcolor(LIGHTBLUE);
		 circle(312,z,5);
		 delay(3);
		setcolor(BLACK);        // TO SET THE COLOR AS BLACK()
		circle(312,z,5);
  }
}
	  cleardevice();
	  setbkcolor(BLACK);
	  setcolor(BLUE);
	  circle(312,235,5);
	  delay(300);
										//LOOP TO DRAW ENLARGING CIRCLE
	 for (int i1=0;i1<=230;i1++)
	 {
	  circle(312,235,i1);
	  delay(30);
	 }
	 for(int i3=5;i3>=BLACK;i3--)
	 {
		setcolor(i3);              // TO SET THE TEXT COLOR
		sound(109*i3);
	  if(i3!=1)
	  {
	  settextstyle(SANS_SERIF_FONT,0,1);
	  outtextxy(130,125,"CONCEIVED AND DEVELOPED BY--");
	  outtextxy(210,145,"AVN9");
	  delay(1000);
	  }
	}
	 nosound();
	 setcolor(BLACK);
	 for (i1=230;i1>=0;i1--)
	 {
	  circle(312,235,i1);
	  delay(30);
	 }
	 closegraph();
}


		 /*********************************************************/
		 /*      FUNCTION DEFINITION TO DISPLAY ENDING SCREEN     */
		 /*********************************************************/

/*THIS FUNCTION DISPLAYS THE EXIT SCREEN OF THE SYSTEM.THIS FUNCTION MAINLY
  USES THE PREDEFINED random() to return an integer between 0 & n-1  */

void endscr()
{
													/* request auto detection */
			int gdriver = DETECT, gmode;
												 /* initialize graphics mode */
			initgraph(&gdriver, &gmode, "");
			cleardevice();
			int i,j;
			for(int k=0;k<600;k++)
			{
			  i=random(700+k);         //TO OBTAIN A RANDOM NUMBER
			  j=random(700+k);
			  setcolor(k);
			  outtextxy(i,j,".");
			  delay(10);
			}
		  settextstyle(4,0,6);     	//4==font,0==direction,6==size
		  for(i=0;i<=10;i++)
		  {
			sound(i*8+200);      		//TO EMIT SOUND OF GIVEN FREQUENCY
			delay(200);
			setcolor(i);
			outtextxy(149,70,"THANK YOU ");   //TO DISPLAY TEXT AT 210,70
													//  IN GRAPHICS MODE
			delay(30);
		 }
	 nosound();
	 delay(1000);
	 setcolor(YELLOW);
	 settextstyle(SANS_SERIF_FONT,0,4);     //4==font,0==direction,6==size
	 outtextxy(110,250,"FOR USING THIS SOFTWARE");
	 getch();
	 cleardevice();
		}

		 /***************************************************/
		 /*     START OF MAIN TO CONTROL INITIAL MENUS      */
		 /***************************************************/

void main()
{
  int c2;

  char pas[100],ch,c1,c3;
  startscr();                       //CALLING FUNCTION startscr()
  do
  {
	clrscr();                       // CLEAR SCREEN
	mline();
	gotoxy(31,8);
	textcolor(YELLOW);             // TO SET THE TEXT COLOR AS YELLOW

											/*DISPLAY INITIAL MENU*/
	 cprintf(" OPTIONS IN HAND");
	 cout<<"\n\t     �� If you are the Computer Operator..............�� 1"
		  <<"\n\t     �� If you are the Administrator .................�� 2"
		  <<"\n\t     �� If you want to exit...........................�� 3";
	 cout<<"\n\t\t\tEnter your choice��";
	 status();
	 gotoxy(45,12);
	 c1=getch();
	 switch(c1)                             // STARTING OF SWITCH
	  {
		 case '1': x:
					  clrscr();                 // CLEAR SCREEN()
					  gotoxy(22,12);
														 /*ASKING FOR PASSWORD*/
					  cout<<"Enter Operator's Password: ";
					  gotoxy(55,12);
					  textcolor(BLACK);
					  cprintf("**************************");
					  gotoxy(55,12);
					  textcolor(BLACK);
					  gets(pas);
					  gotoxy(26,23);
					  textcolor(CYAN+BLINK); //TO SET COLOR AS CYAN AND
												  // MAKE TEXT TO BLINK
					  cprintf("STATUS");
					  textcolor(RED+BLINK);  //TO SET COLOR AS RED AND MAKE
												  //TEXT TO BLINK
					  cprintf(" : ");
					  textcolor(GREEN+BLINK);
					  cprintf("VERIFYING PASSWORD...");
					  textcolor(WHITE);
					  for(int ab=55;ab<60;ab++)
					 {
					  textcolor(RED);
					  gotoxy(ab,12);
					  cprintf("*");
					  delay(600);
					 }
					textcolor(WHITE);     // SET THE TEXT COLOR AS WHITE
					if((strcmpi(pas,"store")==0))//MATCHING THE PASSWORD
					{
					  gotoxy(55,12);
					  textcolor(GREEN);
					  cprintf("*****");
					  gotoxy(32,14);
					  cprintf("PASSWORD ACCEPTED");
					  delay(1500);
					  textcolor(WHITE);
					  do
					  {
						clrscr();
						mline();
						gotoxy(25,6);
						textcolor(YELLOW);  //TO SET THE TEXT COLOR AS YELLOW
						cprintf("WHAT DO YOU WANT TO DO.......");
						cout<<"\n\t\t �� Open a new AMC account.................. �� 1"
							<<"\n\t\t �� List all the members.................... �� 2"
							<<"\n\t\t �� Modify information of existing member... �� 3"
							<<"\n\t\t �� Search for information of existing member�� 4"
							<<"\n\t\t �� Renew membership of a member.............�� 5"
							<<"\n\t\t �� Generate AMC card........................�� 6"
							<<"\n\t\t �� List the available hardware components...�� 7"
							<<"\n\t\t �� List the PCs available...................�� 8"
							<<"\n\t\t �� Sell a hardware component................�� 9"
							<<"\n\t\t �� Sell a new computer......................�� 10"
							<<"\n\t\t �� End existing AMC.........................�� 11"
							<<"\n\t\t �� Go back to main menu.....................�� 12";
					  cout<<"\n\t\t\tPlease enter your choice: ";
					  status();
					  gotoxy(50,19);
					  cin>>c2;
					  switch(c2)
					  {
						 case 1: mem.add();    // CALLING FUNCTION ADD()
									break;

						  case 2:clrscr();
									mem.showall();
									break;

						  case 3:mem.change();  // CALLING FUNCTION CHANGE()
									break;

						  case 4:mem.search();  // CALLING FUNCTION SEARCH()
									break;

						  case 5:mem.renew();   // CALLING FUNCTION RENEW()
									break;

						  case 6:mem.card();    // CALLING FUNCTION CARD()
									break;

						  case 7:clrscr();
									hw.showall();   // CALLING FUNCTION SHOWALL()
									break;

						  case 8:clrscr();   // CLEAR SCREEN
									pc.showall();  // CALLING FUNCTION SHOWALL()
									break;

						  case 9:hw.purchase(); // CALLING FUNCTION PURCHASE()
									break;

						  case 10: pc.purchase(); // CALLING FUNCTION PURCHASE()
									 break;

						  case 11:mem.del();  // CALLING FUNCTION DEL()
									break;

						  case 12:break;

						  default: clrscr();
									  gotoxy(25,8);
									  cout<<"SORRY !!! Wrong choice entered ";
									  gotoxy(35,10);
									  cout<<"Re-enter";
									  gotoxy(25,23);
									  textcolor(CYAN);
									  cprintf("Press any key to continue..........");
									  textcolor(WHITE);
									  getch();
									  break;
					  }
					 }while(c2!=12);
				  }

					else
					{

					  clrscr();
					  gotoxy(25,10);
					  textcolor(RED);
					  cprintf("SORRY !!! WRONG PASSWORD ENTERED ");
					  gotoxy(22,15);
					  cout<<"Do you want to re-enter password(y/n): ";
					  gotoxy(42,20);
					  textcolor(WHITE);
					  cin>>ch;
					  if(ch=='Y'||ch=='y')
					  goto x;
					}

					  break;

		 case '2': y:
					  clrscr();                // CLEAR SCREEN()
					  gotoxy(22,12);
													  /*ASKING FOR PASSWORD*/
					  cout<<"Enter administrator's password: ";
					  gotoxy(55,12);
					  textcolor(BLACK);
					  cprintf("**************************");
					  gotoxy(55,12);
					  textcolor(BLACK);
					  gets(pas);
					  gotoxy(26,23);
					  textcolor(CYAN+BLINK); //TO SET COLOR AS CYAN AND
												  // MAKE TEXT TO BLINK
					  cprintf("STATUS");
					  textcolor(RED+BLINK);  //TO SET COLOR AS RED AND MAKE
												  //TEXT TO BLINK
					  cprintf(" : ");
					  textcolor(GREEN+BLINK);
					  cprintf("VERIFYING PASSWORD...");
					  textcolor(WHITE);
					  for(int bc=55;bc<60;bc++)
					  {
						textcolor(RED);
						gotoxy(bc,12);
						cprintf("*");
						delay(600);
					  }
					  textcolor(WHITE);     // SET THE TEXT COLOR AS WHITE
					  if((strcmpi(pas,"admin")==0))
					  {
						gotoxy(55,12);
						textcolor(GREEN);
						cprintf("*****");
						gotoxy(32,14);
						cprintf("PASSWORD ACCEPTED");
						delay(1500);
						textcolor(WHITE);
						do
						{
						  clrscr();          // CLEAR SCREEN()
						  mline();
						  gotoxy(25,6);
						  textcolor(YELLOW);  // SET THE TEXT COLOR AS YELLOW
						  cprintf("WHAT DO YOU WANT TO DO.......");
						  textcolor(WHITE);
						  cout<<"\n\n\t\t �� Display all the hardware components....�� 1"
								<<"\n\t\t �� Add components to the list of hardware...�� 2"
								<<"\n\t\t �� Display all the PCs available............�� 3"
								<<"\n\t\t �� Add PCs to the list of computers.........�� 4"
								<<"\n\t\t �� List all existing members................�� 5"
								<<"\n\t\t �� Go back to main menu.....................�� 6";
						  cout<<"\n\n\t\t\tPlease enter your choice: ";
						  status();
						  gotoxy(50,15);
						  c3=getch();
						  switch(c3)                    // STARTING OF THE SWITCH
						  {  case '1': clrscr();
											hw.showall();    // CALLING FUNCTION SHOWALL()
											break;

							  case '2': hw.add();        // CALLING FUNCTION ADD()
											break;

							 case '3': clrscr();
										  pc.showall();    // CALLING FUNCTION SHOWALL()
										  break;

							 case '4': pc.add();      // CALLING FUNCTION ADD()
										  break;

							 case '5': clrscr();
										  mem.showall();   // CALLING FUNCTION SHOWALL()
										  break;

							 case '6': break;
							 case 27 : break;
							 default : clrscr();
										  gotoxy(23,8);
										  textcolor(RED);
										  cprintf("Sorry wrong choice entered !! Re-enter!!");
										  gotoxy(25,23);
										  textcolor(CYAN);
										  cprintf("Press any key to continue..........");
										  textcolor(WHITE);
										  getch();
										  break;
							}
						}while(c3!='6'&&c3!=27);
					}
				 else
					  {
						 clrscr();
						 gotoxy(25,10);
						 textcolor(RED);
						 cprintf("SORRY !!! WRONG PASSWORD ENTERED " );
						 gotoxy(22,15);
						 cout<<"\nDo you want to Re-enter password(y/n): ";
						 gotoxy(36,20);
						 cin>>ch;
						 if(ch=='Y'||ch=='y')
						 goto y;
					  }
					break;
		 case '3': //endscr();
					  break;
		 case 27:  //endscr();
					  break;
		 default: clrscr();            // CLEAR SCREEN
					 gotoxy(25,8);
					 cout<<"SORRY !! WRONG CHOICE ENTERED";
					 gotoxy(35,10);
					 cout<<"Renter!!";
					 gotoxy(25,23);
					 textcolor(CYAN);
					 cprintf("Press any key to continue..........");
					 textcolor(WHITE);
					 getch();
					 break;
	 }                               // END OF SWITCH()
  }while(c1!='3'&&c1!=27) ;         //END OF WHILE
}                                  //END OF MAIN


