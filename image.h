typedef struct {
  unsigned short type;
  unsigned int size;
  unsigned short reserved1;
  unsigned short reserved2;
  unsigned int offsetbits;
} BITMAPFILEHEADER1;

typedef struct {
  unsigned int size;
  unsigned int width;
  unsigned int height;
  unsigned short planes;
  unsigned short bitcount;
  unsigned int compression;
  unsigned int sizeimage;
  int xpelspermeter;
  int ypelspermeter;
  unsigned int colorsused;
  unsigned int colorsimportant;
} BITMAPINFOHEADER1;

/* Struktura za smestanje podataka o slici. */
typedef struct Image {
  int width, height; /* Dimenzije slike. */
  char *pixels; /* Niz u kojem se cuvaju podaci za sve piksele u obliku (R, G, B). */
} Image;

/* Funkcija koja inicijalizuje strukturu i vraca pokazivac na nju. */
Image *image_init(int width, int height);

// Funkcija koja oslobadja prostor 
void image_done(Image *image);

// Funkcija za ucitavanje podataka o slici
void image_read(Image *image);

