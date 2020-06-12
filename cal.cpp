#include "cal.h"

void reshape(int w, int h) {

	double widthScale = (double)w / width, heightScale = (double)h / height;

	//podesavanje viewporta, projekcije, vidne tacke...

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-viewportX / 2 * widthScale, viewportX / 2 * widthScale, -viewportY / 2 * heightScale, viewportY / 2 * heightScale, -5, 5);
	glMatrixMode(GL_MODELVIEW);
}

void display() {

	//izdvajamo trenutno vreme koje nam treba za promenu boje pozadine(menja se u odnosu na vreme)
	const int curTime = glutGet(GLUT_ELAPSED_TIME);

	//promenljiva t koja sluzi kao parametar u promeni pozadine kako bi prelaz izmedju boja bio postepen kroz vreme
	//parametar t treba imati vrednost [0, 1]
	// parametar brzina_promene sluzi za promenu brzine kojom ce se menjati boja pozadine
	float brzina_promene = 0.0003;
	const float t = cos(float(curTime) * brzina_promene) * 0.5 + 0.5;

	
	// funkcija kojom se postepeno menja boja pozadine, prva boja je pocetna, druga je krajnja posle cega se boja menja postepeno opet ka prvoj 
	color trenutnaPozadina = prelazna(color(0.3, 0.2, 0.5), color(0.8, 0.7, 0.5), t);

	glClearColor(trenutnaPozadina.r, trenutnaPozadina.g, trenutnaPozadina.b, 1);
	


	//ciscenje bafera
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	//animacija dugmica
	animateButtons();

	doTransition(fromXScreen, toXScreen, fromYScreen, toYScreen);

		//crtanje dugmica i teksta na pocetnom ekranu
		butt_start.draw();
		butt_exit.draw();
		komande();


		//crtanje dela ekrana desno gde je kocka sa dugmicima i tekstom
		butt_nazad.draw();
		if (CUBE_SIZE == 2 || CUBE_SIZE == 3)
			butt_resi.draw();
		prikazi_resenje();
		glTranslatef(8, 0, 0);
		glMultMatrixd(getRotMatrix(camera));
		glTranslatef(-8, 0, 0);
		buildRubiksCube();

		if (rotationType) {
			novaRot();
		}
	

	glutSwapBuffers();
	glutPostRedisplay();

}

void inicijalizuj() {



	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(motion);
	glutReshapeFunc(reshape);
	FOR0(i, CUBE_SIZE) {
		FOR0(j, CUBE_SIZE) {
			FOR0(k, CUBE_SIZE) {
				cubesRotation[i][j][k] = Quaterniond{ AngleAxisd{1,Vector3d{0,0,0}} };
			}
		}
	}

}
