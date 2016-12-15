// HelloWorld.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

// include iostream 需要使用<> 而不是 “”，且不用.h，并且需要在 stdafx.h 后面，否则编译不过
#include <iostream>

// glew.h 需要在 freeglut.h 前面
#include "glew.h"
#include "freeglut.h"

using namespace std;

//// 课本自带的头文件
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

// 启动不起来程序的原因
// 输出目录下没有拷贝 opengl 相关库的 dll
// 链接库中没有 opengl 相关库的 obj
// 编译通不过的原因是 没有添加opengl 相关头文件路径的引用
// ZERO_CHECK 只有批处理文件，项目类型为实用工具，主要负责拷贝文件
// Doc 命令行相关帮助 help,具体命令用/?,例如：cls /?
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(700, 100);
	
	// 有可能版本太高启动不起来，一闪就消失了
	glutInitContextVersion(4,5);

	// GLUT_CORE_PROFILE 会导致一部分命令绘制没有效果，绘制不显示
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Hello World !!");

	// 先获取信息后创建 Window 会导致 所有信息都为 null
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
