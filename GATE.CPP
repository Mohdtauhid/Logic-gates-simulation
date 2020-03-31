#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<graphics.h>
int main()
{  char pattern[15]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0XFF,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA };
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	   int A,B,C;

   settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);

   outtextxy(getmaxx()/4,50,"AND GATE IMPLEMENTATION ");
   setaspectratio(10000,10000);
   ellipse(getmaxx()/2.3,getmaxy()/2,294,66,88,66);
   line(312,179,312,299);
outtextxy(60,180,"A");

  outtextxy(60,219,"B");
  outtextxy(60,259,"C");
   line(170,200,311,200);
      line(170,240,311,240);
   line(170,277,311,277);
   outtextxy(402,278,"OUPUT= A.B.C");
   line(367,236,479,236);

  circle(146,205,9);

  circle(146,244,9);
  circle(146,279,9);
  circle(499,235,9);
		    getch();
	  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
 cout<<"\nENTER (A,B,C) VALUE";
 cin>>A>>B>>C;
   char DD[2]="0";

char AA[4]; itoa(A,AA,10);
 char BB[4]; itoa(B,BB,10);
 char CC[4]; itoa(C,CC,10);
 if(A==1)
  floodfill(146,203,15);
  if(B==1)
  floodfill(146,240,15);
       if(C==1)
  floodfill(146,272,15);
  if(A&&B&&C)
  {  outtextxy(104,182,AA);
  outtextxy(104,219,BB);
    outtextxy(104,259,CC);
  outtextxy(530,214,"1");
  setfillpattern(pattern,4);
  floodfill(494,235,15);
  }
  else
  {outtextxy(104,182,AA);
  outtextxy(104,219,BB);
    outtextxy(104,259,CC);
  outtextxy(530,214,DD);
  }
  getch();
    clrscr();
 cleardevice();

  ///////////////////////////////////////////////////////////
outtextxy(getmaxx()/4,50,"OR GATE IMPLEMENTATION ");

   settextstyle(SANS_SERIF_FONT,HORIZ_DIR,4);
   ellipse(getmaxx()/3,getmaxy()/2,317,48,100,88);
   ellipse(319,267,18,112,100,100);

   ellipse(319,207,250,342,100,100);
 outtextxy(60,180,"A");

  outtextxy(60,219,"B");
  outtextxy(60,259,"C");
   line(170,200,303,200);
      line(170,240,313,240);
   line(170,277,302,277);
   line(414,236,479,236);
  circle(146,205,9);

  circle(146,244,9);
  circle(146,279,9);
  circle(499,235,9);
   outtextxy(402,278,"OUPUT= A+B+C");
		    getch();
	  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
 cout<<"\nENTER (A,B,C) VALUE";
 cin>>A>>B>>C;
itoa(A,AA,10);
  itoa(B,BB,10);
 itoa(C,CC,10);
 if(A==1)
  floodfill(146,203,15);
  if(B==1)
  floodfill(146,240,15);
       if(C==1)
  floodfill(146,272,15);

  if(A||B||C)
  {  outtextxy(104,182,AA);
  outtextxy(104,219,BB);
    outtextxy(104,259,CC);
  outtextxy(530,214,"1");
  setfillpattern(pattern,4);
  floodfill(494,235,15);
  }
  else
  {outtextxy(104,182,AA);
  outtextxy(104,219,BB);
    outtextxy(104,259,CC);
  outtextxy(530,214,DD);
  }
  getch();
    clrscr();
 cleardevice();

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
outtextxy(getmaxx()/4,50,"NOT GATE IMPLEMENTATION ");

   settextstyle(SANS_SERIF_FONT,HORIZ_DIR,4);
   line(getmaxx()/3,getmaxy()/3,getmaxx()/3,260);
	 line(getmaxx()/3,getmaxy()/3,288,200);
       line(213,260,286,201);
     circle(292,200,4.4);

   line(130,210,212,210);
   line(540,231,571,231);
  line(298,199,409,199);
  outtextxy(30,190,"A");
  circle(424,200,9);
  circle(106,210,9);

   outtextxy(400,230,"OUPUT = A");
		    getch();
	  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
 cout<<"\nENTER (A) VALUE";
 cin>>A;
   itoa(A,AA,10);
 if(A==1)
  floodfill(106,210,15);
  if(A==1)
  {  outtextxy(66,188,AA);
  outtextxy(449,180,DD);
  }
  else
  {outtextxy(66,188,AA);
  outtextxy(449,177,"1");
  setfillpattern(pattern,4);
  floodfill(424,200,15);
  }
  getch();
    clrscr();
 cleardevice();


  /////////////////////////////////////////////////////////////////////////

   settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
   outtextxy(getmaxx()/4,50,"NAND GATE IMPLEMENTATION ");
   ellipse(getmaxx()/3,getmaxy()/2,297,66,88,66);
   line(248,179,250,298);
 outtextxy(20,182,"A");
  outtextxy(20,219,"B");
  outtextxy(20,259,"C");

  circle(306,239,5);

  line(140,200,248,200);
  line(140,242,250,242);
  line(140,279,250,279);
   line(312,239,390,239);
 circle(120,200,9);
 circle(120,240,9);
  circle(120,279,9);
  circle(419,239,9);

	       line(520,266,610,266);
			 line(520,270,577,270);
   outtextxy(350,270,"OUPUT = ((A.B).C)");
		    getch();
	  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
 cout<<"\nENTER (A,B,C) VALUE";
 cin>>A>>B>>C;

 itoa(A,AA,10);
  itoa(B,BB,10);
  itoa(C,CC,10);
 if(A==1)
  floodfill(120,200,15);
  if(B==1)
  floodfill(120,240,15);
       if(C==1)
  floodfill(120,279,15);

  if(!(!(A&&B)&&C))
  {  outtextxy(70,182,AA);
  outtextxy(70,219,BB);
    outtextxy(70,259,CC);
  outtextxy(460,217,"1");
  setfillpattern(pattern,4);
  floodfill(419,239,15);
  }
  else
  {outtextxy(70,182,AA);
  outtextxy(70,219,BB);
    outtextxy(70,259,CC);
  outtextxy(460,217,DD);
  }

  getch();
    clrscr();
 cleardevice();


