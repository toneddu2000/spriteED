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