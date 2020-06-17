#include "model.h"
#include "func.h"
#include "image.h"

//funkcija za iscrtavanje jedne stranice jedne male kocke i bojenje 
void draw_part(float* a, float* b, float* c, float* d, int part) {


	//u zavisnosti od polozaja date stranice (part) bojimo stranicu u jednu od 6 boja kocke
	// u slucaju da je vrednost 6, znaci da je stranica u unutrasnjosti velike kocke i bojimo je u crno
	//sve stranice sa istom (part) vrednoscu su zapravo stranice jedne iste boje
	if (part == 0)
		glColor3f(0.7,0,0);
	if (part == 1)
		glColor3f(0,0.5,0);
	if (part == 2)
		glColor3f(1,1,1);
	if (part == 3)
		glColor3f(0,0,0.5);
	if (part == 4)
		glColor3f(0.5,0.5,0.0);
	if (part == 5)
		glColor3f(0,0.5,0.5);
	if (part == 6)
		glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_QUADS);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();

}



//funkcija koja iscrtava jednu malu kocku i boji je u boje koristeci funkciju iznad
void drawCube(float* a, float* b, float* c, float* d,
	float* e, float* f, float* g, float* h,
	int x, int y, int z) {

	int front = 6, back = 6, left = 6, right = 6, up = 6, down = 6;

	/*
	0-5 - 6 razlicitih boja za kocku
	6 - unutrasnje koje se ne boje (boje u crno)
	*/

	if (z == 0)
		front = kocka.faces[0][y][x];
	if (z == CUBE_SIZE - 1)
		back = kocka.faces[1][y][CUBE_SIZE - 1 - x];

	if (y == 0)
		up = kocka.faces[4][CUBE_SIZE - 1 - z][x];
	if (y == CUBE_SIZE - 1)
		down = kocka.faces[5][z][x];

	if (x == 0)
		left = kocka.faces[2][y][CUBE_SIZE - 1 - z];
	if (x == CUBE_SIZE - 1)
		right = kocka.faces[3][y][z];

	
	draw_part(a, b, c, d, front);
	
	draw_part(f, e, h, g, back);		
	
	draw_part(e, a, d, h, left);
	
	draw_part(b, f, g, c, right);	
	
	draw_part(e, f, b, a, up);	
	
	draw_part(d, c, g, h, down);		

}


//funkcija koja gradi rubikovu kocku od svih manjih kockica pomocu funkcije iznad

void buildRubiksCube() {

	double velika = 2.0;  //velicina rubikove
	double mala = velika / CUBE_SIZE; // velicina svake od malih
	double razmak_kocke = mala * 0.05;  // razmakk izmedju svake od malih
	

	double start = velika / 2 + razmak_kocke * (CUBE_SIZE - 1) / 2;

	for (double z = start; z > -start; z -= mala + razmak_kocke) {
		for (double y = start; y > -start; y -= mala + razmak_kocke) {
			for (double x = -start; x < start; x += mala + razmak_kocke) {

				int cx = (int)round((x + velika / 2) / (mala + razmak_kocke));
				int cy = (int)round((-y + velika / 2) / (mala + razmak_kocke));
				int cz = (int)round((-z + velika / 2) / (mala + razmak_kocke));

				glPushMatrix();
				glTranslatef(8, 0, 0);
				glMultMatrixd(getRotMatrix(cubesRotation[cz][cy][cx]));
				glTranslatef(-8, 0, 0);
				float v[8][3] = {
					{ x + 8, y, z },
					{ x + mala + 8, y, z },
					{ x + mala + 8, y - mala, z },
					{ x + 8, y - mala, z },
					{ x + 8, y, z - mala },
					{ x + mala + 8, y, z - mala },
					{ x + mala + 8, y - mala, z - mala },
					{ x + 8, y - mala, z - mala }
				};

				drawCube(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], cx, cy, cz);
				glPopMatrix();
			}
		}
	}


}


//funkcije za dugmice
void animateButtons() {
		butt_start.animate(enableTransition);
		butt_exit.animate(exitProgram);
		butt_nazad.animate(enableTransition);
		butt_resi.animate(resi);
}


//funkcija za tranziciju prilikom pomeranja sa pocetnog ekrana na deo sa kockom i nazad
void doTransition(float fromX, float toX, float fromY, float toY) {

	if (isTransition) {

		if ((ceil(xscreen) == 1 || floor(xscreen) == 1) &&
			(ceil(yscreen) == 0 || floor(yscreen) == 0)) {
			camX += brzina * (toX - fromX) * (8);
			camY += brzina * (toY - fromY) * (5);
			perc += brzina;

			if (perc >= 1) {
				isTransition = false;
				fromXScreen = xscreen = toXScreen;
				fromYScreen = yscreen = toYScreen;
				perc = 0;
			}
		}
		else {
			camX += 0.001 * (toX - fromX) * (8);
			camY += 0.001 * (toY - fromY) * (5);
			perc += 0.001;

			if (perc >= 1) {
				isTransition = false;
				fromXScreen = xscreen = toXScreen;
				fromYScreen = yscreen = toYScreen;
				perc = 0;
			}
		}
	}

	glTranslatef(-camX, -camY, -camZ);
}


static GLuint name;
//funkcija za ispis teksta na pocetni ekran
void komande() {

	Image* image;

	glTexEnvf(GL_TEXTURE_ENV,
		GL_TEXTURE_ENV_MODE,
		GL_REPLACE);

	image = image_init(0, 0);

	/* Kreira se prva tekstura. */
	image_read(image);

	/* Generisu se identifikatori tekstura. */
	glGenTextures(1, &name);

	//glBindTexture(GL_TEXTURE_2D, 0);

	/* Unistava se objekat za citanje tekstura iz fajla. */
	

	glBindTexture(GL_TEXTURE_2D, name);

	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
		image->width, image->height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	image_done(image);

	glBindTexture(GL_TEXTURE_2D, name);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);

	glTexCoord2f(0, 0);
	glVertex3f(1, 0, -1);

	glTexCoord2f(1, 0);
	glVertex3f(-4, 0, -1);

	glTexCoord2f(1, 1);
	glVertex3f(-4, 2.5, -1);

	glTexCoord2f(0, 1);
	glVertex3f(1, 2.5, -1);
	glEnd();

		glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);

	glTexCoord2f(0, 0);
	glVertex3f(1, 0, -1);

	glTexCoord2f(1, 0);
	glVertex3f(5, 5, -1);

	glTexCoord2f(1, 1);
	glVertex3f(5, 2.5, -1);

	glTexCoord2f(0, 1);
	glVertex3f(1, 2.5, -1);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, 0);

	stampaj(-3.5, 2.2, "Komande:(capslock za kontrarotaciju)", 1);
	stampaj(-3.2, 1.9, "Z/z - prednja rotacija", 1);
	stampaj(-3.2, 1.6, "X/x - zadnja rotacija", 1);
	stampaj(-3.2, 1.3, "C/c - leva rotacija", 1);
	stampaj(-3.2, 1,   "V/v - desna rotacija", 1);
	stampaj(-3.2, 0.7, "B/b - gornja rotacija", 1);
	stampaj(-3.2, 0.4, "N/n - donja rotacija", 1);
	stampaj(-3.2, 0.1, "R/r - zadrzati za random mesanje kocke", 1);

}


//funkcija za ispis resenja ispod kocke
void prikazi_resenje() {

	FOR0(i, moveList.size()) {
		string s = "";
		s += moveList[i];
		stampaj(7.3 + i * 0.3, -2.2 , s, 1.5);
	}

}
