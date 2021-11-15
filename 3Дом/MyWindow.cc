
#include "MyWindow.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <algorithm>
#include <vector>

static constexpr double Pi = acos(-1);

using VertexVector = std::vector<std::vector<GLdouble>>;
using NormalVector = std::vector<std::vector<GLdouble>>;
using FaceVector = std::vector<std::vector<int>>;
using TexCoordVector = std::vector<std::vector<std::vector<GLdouble>>>;

struct Model {
	VertexVector vertices;
	FaceVector faces;
	NormalVector normals;
	TexCoordVector texcoords;
};

static const VertexVector madhouse_vertices {
	{ -1., 0., 2.5 },
	{ 1., 0., 2.5 },
	{ -1., -1., 2. },
	{ -1., 1., 2. },
	{ 1., 1., 2. },
	{ 1., -1., 2. },
	{ -1., -1., 0. },
	{ -1., 1., 0. },
	{ 1., 1., 0. },
	{ 1., -1., 0. },
};

static const FaceVector madhouse_faces {
	{ 1, 4, 8, 9, 5 },
	{ 0, 2, 6, 7, 3 },
	{ 4, 3, 7, 8 },
	{ 2, 5, 9, 6 },
	{ 7, 6, 9, 8 },
	{ 1, 0, 3, 4 },
	{ 0, 1, 5, 2 },
};

static const NormalVector madhouse_normals {
	{ 1., 0., 0. },
	{ -1., 0., 0. },
	{ 0., 1., 0. },
	{ 0., -1., 0. },
	{ 0., 0., -1. },
	{ 0., 0.4472, 0.8944},
	{ 0., -0.4472, 0.8944},
};
static const TexCoordVector madhouse_tc {

	{ {0.1665, 0.}, {0.333, 0.2}, {0.333, 0.5}, {0., 0.5}, {0., 0.2} },
	{ {0.1665, 0.5}, {0.333, 0.7}, {0.333, 1.0}, {0., 1.0}, {0., 0.7} },
	{ {0.333, 0.2}, {0.667, 0.2}, {0.667, 0.5}, {0.333, 0.5} },
	{ {0.333, 0.7}, {0.667, 0.7}, {0.667, 1.}, {0.333, 1.} },
	{ {0.333, 0.}, {0.667, 0.}, {0.667, 0.2}, {0.333, 0.2} },
	{ {0.667, 0.}, {1., 0.}, {1., 0.5}, {0.667, 0.5}},
	{ {0.667, 0.5}, {1., 0.5}, {1., 1.}, {0.667, 1.}},
};

static const Model madhouse_model {
	madhouse_vertices,
	madhouse_faces,
	madhouse_normals,
	madhouse_tc
};
void MyWindow::setup_gl()
{
	glClearColor(0.2f, 0.5f, 0.3f, 0.4f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(65.0, 800./650., 0.1, 120.0);
	glMatrixMode(GL_MODELVIEW);
}
void draw_model(const Model& m)
{
	for (size_t face = 0; face < m.faces.size(); face++) {
		size_t nv = m.faces[face].size();
		if (nv == 3) glBegin(GL_TRIANGLES);
		else if (nv == 4) glBegin(GL_QUADS);
		else glBegin(GL_TRIANGLE_FAN);
		glNormal3dv(&m.normals[face][0]);
		for (size_t v = 0; v < nv; v++) {
			size_t vi = m.faces[face][v];
			glTexCoord2dv(&m.texcoords[face][v][0]);
			glVertex3dv(&m.vertices[vi][0]);
		}

		glColor3d(0.8, 0.6, 0.3 );
		glEnd();
	}
}
void MyWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(5, 5, 3, 0, 0, 0, 0, 0, 1);

	static double a = 0;
	a += 0.1;
	glRotated(a, 0., 0., 1.);
	glEnable(GL_TEXTURE_2D);
	 glColor3d(0.8, 0.4, 0.3);
	  glBegin(GL_QUADS);

	     glVertex3d(-1, 1, 0);
	     glVertex3d(1, 1, 0);
	     glVertex3d(1, 1, 2);
	     glVertex3d(-1, 1, 2);

	     glVertex3d(-1, -1, 0);
	     glVertex3d(1, -1, 0);
	     glVertex3d(1, -1, 2);
	     glVertex3d(-1, -1, 2);

		 glColor3d(0.8, 0.6, 0.3);
	 	 glVertex3d(1, -1, 0);
         glVertex3d(1, 1, 0);
	 	 glVertex3d(1, 1, 2);
	 	 glVertex3d(1, -1, 2);

	 	 glVertex3d(-1, -1, 0);
         glVertex3d(-1, 1, 0);
	 	 glVertex3d(-1, 1, 2);
	 	 glVertex3d(-1, -1, 2);

	 	 glColor3d(0.8, 0.6, 0.3);
	     glVertex3d(-1, 0, 2.5);
	     glVertex3d(1, 0, 2.5);
	     glVertex3d(1, 1, 2);
	     glVertex3d(-1, 1, 2);

	     glVertex3d(-1, 0, 2.5);
	     glVertex3d(1, 0, 2.5);
	     glVertex3d(1, -1, 2);
	     glVertex3d(-1, -1, 2);

	 	glEnd();

	  glEnable(GL_TEXTURE_2D);
	for (int i = -4; i <= 4; i++)
		for (int j = -4; j <= 4; j++) {
			glPushMatrix();

			glTranslated(300 * i, 300 * j, 0.);

			draw_model(madhouse_model);
			glPopMatrix();
		}

}



