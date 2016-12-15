// HelloWorld.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

// include iostream ��Ҫʹ��<> ������ �������Ҳ���.h��������Ҫ�� stdafx.h ���棬������벻��
#include <iostream>

// glew.h ��Ҫ�� freeglut.h ǰ��
#include "glew.h"
#include "freeglut.h"

using namespace std;

//// �α��Դ���ͷ�ļ�
//#include "vgl.h"
//#include "LoadShaders.h"

enum VAO_IDs{Triangles,NumVAOs};
enum Buffer_IDs{ArrayBuffer,NumBuffers};
enum Attrib_IDs { vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

//-----------------------------------init-------------------------------------------
void init(void)
{
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat verticces[NumVertices][2] = 
	{
		{-0.90,-0.90},
		{ 0.85,-0.9},
		{-0.90, 0.85},
		{ 0.90,-0.85},
		{ 0.90, 0.90},
		{-0.85, 0.90}
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticces), verticces, GL_STATIC_DRAW);

	//ShaderInfo shaders[] = { {GL_VERTEX_SHADER,"triangles.vert"},{GL_FRAGMENT_SHADER,"triangles.frag"},{GL_NONE,NULL } };

	/*GLuint program= LoadShaders(shaders);
	glUseProgram(program);*/

	//glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}

//-----------------------------------display----------------------------------------
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glFlush();
}

// ���������������ԭ��
// ���Ŀ¼��û�п��� opengl ��ؿ�� dll
// ���ӿ���û�� opengl ��ؿ�� obj
// ����ͨ������ԭ���� û�����opengl ���ͷ�ļ�·��������
// ZERO_CHECK ֻ���������ļ�����Ŀ����Ϊʵ�ù��ߣ���Ҫ���𿽱��ļ�
// Doc ��������ذ��� help,����������/?,���磺cls /?
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(700, 100);
	
	// �п��ܰ汾̫��������������һ������ʧ��
	glutInitContextVersion(4,5);

	// GLUT_CORE_PROFILE �ᵼ��һ�����������û��Ч�������Ʋ���ʾ
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Hello World !!");

	// �Ȼ�ȡ��Ϣ�󴴽� Window �ᵼ�� ������Ϣ��Ϊ null
#pragma region HardwareInfo
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glsVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	GLint numExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

	printf("GL Renderer: %s\n", renderer);
	printf("GL Vendor: %s\n", vendor);
	printf("GL version (string): %s\n", version);
	printf("GL version (integer): %d.%d\n", major, minor);
	printf("GLSL version: %s", glsVersion);
#pragma endregion
	
	if (glewInit()) 
	{
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}

	//init();

	glutDisplayFunc(display);
	glutMainLoop();

    return 0;
}
