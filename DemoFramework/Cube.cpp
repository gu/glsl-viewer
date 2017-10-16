#include "OpenGL.h"

#include <string>
#include <vector>

// Includes to create the cube
#include "ISceneNode.h"
#include "ModelManager.h"
#include "DrawableProxy.h"
#include "DrawableCube.h"

// Includes for the camera
#include "PerspectiveTransform.h"
#include "LookAtTransform.h"

#include "RenderTargetProxy.h"
#include "RenderTarget.h"
#include "RenderManager.h"
#include "ClearFrameCommand.h"
#include "SwapCommand.h"

// Includes for walking the scene graph
#include "RenderVisitor.h"

using namespace Crawfis::Graphics;
using namespace Crawfis::Math;
using namespace std;


ISceneNode* rootSceneNode;
IVisitor* renderVisitor;

int windowGUID;
int windowWidth;
int windowHeight; 

void CreateGLUTWindow(std::string windowTitle)
{
	windowWidth = 800;
	windowHeight = 600;
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	windowGUID = glutCreateWindow(windowTitle.c_str());
}

void InitializeOpenGLExtensions()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		throw "Error initializing GLEW";
	}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void InitializeDevices()
{
	CreateGLUTWindow("OpenGL Demo Framework");
	InitializeOpenGLExtensions();
}

ISceneNode* CreateSceneGraph()
{
	// Create a simple scene
	// Perspective
	// LookAt camera
	// Drawable Cube
	//
	// First, create a Cube model and register it.
	IDrawable* cube = new DrawableCube();
	ModelManager::Instance()->RegisterModel("Cube", cube);
	DrawableProxy* cubeNode = new DrawableProxy("Cube", "Cube"); // It is okay if they have the same name.
	// Look At data
	Vector3 eyePosition = Vector3(3, 3, 3);
	Vector3 centerOfInterest = Vector3(0,0,0);
	Vector3 viewUp = Vector3(0,1,0);
	ISceneNode* lookAt = new LookAtTransform("LookAt", cubeNode, eyePosition, centerOfInterest, viewUp);
	ISceneNode* rootNode = new PerspectiveTransform("Perspective", lookAt, 30, windowWidth, windowHeight, 0.1, 100);
	return rootNode;
}

void DisplayFrame()
{
	rootSceneNode->Accept(renderVisitor);
}

void ReshapeWindow(int newWidth, int newHeight)
{
	windowWidth = newWidth;
	windowHeight = newHeight;
}

ISceneNode* CreateFrameBuffer(Crawfis::Graphics::ISceneNode * scene)
{
	IRenderTarget* screen = new RenderTarget();
	RenderManager::Instance()->RegisterRenderTarget("Screen", screen);
	screen->setEnableCommand(new ClearFrameCommand(Colors::IndianRed));
	screen->setDisableCommand(new SwapCommand(true));
	RenderTargetProxy* frameBuffer = new RenderTargetProxy("Screen Display", "Screen", scene);
	return frameBuffer;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	InitializeDevices();

	ISceneNode* scene = CreateSceneGraph();
	rootSceneNode = CreateFrameBuffer(scene);

	renderVisitor = new RenderVisitor();

	glutDisplayFunc(DisplayFrame);
	glutReshapeFunc(ReshapeWindow);

	glutMainLoop();

	return 0;
}