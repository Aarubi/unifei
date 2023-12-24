#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/ext.hpp> // perspective, translate, rotate
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/io.hpp>

#include <vector>
#include <iostream>
#include <math.h>

// Instale as seguintes bibliotecas:
//sudo apt-get install cmake build-essential libgl1-mesa-dev freeglut3 libglm-dev

// Para compilar execute no terminal:
// g++ -o Transformacao exemplo_transformacao.cpp -lglut -lGLU -lGL -lm

std::vector<glm::vec4> screw;


std::vector<glm::vec4> screw2;


void pontos_screw()
{
	
    screw.push_back(glm::vec4( 45.0f, 60.0f, 23.73f, 1.0f ));
	
    screw.push_back(glm::vec4( 40.0f, 60.0f, 20.0f, 1.0f ));

    screw.push_back(glm::vec4( 40.0f, 50.0f, 20.0f, 1.0f ));
    screw.push_back(glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ));

}

void pontos_screw2(){

    screw2.push_back(glm::vec4( 44.05f, 29.58f, 24.19f, 1.0f )); //ponto P
	
    screw2.push_back(glm::vec4( 40.0f, 29.58f, 20.0f, 1.0f )); // Ponto central da cabeça do parafuso (que vai da origem)

    screw2.push_back(glm::vec4( 40.0f, 19.58f, 20.0f, 1.0f )); // distancia do comprimemnto do parafuso que escolhi
    screw2.push_back(glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ));

}

std::vector<glm::vec4> transformacao(std::vector<glm::vec4> cube_in)
{
	std::cout << "Initial points: \n";	
	for(int i=0;i<screw.size();i++)
		std::cout << cube_in[i] << "\n";
	
	glm::mat4 T = glm::translate( glm::mat4( 1.0f ), glm::vec3( -1.0f, -1.0f,1.0f ) );
		
	std::cout << "Matrix: \n " << T << "\n";
	
	std::vector<glm::vec4> cube_out;
	
	for(int i=0;i<screw.size();i++)
	{
		glm::vec4 point = T * cube_in[i];
		cube_out.push_back(point);
	}
	
	std::cout << "Final points: \n";
	for(int i=0;i<screw.size();i++)
		std::cout << cube_out[i] << "\n";
	
	return cube_out;

}

void referencia()
{
    
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(45, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 45, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 45);
    glEnd();

}

void draw_screw(std::vector<glm::vec4> cube_in, int r, int g, int b)
{
    
    glColor3f(r, g, b);

    glLineWidth(5.0f);

    glBegin(GL_LINES);
    
    glVertex3f(cube_in[0].x,cube_in[0].y,cube_in[0].z);
    glVertex3f(cube_in[1].x,cube_in[1].y,cube_in[1].z);

    glEnd();

    glBegin(GL_LINES);
    
    glVertex3f(cube_in[1].x,cube_in[1].y,cube_in[1].z);
    glVertex3f(cube_in[2].x,cube_in[2].y,cube_in[2].z);

    glEnd();

   
}


void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    referencia();
    //draw_screw(cube);
    
    std::vector<glm::vec4> pontos = transformacao(screw);
    draw_screw(pontos,1,1,0);

    std::vector<glm::vec4> pontosParafusados = transformacao(screw2);

    draw_screw(pontosParafusados,0,1,1);


    glutPostRedisplay();
    glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);
    
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if (h == 0)
        h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);

    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(10, (GLfloat)w / (GLfloat)h, 0.5, 500);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Especifica posição do observador e do alvo
    //gluLookAt(180, 205, 80, 45.0f, 60.0f, 23.73f, 0, 0, 1);
    gluLookAt(180, 205, 80, 0, 0, 0, 0, 0, 1);
}

// Programa Principal
int main(int argc, char **argv)
{

    pontos_screw();
    pontos_screw2();
    
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Visualizacao 3D");
    glutDisplayFunc(Display);
    glutReshapeFunc(AlteraTamanhoJanela);
    //glutMouseFunc(GerenciaMouse);
    Inicializa();
    glutMainLoop();
}
