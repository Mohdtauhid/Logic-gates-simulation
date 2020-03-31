/*------------------------------------------------------------------------*/
/*		SIMULATION OF DIGITAL LOGIC GATES                         */
/*------------------------------------------------------------------------*/
#include<iostream.h>
#include<stdio.h>
#include<process.h>
#include<dos.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
# define xp 53                                   // xp starting x - position in drawing space
# define yp 26                                   // yp starting y - position in drawing space
# define O 4                                     // color for input One
# define Z 2                                     // color for input Zero
# define I_O 15                                  // color of the I/O lines before processing
# define DOTS 15                                 // color of the dots
union REGS i, o;
char pos[10][10];
int close_help;
void initmouse();
void showmouse();
void hidemouse();
void getmouse(int*, int*, int*);
void front();
struct store
{
   int x, y;
};
struct store os;
class draw
{
     int X, Y, lx, ly, rx, ry, br, br1, button;
     int job, len, a[15], color;
     int pixx[12], pixy[12], xx, yy;

   public :
     void process();
     void operation();
     void appearance();
     void dots();

     void and();
     void or();
     void not();
     void nand();
     void nor();
     void xor();
     void xnor();
     struct store assign(int, int);

     void Line();
     void rub();
     void Delete();
     void give_IO(int, int, int);
     void clear();
     void find();
     struct store identifyInput(int, int);
     void changeColor(int, int, int);
     void reDraw();

