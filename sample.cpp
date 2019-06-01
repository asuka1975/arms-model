#include <iostream>
#include <gl\glut.h>
#include "vector.h"
#include "model.h"

static void display(void);

template <class T> 
std::ostream &operator<<(std::ostream &o, const std::vector<T> &v)
{
	o << "{"; for (int i = 0; i<(int)v.size(); i++)o << (i>0 ? ", " : "") << v[i]; o << "}"; return o;
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("graph");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}

void display(void)
{
	int s = 5;
	Model model{
		vector{ 200, 0, 0 },
		vector{ 10, 0, 0, 0, 10, 1 },
		vector{ 0, s, 0, s, 0, 1 },
		vector{ 0, s, 1, s, 0, 2 }
	};

	for (int i = 0; i < 1000; i++) {
		model.AdvanceStep();
	}

	std::vector<int> A = model.GetAgentRecord(0);
	std::vector<int> B = model.GetAgentRecord(1);
	std::vector<int> T = model.GetAgentRecord(2);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < T.size(); i++) {
		double a = static_cast<double>(A[i]) / 200;
		double b = static_cast<double>(B[i]) / 200;
		glVertex2f(static_cast<double>(T[i]) / 1000 * 2.0 - 1.0, a / (a + b) * 2.0 - 1);
	}
	glEnd();

	glFlush();
}
