#include "func.h"

//funkcija za ispis teksta na odredjenoj poziciji odredjene velicine
void stampaj(float x, float y, string text, float size) {

	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size / 800.0, size / 800.0, 0);
	glLineWidth(2);
	glColor3f(0,0,0);

	FOR0(i, text.size())
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	glPopMatrix();

}

//setovanje na true
void enableTransition() {
	isTransition = true;
}

//funkcija za iskljucivanje programa prilikom pritiska na dugme iskljuci
void exitProgram() {	exit(0);  }


//funkcija koristi bfs, nije najsjajniji izbor ali dovoljno dobar
//vraca poteze kojim se dolazi do resenja
void pronadji_resenje(vector<char>& potezi) {

	State tre;
	set<State> visited;
	queue<State> q;
	map<State, pair<char, State>> parent;


	visited.insert(kocka);
	q.push(kocka);

	while (!q.empty()) {

		State s = q.front();
		State copy = s;
		q.pop();

		if (s.isSolved()) {
			tre = s;
			break;
		}

		
		s.front_clock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('z', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.front_anticlock();

		s.back_clock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('x', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.back_anticlock();

		s.left_clock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('c', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.left_anticlock();

		s.right_clock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('v', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.right_anticlock();

		s.up_clock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('b', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.up_anticlock();

		s.down_clock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('n', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.down_anticlock();

		
		s.front_anticlock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('Z', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.front_clock();

		s.back_anticlock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('X', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.back_clock();

		s.left_anticlock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('C', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.left_clock();

		s.right_anticlock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('V', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.right_clock();

		s.up_anticlock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('B', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.up_clock();

		s.down_anticlock();
		if (visited.find(s) == visited.end()) {
			visited.insert(s);
			parent[s] = make_pair('N', copy);
			q.push(s);
			if (s.isSolved()) {
				tre = s;
				break;
			}
		}
		s.down_clock();

	}

	while (parent.count(tre)) {
		pair<char, State> s = parent[tre];
		potezi.push_back(s.first);;
		tre = s.second;
	}

	reverse(potezi.begin(), potezi.end());

}

//pozivanje funkcije i brisanje prethodnog resenja iz liste
void resi() {
	moveList.clear();
	pronadji_resenje(moveList);
}


//izmenjivanje stanja kocke(matrice) u zavisnosti od vrste poteza tj rotationType
void prState() {

	FOR0(a, rotationQueue.size()) {
		tacka mci = rotationQueue[a];
		int i = mci.z, j = mci.y, k = mci.x;
		cubesRotation[i][j][k] = Quaterniond{ AngleAxisd{ 1, Vector3d{ 0,0,0 } } };
	}

	rotationQueue.clear();
	totalRotation = 0;

	if (rotationType == 1)
		kocka.front_anticlock();
	else if (rotationType == 2)
		kocka.back_anticlock();
	else if (rotationType == 3)
		kocka.left_anticlock();
	else if (rotationType == 4)
		kocka.right_anticlock();
	else if (rotationType == 5)
		kocka.up_anticlock();
	else if (rotationType == 6)
		kocka.down_anticlock();

	else if (rotationType == 7)
		kocka.front_clock();
	else if (rotationType == 8)
		kocka.back_clock();
	else if (rotationType == 9)
		kocka.left_clock();
	else if (rotationType == 10)
		kocka.right_clock();
	else if (rotationType == 11)
		kocka.up_clock();
	else if (rotationType == 12)
		kocka.down_clock();

	
	rotationType = 0;

}

//stepeni u radiane
double radian(double deg) {
	return PI * deg / 180;
}


//funkcije za matrice
double* getRotMatrix(Quaterniond& q) {

	Matrix3d rotMat = q.normalized().toRotationMatrix();

	matrix[0] = rotMat(0, 0);	matrix[4] = rotMat(0, 1);	matrix[8] = rotMat(0, 2);	matrix[12] = 0;
	matrix[1] = rotMat(1, 0);	matrix[5] = rotMat(1, 1);	matrix[9] = rotMat(1, 2);	matrix[13] = 0;
	matrix[2] = rotMat(2, 0);	matrix[6] = rotMat(2, 1);	matrix[10] = rotMat(2, 2);	matrix[14] = 0;
	matrix[3] = 0;				matrix[7] = 0;				matrix[11] = 0;				matrix[15] = 1;

	return matrix;

}

void novaRot() {


	FOR0(a, rotationQueue.size()) {
		tacka mci = rotationQueue[a];
		int i = mci.z, j = mci.y, k = mci.x;
		Quaterniond qr = Quaterniond{ AngleAxisd{ radian(rorationSpeed), rotationAxis} };
		cubesRotation[i][j][k] = qr * cubesRotation[i][j][k];
	}

	totalRotation += rorationSpeed;

	if (totalRotation >= 90 || totalRotation <= -90) {
		prState();
	}

}
