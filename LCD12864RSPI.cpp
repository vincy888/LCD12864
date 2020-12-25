//Demo LCD12864 spi







#include "LCD12864RSPI.h"





extern "C" 

{

#include <Arduino.h>

//#include <wiring.h> 

#include <inttypes.h>

#include <stdio.h>  //not needed yet

#include <string.h> //needed for strlen()

#include <avr/pgmspace.h>

}







LCD12864RSPI::LCD12864RSPI() 

{

this->DEFAULTTIME = 80; // 80 ms default time

this->delaytime = DEFAULTTIME;

} 



//*********************ÑÓÊ±º¯Êý************************//

void LCD12864RSPI::delayns(void)

{   

delayMicroseconds(delaytime);

 }





void LCD12864RSPI::WriteByte(int dat)

{

    //digitalWrite(latchPin, HIGH);

    delayns();

    shiftOut(dataPin, clockPin, MSBFIRST, dat);

    //digitalWrite(latchPin, LOW);

}





void LCD12864RSPI::WriteCommand(int CMD)

{

   int H_data,L_data;

   H_data = CMD;

   H_data &= 0xf0;           //ÆÁ±ÎµÍ4Î»µÄÊý¾Ý

   L_data = CMD;             //xxxx0000¸ñÊ½

   L_data &= 0x0f;           //ÆÁ±Î¸ß4Î»µÄÊý¾Ý

   L_data <<= 4;             //xxxx0000¸ñÊ½

   WriteByte(0xf8);          //RS=0£¬Ð´ÈëµÄÊÇÖ¸Áî£»

   WriteByte(H_data);

   WriteByte(L_data);

}





void LCD12864RSPI::WriteData(int CMD)

{

   int H_data,L_data;

   H_data = CMD;

   H_data &= 0xf0;           //ÆÁ±ÎµÍ4Î»µÄÊý¾Ý

   L_data = CMD;             //xxxx0000¸ñÊ½

   L_data &= 0x0f;           //ÆÁ±Î¸ß4Î»µÄÊý¾Ý

   L_data <<= 4;             //xxxx0000¸ñÊ½

   WriteByte(0xfa);          //RS=1£¬Ð´ÈëµÄÊÇÊý¾Ý

   WriteByte(H_data);

   WriteByte(L_data);

}







void LCD12864RSPI::Initialise()

{

   // pinMode(latchPin, OUTPUT);     

    pinMode(clockPin, OUTPUT);    

    pinMode(dataPin, OUTPUT);

   // digitalWrite(latchPin, LOW);

    delayns();



    WriteCommand(0x30);        //¹¦ÄÜÉè¶¨¿ØÖÆ×Ö

    WriteCommand(0x0c);        //ÏÔÊ¾¿ª¹Ø¿ØÖÆ×Ö

    WriteCommand(0x01);        //Çå³ýÆÁÄ»¿ØÖÆ×Ö

    WriteCommand(0x06);        //½øÈëÉè¶¨µã¿ØÖÆ×Ö

}





void LCD12864RSPI::CLEAR(void)

{  

    WriteCommand(0x30);//

    WriteCommand(0x01);//Çå³ýÏÔÊ¾

}





void LCD12864RSPI::DisplayString(int X,int Y,uchar *ptr,int dat)

{

  int i;



  switch(X)

   {

     case 0:  Y|=0x80;break;



     case 1:  Y|=0x90;break;



     case 2:  Y|=0x88;break;



     case 3:  Y|=0x98;break;



     default: break;

   }

  WriteCommand(Y); // ¶¨Î»ÏÔÊ¾ÆðÊ¼µØÖ·



  for(i=0;i<dat;i++)

    { 

      WriteData(ptr[i]);//ÏÔÊ¾ºº×ÖÊ±×¢ÒâÂëÖµ£¬Á¬ÐøÁ½¸öÂë±íÊ¾Ò»¸öºº×Ö

    }

}







void LCD12864RSPI::DisplaySig(int M,int N,int sig)

{

  switch(M)

   {

     case 0:  N|=0x80;break;



     case 1:  N|=0x90;break;



     case 2:  N|=0x88;break;



     case 3:  N|=0x98;break;



     default: break;

   }

  WriteCommand(N); // ¶¨Î»ÏÔÊ¾ÆðÊ¼µØÖ·

  WriteData(sig); //Êä³öµ¥¸ö×Ö·û

 }









void LCD12864RSPI::DrawFullScreen(uchar *p)

{

      int ygroup,x,y,i;

      int temp;

      int tmp;

             

      for(ygroup=0;ygroup<64;ygroup++)           //Ð´ÈëÒº¾§ÉÏ°ëÍ¼Ïó²¿·Ö

        {                           //Ð´Èë×ø±ê

           if(ygroup<32)

            {

             x=0x80;

             y=ygroup+0x80;

            }

           else 

            {

              x=0x88;

              y=ygroup-32+0x80;    

            }         

           WriteCommand(0x34);        //Ð´ÈëÀ©³äÖ¸ÁîÃüÁî

           WriteCommand(y);           //Ð´ÈëyÖá×ø±ê

           WriteCommand(x);           //Ð´ÈëxÖá×ø±ê

           WriteCommand(0x30);        //Ð´Èë»ù±¾Ö¸ÁîÃüÁî

           tmp=ygroup*16;

           for(i=0;i<16;i++)

		 {

		    temp=p[tmp++];

		    WriteData(temp);

               }

          }

        WriteCommand(0x34);        //Ð´ÈëÀ©³äÖ¸ÁîÃüÁî

        WriteCommand(0x36);        //ÏÔÊ¾Í¼Ïó

}





LCD12864RSPI LCDA = LCD12864RSPI();