     void help();

};
void main()
{
   front();
   sleep(1);
   int gd = DETECT, gm;
   initgraph(&gd, &gm,"c:\\turboc3\\bgi");
   draw d;
   d.process();
   getch();
}
void draw :: process()
{
   int i, j, x, y, r, c;
   appearance();
   setviewport(rx+8, yp, X-6, Y-6, 1);
   dots();
   showmouse();
   close_help = 0;
   for(i=0; i<10; i++)
       for(j=0; j<10; j++)
	       pos[i][j] = 'z';
   setcolor(15);
   for(;;)
   {
       showmouse();
       getmouse(&button, &lx, &ly);
       if( (button & 1) == 1 )
       {
	   hidemouse();
	   for(j=0; j<=8; j++)                             // GATES AND ERASER
	       if( (lx>8)&&(ly>a[j])&&(lx<len)&&(ly<a[j]+br) )
		   job = j+1;
	   if( (lx>5)&&(ly>336)&&(lx<rx-20)&&(ly<365) )    // 0
	       job = 10;
	   if( (lx>rx-20)&&(ly>336)&&(lx<rx)&&(ly<365) )   // 1
	       job = 11;
	   if( (lx>4)&&(ly>385)&&(lx<46)&&(ly<413) )       // FIND
	       job = 12;
	   if( (lx>4)&&(ly>430)&&(lx<46)&&(ly<458) )       //CLEAR
	       job = 13;
	   if( (lx>X-44)&&(ly>7)&&(lx<X-29)&&(ly<20) )     // ?
	       job = 14;
	   if( (lx>X-24)&&(ly>7)&&(lx<X-9)&&(ly<20) )      // X
	       exit(0);
	   dots();
	   operation();
       }
   }
}
void draw :: operation()
{
   int i, j, cx, cy, c1, c2;
   cx = lx;
   cy = ly;
   if(lx < xp+30)                      // condition is necessary to avoid drawing while clicking the button
       lx = 641;
   for(i=0; i<12; i++)                 // this loop changes lx to the appropriate one
   {
       if(lx+15 < pixx[i])
       {
	   lx = pixx[i-2];
	   break;
       }
   }
   for(i=0; i<=10; i++)                // this loop changes ly appropriately
   {
       if(ly < pixy[i])
       {
	   ly = pixy[i-1];
	   break;
       }
   }
   if(job == 1)
       and();
   if(job == 2)
       or();
   if(job == 3)
       not();
   if(job == 4)
       nand();
   if(job == 5)
	nor();
   if(job == 6)
       xor();
   if(job == 7)
       xnor();
   if(job == 8)
       Line();
   if(job == 9)
       rub();
   if(job == 10)
       give_IO(job, cx, cy);
   if(job == 11)
       give_IO(job, cx, cy);
   if(job == 12)
       find();
   if(job == 13)
       clear();
   if(job == 14)
       help();
   if(job != 14 && close_help == 1)         // closes the help window
   {
       setfillstyle(1, 0);
       close_help = 0;
       bar(50, 57, 525, 390);
       reDraw();
   }
}
void draw :: and()
{
   setcolor(10);
   line(lx, ly, lx, ly-20);                 // AND
   line(lx, ly, lx+10, ly);
   line(lx, ly-20, lx+10, ly-20);
   arc(lx+12, ly-10, 260, 100, 10);
   line(lx+22, ly-10, lx+25, ly-10);
   line(lx-3, ly-17, lx, ly-17);
   line(lx-3, ly-3, lx, ly-3);
   os = assign(lx, ly);
   pos[os.y][os.x] = 'a';
}
void draw :: or()
{
   setcolor(11);
   arc(lx-16, ly-10, 330, 30, 18);          //OR
   line(lx, ly, lx+10, ly);
   line(lx, ly-20, lx+10, ly-20);
   arc(lx-3, ly-35, 293, -41, 37);
   arc(lx-3, ly+15, 45, 67, 37);
   line(lx+24, ly-10, lx+27, ly-10);
   line(lx-3, ly-17, lx, ly-17);
   line(lx-3, ly-3, lx, ly-3);
   os = assign(lx, ly);
   pos[os.y][os.x] = 'b';
}
void draw :: not()
{
   setcolor(7);                             // NOT
   line(lx, ly, lx, ly-20);
   line(lx, ly, lx+10, ly-10);
   line(lx, ly-20, lx+10, ly-10);
   circle(lx+13, ly-10, 2);
   line(lx+16, ly-10, lx+18, ly-10);
   line(lx-3, ly-10, lx, ly-10);
   os = assign(lx, ly);
   pos[os.y][os.x] = 'c';
}
void draw :: nand()
{
   setcolor(13);
   line(lx, ly, lx, ly-20);                 // NAND
   line(lx, ly, lx+10, ly);
   line(lx, ly-20, lx+10, ly-20);
   arc(lx+12, ly-10, 260, 100, 10);
   circle(lx+25, ly-10, 2);
   line(lx+27, ly-10, lx+30, ly-10);
   line(lx-3, ly-17, lx, ly-17);
   line(lx-3, ly-3, lx, ly-3);
   os = assign(lx, ly);
   pos[os.y][os.x] = 'd';
}
void draw :: nor()
{
   setcolor(9);
   arc(lx-16, ly-10, 330, 30, 18);          // NOR
   line(lx, ly, lx+9, ly);
   line(lx, ly-20, lx+9, ly-20);
   arc(lx-4, ly-35, 293, -41, 37);
   arc(lx-4, ly+15, 45, 67, 37);
   circle(lx+26, ly-10, 2);
   line(lx+29, ly-10, lx+31, ly-10);
   line(lx-3, ly-17, lx, ly-17);
   line(lx-3, ly-3, lx, ly-3);
   os = assign(lx, ly);
   pos[os.y][os.x] = 'e';
}
void draw :: xor()
{
   setcolor(14);
   arc(lx-16, ly-10, 330, 30, 18);          // XOR
   arc(lx-13, ly-10, 330, 30, 18);
   line(lx+3, ly, lx+10, ly);
   line(lx+3, ly-20, lx+10, ly-20);
   arc(lx-3, ly-35, 293, -41, 37);
   arc(lx-3, ly+15, 45, 67, 37);
   line(lx+24, ly-10, lx+27, ly-10);
   line(lx-3, ly-17, lx, ly-17);
   line(lx-3, ly-3, lx, ly-3);
   os = assign(lx, ly);
   pos[os.y][os.x] = 'f';
}
void draw :: xnor()
{
   setcolor(12);
   arc(lx-16, ly-10, 330, 30, 18);       // XNOR
   arc(lx-13, ly-10, 330, 30, 18);
   line(lx+3, ly, lx+9, ly);
   line(lx+3, ly-20, lx+9, ly-20);
   arc(lx-4, ly-35, 293, -41, 37);
   arc(lx-4, ly+15, 45, 67, 37);
   circle(lx+26, ly-10, 2);
   line(lx+29, ly-10, lx+31, ly-10);
   line(lx-3, ly-17, lx, ly-17);
   line(lx-3, ly-3, lx, ly-3);
   os = assign(lx, ly);
   pos[os.y][os.x] = 'g';
}
struct store draw :: assign(int ax, int ay)      // creates a 10 X 10 matrix.
{
   int i, j;
   struct store s;
   for(i=30, j=0; i<=530; i+=55, j++)
       if(ax == i)
	   s.x = j;
   for(i=27, j=0; i<=441; i+=46, j++)
       if(ay == i)
	   s.y = j;
   return s;
}
void draw :: Line()
{
   int tx, ty, x1, y1, x2, y2, x3, y3;
   showmouse();
   getmouse(&button, &lx, &ly);
   if(button & 1 == 1)
   {
       hidemouse();
       x3=x1=x2=lx;
       y3=y1=y2=ly;
       setcolor(I_O);
       line(x1-xp, y1-yp, x2-xp, y2-26);
       getmouse(&button, &lx, &ly);
       while(button == 1)
       {
	   if(x3!=lx || y3!=ly)
	   {
	       setcolor(0);
	       line(x1-xp, y1-yp, x2-xp, y2-26);
	       x2=lx;
	       y2=ly;
	       setcolor(I_O);
	       line(x1-xp, y1-yp, x2-xp, y2-26);
	   }
	   getmouse(&button, &lx, &ly);
       }
       showmouse();
   }
}
void draw :: rub()
{
   int x1, y1;
   showmouse();
   getmouse(&button, &lx, &ly);
   if(button & 1 == 1)
   {
       hidemouse();
       x1=lx;
       y1=ly;
       setfillstyle(SOLID_FILL, 0);
       setcolor(15);
       while(button == 1)
       {
	   rectangle(x1-xp, y1-9, lx-(xp-10), ly-(yp+3));
	   bar(x1-xp, y1-9, lx-(xp-10), ly-(yp+3));
	   if(lx<590 && ly<470)                            // condition is necessary for preventing abnormal program termination
	       Delete();
	   x1=lx;
	   y1=ly;
	   getmouse(&button, &lx, &ly);
       }
       showmouse();
   }
}
void draw :: Delete()                  // removes the gate from the matrix when erased
{
   struct store d;
   int i, j, k, l;
   for(i=0; i<12; i++)
   for(j=lx-xp; j<lx-xp+10; j++)
   if(pixx[i] == j)
   for(k=0; k<11; k++)
   for(l=ly+yp; l<ly+yp+15; l++)
   if(pixy[k] == l)
   {
       d = assign(pixx[i], pixy[k-1]);
       pos[d.y][d.x] = 'z';
   }
}
void draw :: give_IO(int jo, int sx, int sy)
{
   int xc, yc, co;
   reDraw();
   xc = sx-xp;
   yc = sy-yp;
   if(jo == 10)
       co = Z;
   else if(jo == 11)
       co = O;
   if(sx > rx)                                   // avoids drawing while clicking the button
   {
       while( getpixel(xc, yc) == I_O )
       {
	   putpixel(xc, yc, co);
	   if( getpixel(xc+1, yc) == I_O )
	       xc = xc + 1;
	   if( getpixel(xc+1, yc-1) == I_O)
	   {
	       xc = xc + 1;
	       yc = yc - 1;
	   }
	   if(getpixel(xc+1, yc+1) == I_O)
	   {
	       xc = xc + 1;
	       yc = yc + 1;
	   }
       }
   }
   xc = sx - xp - 1;
   yc = sy - yp;
   if(sx > rx)
   {
       while( getpixel(xc, yc) == I_O )
       {
	   putpixel(xc, yc, co);
	   if( getpixel(xc-1, yc) == I_O )
	       xc = xc - 1;
	   if( getpixel(xc-1, yc-1) == I_O)
	   {
	       xc = xc - 1;
	       yc = yc - 1;
	   }
	   if(getpixel(xc-1, yc+1) == I_O)
	   {
	       xc = xc - 1;
	       yc = yc + 1;
	   }
       }
   }
}
void draw :: find()
{
   int no, r, c, col=0, fx, ok=0, repeat=0;
   struct store get;
   for(r=0; r<10; r++)
       for(c=0; c<10; c++)
	   if(pos[r][c] != 'z')
	       repeat++;
   for(no=0; no<repeat; no++)
   for(r=0; r<10; r++)
   {
       for(c=0; c<10; c++)
       {
	   if(pos[r][c] == 'a')
	   {
	       get = identifyInput(pixx[c], pixy[r]);
	       if(  (get.x == O) && (get.y == O) )
		   col = O;
	       else if( ((get.x == O) && (get.y == Z))  || ((get.x == Z) && (get.y == O))  || ((get.x == Z) && (get.y == Z))  )
		   col = Z;
	       if( ((get.x != O) && (get.x != Z)) || ((get.y != O) && (get.y != Z)) )
		   ok = 1;
	       else ok = 0;
	       fx = pixx[c] + 26;                          // fx is the pixel position from where the output line starts
	       if(ok == 0)
		   changeColor(fx, pixy[r], col);          // changes the color of output i.e., gives the output
	   }
	   else if(pos[r][c] == 'b')
	   {
	       get = identifyInput(pixx[c], pixy[r]);
	       if(  ((get.x == O) && (get.y == O)) || ((get.x == O) && (get.y == Z))  || ((get.x == Z) && (get.y == O)) )
		   col = O;
	       else if( (get.x == Z) && (get.y == Z) )
		   col = Z;
	       if( ((get.x != O) && (get.x != Z)) || ((get.y != O) && (get.y != Z)) )
		   ok = 1;
	       else ok = 0;
	       fx = pixx[c] + 28;
	       if(ok == 0)
		   changeColor(fx, pixy[r], col);
	   }
	   else if(pos[r][c] == 'c')
	   {
	       get.x = getpixel(pixx[c]-4, pixy[r]-10);
	       if(get.x == O)
		   col = Z;
	       else if(get.x == Z)
		   col = O;
	       if( (get.x != O) && (get.x != Z) )
		   ok = 1;
	       else ok = 0;
	       fx = pixx[c] + 19;
	       if(ok == 0)
		   changeColor(fx, pixy[r], col);
	   }
	   else if(pos[r][c] == 'd')
	   {
	       get = identifyInput(pixx[c], pixy[r]);
	       if(  (get.x == O) && (get.y == O) )
		   col = Z;
	       else if( ((get.x == O) && (get.y == Z))  || ((get.x == Z) && (get.y == O))  || ((get.x == Z) && (get.y == Z))  )
		   col = O;
	       if( ((get.x != O) && (get.x != Z)) || ((get.y != O) && (get.y != Z)) )
		   ok = 1;
	       else ok = 0;
	       fx = pixx[c] + 31;
	       if(ok == 0)
		   changeColor(fx, pixy[r], col);
	   }
	   else if(pos[r][c] == 'e')
	   {
	       get = identifyInput(pixx[c], pixy[r]);
	       if(  ((get.x == O) && (get.y == O)) || ((get.x == O) && (get.y == Z))  || ((get.x == Z) && (get.y == O)) )
		   col = Z;
	       else if( (get.x == Z) && (get.y == Z) )
		   col = O;
	       if( ((get.x != O) && (get.x != Z)) || ((get.y != O) && (get.y != Z)) )
		   ok = 1;
	       else ok = 0;
	       fx = pixx[c] + 32;
	       if(ok == 0)
		   changeColor(fx, pixy[r], col);
	   }
	   else if(pos[r][c] == 'f')
	   {
	       get = identifyInput(pixx[c], pixy[r]);
	       if( ((get.x == O) && (get.y == O)) || ((get.x == Z) && (get.y == Z)) )
		   col = Z;
	       else if( ((get.x == O) && (get.y == Z)) || ((get.x == Z) && (get.y == O)) )
		   col = O;
	       if( ((get.x != O) && (get.x != Z)) || ((get.y != O) && (get.y != Z)) )
		   ok = 1;
	       else ok = 0;
	       fx = pixx[c] + 28;
	       if(ok == 0)
		   changeColor(fx, pixy[r], col);
	   }
	   else if(pos[r][c] == 'g')
	   {
	       get = identifyInput(pixx[c], pixy[r]);
	       if( ((get.x == O) && (get.y == O)) || ((get.x == Z) && (get.y == Z)) )
		   col = O;
	       else if( ((get.x == O) && (get.y == Z)) || ((get.x == Z) && (get.y == O)) )
		   col = Z;
	       if( ((get.x != O) && (get.x != Z)) || ((get.y != O) && (get.y != Z)) )
		   ok = 1;
	       else ok = 0;
	       fx = pixx[c] + 32;
	       if(ok == 0)
		   changeColor(fx, pixy[r], col);
	   }
       }
   }
}
struct store draw :: identifyInput(int x, int y)         //gets the color of the two inputs
{
   int y1, y2;
   struct store in;
   x = x - 4;
   y1 = y - 17;
   y2 = y - 3;
   in.x = getpixel(x, y1);
   in.y = getpixel(x, y2);
   return in;
}
void draw :: changeColor(int cx, int cy, int ccol)         // changes the color of the o/p i.e, gives the result
{
   cy = cy - 10;
   while( (getpixel(cx, cy) == I_O) )
   {
       putpixel(cx, cy, ccol);
       delay(10);
       if( getpixel(cx+1, cy) == I_O)
	   cx = cx + 1;
       else if( getpixel(cx, cy+1) == I_O)
	   cy = cy + 1;
       else if( getpixel(cx, cy-1) == I_O)
	   cy = cy - 1;
       else if( getpixel(cx-1, cy) == I_O)
	   cx = cx - 1;
       else if( getpixel(cx+1, cy+1) == I_O)
       {
	   cx = cx + 1;
	   cy = cy + 1;
       }
       else if( getpixel(cx+1, cy-1) == I_O)
       {
	   cx = cx + 1;
	   cy = cy - 1;
       }
       else if( getpixel(cx-1, cy+1) == I_O)
       {
	   cx = cx - 1;
	   cy = cy + 1;
       }
       else if( getpixel(cx-1, cy-1) == I_O)
       {
	   cx = cx - 1;
	   cy = cy - 1;
       }
   }
}
void draw :: clear()
{
   int r, c;
   setfillstyle(SOLID_FILL, 16);
   bar(0, 0, X-6, Y-6);
   dots();
   for(r=0; r<10; r++)                    // CLEARING THE MATRIX and setting all positions as zero i.e, 'z'
       for(c=0; c<10; c++)
	   pos[r][c] = 'z';
}
void draw :: help()
{
   close_help = 1;
   setcolor(9);
   rectangle(50, 57, 525, 390);        // HELP - rectangle
   setfillstyle(1, 1);
   bar(51, 58, 524, 77);               // TITLE BAR
   line(50, 78, 525, 78);

   setfillstyle(1, 7);                 // SPACE
   bar(51, 79, 524, 389);
   settextstyle(0, 0, 0);
   setcolor(11);
   outtextxy(60, 68, "? HELP");

   setcolor(7);
   rectangle(501, 61, 519, 74);        // X
   setfillstyle(1, 8);
   bar(502, 62, 518, 73);
   settextstyle(0, 0, 0);
   setcolor(15);
   outtextxy(507, 68, "x");

   settextstyle(0, 0, 0);
   setcolor(0);
   outtextxy(64, 90, "WELCOME TO HELP");
   line(63, 95, 183, 95);

   settextstyle(2, 0, 0);
   outtextxy(64, 104, "This program can be used for processing simple digital logic gates.");  //64, 102
   outtextxy(64, 117, "100 gates can be drawn at the specific location represented by two dots."); // 64, 120
   settextstyle(2, 0, 0);
   outtextxy(64, 137, "PROCEDURE :");
   line(63, 144, 126, 144);
   outtextxy(64, 155, "1. Draw the gates in the desired position.");
   outtextxy(64, 167, "2. Represent the inputs & outputs by straight lines.");
   outtextxy(64, 179, "3. Also represent the connections between the gates using straight lines.");
   outtextxy(64, 191, "4. Draw the connections in such a way that the lines do not intersect.");
   outtextxy(64, 203, "5. Use SMOOTH lines to get the correct result.");
   outtextxy(64, 215, "6. After drawing the circuit, give the inputs to the gates at the EXTREME LEFT");
   outtextxy(64, 227, "   alone, ");
   outtextxy(64, 239, "      - click the button - 0 and then click on the lines, to which, the input");
   outtextxy(64, 251, "        zero should be given");
   outtextxy(64, 263, "      - click the button - 1 and then click on the lines, to which, the input");
   outtextxy(64, 275, "        one should be given");
   outtextxy(64, 287, "7. Finally click the button FIND to get the outputs of all the other gates.");
   outtextxy(265, 305, "Your final drawing should look like this.");
   outtextxy(243, 306, "<");
   outtextxy(245, 305, "ÄÄ");
   setcolor(10);
   line(130, 325, 130, 325-20);                 // AND - HELP
   line(130, 325, 130+10, 325);
   line(130, 325-20, 130+10, 325-20);
   arc(130+12, 325-10, 260, 100, 10);
   line(130+22, 325-10, 130+25, 325-10);
   line(130-3, 325-17, 130, 325-17);
   line(130-3, 325-3, 130, 325-3);

   setcolor(11);
   arc(130-16, 379-10, 330, 30, 18);             //OR - HELP
   line(130, 379, 130+10, 379);
   line(130, 379-20, 130+10, 379-20);
   arc(130-3, 379-35, 293, -41, 37);
   arc(130-3, 379+15, 45, 67, 37);
   line(130+24, 379-10, 130+27, 379-10);
   line(130-3, 379-17, 130, 379-17);
   line(130-3, 379-3, 130, 379-3);

   setcolor(14);
   arc(220-16, 352-10, 330, 30, 18);             // XOR - HELP
   arc(220-13, 352-10, 330, 30, 18);
   line(220+3, 352, 220+10, 352);
   line(220+3, 352-20, 220+10, 352-20);
   arc(220-3, 352-35, 293, -41, 37);
   arc(220-3, 352+15, 45, 67, 37);
   line(220+24, 352-10, 220+27, 352-10);
   line(220-3, 352-17, 220, 352-17);
   line(220-3, 352-3, 220, 352-3);

   line(100, 322, 130-4, 322);
   line(100, 308, 130-4, 308);

   line(100, 376, 130-4, 376);
   line(100, 362, 130-4, 362);

   setcolor(I_O);
   line(130+26, 315, 130+60, 315);
   line(130+28, 369, 130+60, 369);

   line(220-30, 335, 130+60, 315);
   line(190, 349, 190, 369);

   line(220-4, 335, 220-30, 335);
   line(220-4, 349, 220-30, 349);

   line(220+28, 352-10, 220+60, 352-10);

   setcolor(0);
   outtextxy(417, 340, "Click Here");
   setcolor(1);
   rectangle(415, 350, 475, 375);                // TEST button - HELP
   setfillstyle(1, 9);
   bar(416, 351, 474, 374);
   line(474, 351, 474, 374);
   line(415, 374, 475, 374);
   setcolor(15);
   settextstyle(0, 0, 0);
   outtextxy(430, 363, "TEST");

   setcolor(O);
   line(100, 322, 130-4, 322);
   line(100, 362, 130-4, 362);
   setcolor(Z);
   line(100, 376, 130-4, 376);
   line(100, 308, 130-4, 308);

   getmouse(&button, &lx, &ly);
   if(button == 1)
   {
       if(lx-xp>501 && ly-yp>61 && lx-xp<519 && ly-yp<74)  // closes help when X is pressed
       {
	   setfillstyle(1, 0);
	   bar(50, 57, 525, 390);
	   reDraw();
	   job = 100;
       }
       else if( (lx<103 && ly>yp && ly<474 ) || (lx>578 && lx<634 && ly>yp
		 && ly<474) || (lx<634 && ly>yp && ly<83)
		     || (lx<634 && ly>417 && ly<474) )     // closes help
       {
	   setfillstyle(1, 0);
	   bar(50, 57, 525, 390);
	   reDraw();
	   job = 100;
       }
       else if(lx-xp>415 && ly-yp>350 && lx-xp<475 && ly-yp<375)
       {
	   changeColor(156, 325, Z);
	   changeColor(158, 379, O);
	   changeColor(248, 352, O);
       }
   }
}
void draw :: reDraw()                           // redraws the gates in the specific location
{
   int i, j;
   for(i=0; i<10; i++)
       for(j=0; j<10; j++)
	   if(pos[i][j] != 'z')
	   {
	       lx = pixx[j];
	       ly = pixy[i];
	       if(pos[i][j] == 'a')
		   and();
	       if(pos[i][j] == 'b')
		   or();
	       if(pos[i][j] == 'c')
		   not();
	       if(pos[i][j] == 'd')
		   nand();
	       if(pos[i][j] == 'e')
		   nor();
	       if(pos[i][j] == 'f')
		   xor();
	       if(pos[i][j] == 'g')
		   xnor();
	   }
}
void draw :: dots()
{
   int i, j, k, l, m=0;
   for(i=30, l=0; i<=578; i+=42+13, l++)
   {
       j = 7;
       k = 0;
       pixx[l] = i;
       while(j <= 470)
       {
	   k++;
	   putpixel(i, j, DOTS);
	   if(k % 2 != 0)
	   {
	       j+=20;
	       pixy[m++] = j;
	   }
	   else
	       j+=26;
       }
   }
   pixx[10] = 557;
   pixx[11] = 612;
}
void draw :: appearance()
{
    int i, j=0, r=0;
    int yend, l;
    X = getmaxx();
    Y = getmaxy();
    rx = 45;
    ry = 3 * Y / 4;
    len = 42;                          // length of tool box
    br = ry/11;                        // breadth of box
/*----------------------------------------------------------------------------------*/
    setfillstyle(SLASH_FILL, 3);
    bar(2, 3, X-3, 25);                          // TITLE  SLASH

    setfillstyle(SOLID_FILL, 8);                 // X
    setcolor(7);
    rectangle(X-24, 7, X-9, 20);
    bar(X-23, 8, X-10, 19);

    rectangle(X-44, 7, X-29, 20);                // ?
    bar(X-43, 8, X-30, 19);
    setcolor(15);
    outtextxy(X-20, 9, "x");
    outtextxy(X-39, 10, "?");

    setcolor(7);
    for(i=0; i<=4; i++)
    {
	rectangle(0+i, 0+i, X-i, Y-i);           //border
	if(i>=2)
	   setcolor(9);
    }

    line(4, 23, X-3, 23);
    line(4, 24, X-3, 24);
    setcolor(11);
    settextstyle(1, 0, 1);
    settextjustify(CENTER_TEXT, CENTER_TEXT);
    outtextxy(X/2, 10, "DIGITAL  LOGIC  GATES");
    setfillstyle(SOLID_FILL, 1);
    bar(rx+1, 25, rx+6, Y-5);

    setcolor(11);
    rectangle(rx+7, 25, X-5, Y-5);               // space for drawing
    setfillstyle(INTERLEAVE_FILL, 1);
    setcolor(15);
    for(i=yp+2; (i<=ry-2 && r!=9); i+=br)
    {
       r++;
       rectangle(8, i, len, i+br-3);
       bar(9, i+1, len-1, i+br-4);
       a[j++] = i;
       if(r == 9)
	   yend = i+br;
    }
    rectangle(5, yp-1, rx, yend);

    setcolor(7);
    rectangle(5, 336, rx-20, 365);               // Input - 0
    setcolor(7);
    line(5, 333, 45, 333);
    line(5, 368, 45, 368);
    setfillstyle(6, Z);
    bar(6, 337, rx-21, 364);
    setcolor(15);
    outtextxy(15, 347, "O");

    setcolor(7);
    rectangle(rx-20, 336, rx, 365);              //Input - 1
    setfillstyle(6, O);
    bar(rx-19, 337, rx-1, 364);
    setcolor(15);
    outtextxy(36, 347, "1");

    setfillstyle(4, 1);
    settextstyle(0,0,1);
    settextjustify(LEFT_TEXT, CENTER_TEXT);

    setcolor(3);
    rectangle(4, 385, 46, 413);                  // FIND
    bar(5, 386, 45, 412);
    setcolor(7);
    line(4, 412, 46, 412);
    line(45, 385, 45, 413);
    setcolor(11);
    outtextxy(10, 400, "FIND");

    setcolor(3);
    rectangle(4, 430, 46, 458);                  //CLEAR
    bar(5, 431, 45, 457);
    setcolor(7);
    line(4, 457, 46, 457);
    line(45, 430, 45, 458);
    setcolor(11);
    outtextxy(6, 444, "CLEAR");

    setcolor(11);
    l = len/2;
    arc(l+5, a[0]+15, 260, 100, 7);              //AND
    line(l-3, a[0]+8, l+3, a[0]+8);
    line(l-3, a[0]+22, l+3, a[0]+22);
    line(l-3, a[0]+8, l-3, a[0]+22);

    arc(l-15, a[1]+15, 330, 30, 12);             //OR
    line(l-5, a[1]+8, l+2, a[1]+8);
    line(l-5, a[1]+22, l+2, a[1]+22);
    arc(l-10, a[1]-10, 293, -45, 35);
    arc(l-10, a[1]+40, 45, 67, 35);

    line(l-6, a[2]+8, l+9, a[2]+15);             //NOT
    line(l-6, a[2]+22, l+9, a[2]+15);
    line(l-6, a[2]+8, l-6, a[2]+22);
    circle(l+11, a[2]+15, 2);

    arc(l+2, a[3]+15, 260, 100, 7);              //NAND
    line(l-6, a[3]+8, l, a[3]+8);
    line(l-6, a[3]+22, l, a[3]+22);
    line(l-6, a[3]+8, l-6, a[3]+22);
    circle(l+11, a[3]+15, 2);

    arc(l-17, a[4]+15, 330, 30, 12);             //NOR
    line(l-7, a[4]+8, l-1, a[4]+8);
    line(l-7, a[4]+22, l-1, a[4]+22);
    arc(l-13, a[4]-10, 293, -45, 35);
    arc(l-13, a[4]+40, 45, 67, 35);
    circle(l+12, a[4]+15, 2);

    arc(l-17, a[5]+15, 330, 30, 12);             //XOR
    arc(l-13, a[5]+15, 330, 30, 12);
    line(l-4, a[5]+8, l+2, a[5]+8);
    line(l-4, a[5]+22, l+2, a[5]+22);
    arc(l-10, a[5]-10, 293, -45, 35);
    arc(l-10, a[5]+40, 45, 67, 35);

    arc(l-18, a[6]+15, 330, 30, 12);             //XNOR
    arc(l-14, a[6]+15, 330, 30, 12);
    line(l-5, a[6]+8, l-1, a[6]+8);
    line(l-5, a[6]+22, l-1, a[6]+22);
    arc(l-13, a[6]-10, 293, -45, 35);
    arc(l-13, a[6]+40, 45, 67, 35);
    circle(l+12, a[6]+15, 2);

    line(12, a[7]+4, 35, a[7]+25);               //LINE

    settextstyle(2,0,2);                         //ERASER
    outtextxy(14, a[8]+13, "ERASER");
}
void initmouse()
{
   i.x.ax = 0;
   int86(0x33, &i, &o);
}
void hidemouse(void)
{
   i.x.ax=2;
   int86(0x33,&i,&o);
}
void showmouse()
{
   i.x.ax = 1;
   int86(0x33, &i, &o);
}
void getmouse(int *button,int *lx,int *ly)
{
   i.x.ax=3;
   int86(0x33,&i,&o);
   *button=o.x.bx;
   *lx=o.x.cx;
   *ly=o.x.dx;
}
void front()
{
   clrscr();
   int i, j, s, BK=0, BORDER=7, N=2;
   char name[15], title[35], au[10];
   strcpy(title, "SIMULATION OF DIGITAL LOGIC GATES");
   strcpy(name, "MOHD TAUHID MANSOORI");
   strcpy(au, "Author");
   textcolor(BK);
   for(i=0; i<2000; i++)
       cprintf("Û");
   textbackground(BK);
   gotoxy(2, 1);                                 // border
   textcolor(BORDER);
   cprintf("É");
   for(i=0; i<76; i++)
       cprintf("Í");
   cprintf("»");
   for(i=0; i<24; i++)
   {
       gotoxy(79, 2+i);
       cprintf("º");
   }
   gotoxy(79, 25);
   cprintf("¼");
   for(i=0; i<76; i++)
   {
       gotoxy(3+i, 25);
       cprintf("Í");
   }
   gotoxy(2, 25);
   cprintf("È");
   for(i=0; i<23; i++)
   {
       gotoxy(2, i+2);
       cprintf("º");
   }
   sleep(2);
   textcolor(10);                                // underline
   for(i=0; i<35; i++)
   {
       gotoxy(22+i, 6);
       cprintf("Ä");
   }
   for(j=0; j<33; j++)                           // Title
   for(i=-1; i<5; i++)
   {
      textcolor(2);
      s = (0.5*i + 10);
      gotoxy(11+s+j, s-7);
      cprintf("%c", title[j]);
      if( (j != 10) && (j != 13) && (j != 21) && (j != 27) )
      delay(10);
      textcolor(BLACK);
      gotoxy(11+s+j, s-7);
      if(i != 4)
      cprintf("%c", title[j]);
   }
   textcolor(2);
   gotoxy(28, 8);
   cprintf("PROGRAM COMPOSED IN C++");
   textcolor(7);
   for(i=0; i<31; i++)
   {
       gotoxy(24+i, 14);
       cprintf("Û");
   }
   for(i=0; i<6; i++)                            // Author
   {
       textcolor(8);
       gotoxy(35+i, 20);
       cprintf("%c", au[i]);
       delay(100);
       gotoxy(35+i, 20);
       textcolor(7);
       cprintf("%c", au[i]);
       delay(100);
       gotoxy(35+i, 20);
       textcolor(15);
       cprintf("%c", au[i]);
   }
   for(i=13; i>=0; i--)
   {
       textcolor(15);
       gotoxy(31+i,21);
       cprintf("%c", name[i]);
       delay(100);
       textcolor(0);
       gotoxy(31+i,21);
       cprintf(" ");
   }
   for(i=0; i<14; i++)
   {
       textcolor(15);
       gotoxy(31+i,21);
       cprintf("%c", name[i]);
       delay(100);
       textcolor(N);
       gotoxy(31+i,21);
       cprintf("%c", name[i]);
   }
   gotoxy(31, 21);
   textattr(N + (8 << 4));
   cprintf("MOHD TAUHID MANSOORI");
   textcolor(7);
   sleep(1);
   gotoxy(24, 13);
   cprintf("Loading...");
   gotoxy(37, 16);
   cprintf("0%");
   sleep(1);
   for(i=0, j=30; i<31; i++, j--)
   {
       gotoxy(24+i, 14);
       delay(10*j);
       textcolor(2);
       cprintf("Û");
       gotoxy(36, 16);
       textcolor(7);
       cprintf("%d%", i*3+10);
   }
}
