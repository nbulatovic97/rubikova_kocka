#include "key_mou.h"

//tipke na tastaruri
void keyboard(unsigned char key, int x, int y) {


	if (xscreen == 1 && yscreen == 0) {
		if (rotationType == 0) {
			if (key == 'r' || key == 'R') {
				int cacheLayer = layer;
				FOR(i, 1, 1) {
					layer = rand() % (CUBE_SIZE / 2);
					rotationType = 1 + rand() % 12;
					prState();
				}
				layer = cacheLayer;
			}

			if (key == 'Z') {
				rotationAxis = { 0, 0, 1 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(j, i, layer));
				}
				if (rorationSpeed < 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 1;
			}
			else if (key == 'z') {
				rotationAxis = { 0, 0, 1 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(j, i, layer));
				}
				if (rorationSpeed > 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 7;
			}
			else if (key == 'X') {
				rotationAxis = { 0, 0, 1 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(j, i, CUBE_SIZE - 1 - layer));
				}
				if (rorationSpeed > 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 2;
			}
			else if (key == 'x') {
				rotationAxis = { 0, 0, 1 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(j, i, CUBE_SIZE - 1 - layer));
				}
				if (rorationSpeed < 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 8;
			}
			else if (key == 'C') {
				rotationAxis = { 1, 0, 0 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(layer, i, j));
				}
				if (rorationSpeed > 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 3;
			}
			else if (key == 'c') {
				rotationAxis = { 1, 0, 0 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(layer, i, j));
				}
				if (rorationSpeed < 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 9;
			}
			else if (key == 'V') {
				rotationAxis = { 1, 0, 0 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(CUBE_SIZE - 1 - layer, i, j));
				}
				if (rorationSpeed < 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 4;
			}
			else if (key == 'v') {
				rotationAxis = { 1, 0, 0 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(CUBE_SIZE - 1 - layer, i, j));
				}
				if (rorationSpeed > 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 10;
			}
			else if (key == 'B') {
				rotationAxis = { 0, 1, 0 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(i, layer, j));
				}
				if (rorationSpeed < 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 5;
			}
			else if (key == 'b') {
				rotationAxis = { 0, 1, 0 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(i, layer, j));
				}
				if (rorationSpeed > 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 11;
			}
			else if (key == 'N') {
				rotationAxis = { 0, 1, 0 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(i, CUBE_SIZE - 1 - layer, j));
				}
				if (rorationSpeed > 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 6;
			}
			else if (key == 'n') {
				rotationAxis = { 0, 1, 0 };
				FOR0(i, CUBE_SIZE) {
					FOR0(j, CUBE_SIZE)
						rotationQueue.push_back(tacka(i, CUBE_SIZE - 1 - layer, j));
				}
				if (rorationSpeed < 0)
					rorationSpeed = -rorationSpeed;
				rotationType = 12;
			}
		}
	}

}
//mis
void mouse(int button, int state, int x, int y) {

	if (isMousePressed == false) {
		float mis_x = (x - (float)width / 2) * viewportX / width + camX;
		float mis_y = ((float)height / 2 - y) * viewportY / height + camY;

		printf("Kliknuto je na %f, %f\n", mis_x, mis_y);

		if (xscreen == 0 && yscreen == 0) {
			if (butt_start.collision(mis_x, mis_y)) {
				butt_start.isAnimating = true;
				xscreen = 0.5;
				fromXScreen = 0;
				toXScreen = 1;
				yscreen = 0;
				fromYScreen = 0;
				toYScreen = 0;
			}
			
			else if (butt_exit.collision(mis_x, mis_y)) {
				butt_exit.isAnimating = true;
			}
		}
		if (xscreen == 1 && yscreen == 0) {
			if (butt_nazad.collision(mis_x, mis_y)) {
				butt_nazad.isAnimating = true;
				xscreen = 0.5;
				fromXScreen = 1;
				toXScreen = 0;
				yscreen = 0;
				fromYScreen = 0;
				toYScreen = 0;
			}
			if (butt_resi.collision(mis_x, mis_y) && (CUBE_SIZE == 2 || CUBE_SIZE == 3)) 
				butt_resi.isAnimating = true;
			
		}
		
				
	}


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		px = x;
		py = y;
		isMousePressed = true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		py = px = -1;
		isMousePressed = false;
	}



}
void motion(int x, int y) {

	if (xscreen == 1 && yscreen == 0) {
		if (px != -1 && py != -1) {
			double factor = 0.005;
			Quaterniond qx = Quaterniond{ AngleAxisd{ (y - py) * factor, Vector3d{ 1, 0, 0 } } };
			Quaterniond qy = Quaterniond{ AngleAxisd{ (x - px) * factor, Vector3d{ 0, 1, 0 } } };
			camera = qx * qy * camera;
		}
	}
	px = x;
	py = y;

}