/////////////////////////////////////////////////////////////////////////
outtextxy(getmaxx()/4,50," NOR GATE IMPLEMENTATION ");

   settextstyle(SANS_SERIF_FONT,HORIZ_DIR,4);
   ellipse(getmaxx()/3,getmaxy()/2,317,48,100,88);
   ellipse(319,267,18,112,100,100);

   ellipse(319,207,250,342,100,100);
 outtextxy(30,177,"A");

  outtextxy(30,219,"B");
  outtextxy(30,260,"C");
   line(170,195,300,195);
   line(170,238,313,238);
   line(170,279,302,279);
 circle(140,200,9);
 circle(140,240,9);
  circle(140,279,9);
  circle(579,235,9);
	    line(427,236,559,236);

   circle(420,236,6);


	    line(498,314,620,314);
	    line(504,320,577,320);
   outtextxy(350,320,"OUPUT =((A+B)+C)");

       getch();
	  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
 cout<<"\nENTER (A,B,C) VALUE";
 cin>>A>>B>>C;
 itoa(A,AA,10);
 itoa(B,BB,10);

itoa(C,CC,10);
 if(A==1)
  floodfill(140,200,15);
  if(B==1)
  floodfill(140,240,15);
       if(C==1)
  floodfill(140,279,15);

  if(!(!(A||B)||C))
  {  outtextxy(80,182,AA);
  outtextxy(80,219,BB);
    outtextxy(80,259,CC);
  outtextxy(620,214,"1");
  setfillpattern(pattern,4);
  floodfill(579,235,15);
  }
  else
  {outtextxy(80,182,AA);
  outtextxy(80,219,BB);
    outtextxy(80,259,CC);
  outtextxy(620,214,DD);
  }
  getch();
      clrscr();
cleardevice();

////////////////////////////////////////////////////////////////////

outtextxy(getmaxx()/4,50," XOR GATE IMPLEMENTATION ");

   settextstyle(SANS_SERIF_FONT,HORIZ_DIR,4);

   ellipse(getmaxx()/3.2,getmaxy()/2,320,44,100,88);
   ellipse(getmaxx()/3,getmaxy()/2,317,48,100,88);
   ellipse(319,267,18,112,100,100);

   ellipse(319,207,250,342,100,100);
 outtextxy(30,176,"A");
  outtextxy(30,220,"B");

  outtextxy(30,259,"C");
   circle(140,200,9);
 circle(140,240,9);
  circle(140,279,9);
  circle(529,235,9);
   line(170,207,290,207);
   line(170,239,298,239);
   line(170,271,291,271);
   outtextxy(412,285,"OUPUT= A+B+C");
   line(415,236,499,236);
   circle(615,307,10.55);
   circle(575,307,10.55);
       getch();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
 cout<<"\nENTER (A,B,C) VALUE";
 cin>>A>>B>>C;

 itoa(A,AA,10);
  itoa(B,BB,10);
  itoa(C,CC,10);
 if(A==1)
  floodfill(140,200,15);
  if(B==1)
  floodfill(140,240,15);
       if(C==1)
  floodfill(140,279,15);

  if((A&&(!B)&&(!C))||((!A)&&(!C)&&(B))||(((!A)&&(!B)&&C))||A&&B&&C)
  {  outtextxy(80,182,AA);
  outtextxy(80,219,BB);
    outtextxy(80,259,CC);
  outtextxy(559,214,"1");
  setfillpattern(pattern,4);
  floodfill(529,235,15);
  }
  else
  {outtextxy(80,182,AA);
  outtextxy(80,219,BB);
    outtextxy(80,259,CC);
  outtextxy(559,214,DD);
  }
  getch();
    clrscr();
 closegraph();
  return 0;
 }

