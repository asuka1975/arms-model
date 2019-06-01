#include <iostream>
#include <gl\glut.h>
#include "vector.h"
#include "model.h"

double epoch = 1000;


static void display(void);

template <class T> 
std::ostream &operator<<(std::ostream &o, const std::vector<T> &v)
{
	o << "{"; for (int i = 0; i<(int)v.size(); i++)o << (i>0 ? ", " : "") << v[i]; o << "}"; return o;
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("graph");

	glClearColor(0.1, 0.2, 0.3, 0.0);

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}

void display(void)
{
	Model model{
		vector{ 400, 0, 0 },
		vector{ 0.5, 0.1, 0.1 },
		vector{ 1, 0, 0, 0, 1, 1 },
		vector{ 0, 1, 0, 1, 0, 1 },
		vector{ 0, 1, 1, 1, 0, 2 }
	};

	for (int i = 0; i < epoch; i++) {
		model.AdvanceStep();
	}

	std::vector<double> A = model.GetAgentRecord(0);
	std::vector<double> B = model.GetAgentRecord(1);
	std::vector<double> T = model.GetAgentRecord(2);

	glColor3f(0.2, 0.9, 0.9);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < T.size(); i++) {
		glVertex2f(static_cast<double>(T[i]) / epoch * 2.0 - 1.0, static_cast<double>(A[i]) / (A[i] + B[i]) * 20.0 - 19);
	}
	glEnd();

	glFlush();
}
