/*
MIT License

Copyright (c) 2019 Antonio "toneddu2000" Latronico

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//test C functions (not used)

//example pointer string
string *myPointerString;

//example struct
typedef struct libro
{
  string titolo;
  string autore;
  int anno_pubblicazione;
  float prezzo;
} t_libro;

//(string imagename, int width, int height, void *pixeldata, optional int datasize, optional int format)

void Pointer_TestStringInit()
{
	//call this func in CSQC_Init
	*myPointerString = "zaz";
}

void PrintString(void *ptr)
{
	
	print("My pointer string is: ",ptr,"\n");
}

void Pointer_TestStringUpdate()
{
	//call this func in CSQC_UpdateView
	PrintString((void *) *myPointerString);
}