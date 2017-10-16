#pragma once

#include "OpenGL.h"
#include "IDrawable.h"

namespace Crawfis 
{
	namespace Graphics
	{
		class DrawableCube : public IDrawable
		{
		public:
			DrawableCube() 
			{
			}
			virtual void Draw()
			{
				// TODO: Create VBO. Give each vertex or face a color and a normal. Use Indexed draw mode.
				glBegin( GL_QUADS );
				// front
				glNormal3f(0,0,-1);
				glVertex3f(-1.0f,-1.0f,-1.0f);
				glVertex3f(1.0f,-1.0f,-1.0f);
				glVertex3f(1.0f,1.0f,-1.0f);
				glVertex3f(-1.0f,1.0f,-1.0f);

				//right
				glNormal3f(1,0,0);
				glVertex3f(1.0f,-1.0f,-1.0f);
				glVertex3f(1.0f,-1.0f,1.0f);
				glVertex3f(1.0f,1.0f,1.0f);
				glVertex3f(1.0f,1.0f,-1.0f);

				//left
				glNormal3f(-1,0,0);
				glVertex3f(-1.0f,-1.0f,-1.0f);
				glVertex3f(-1.0f,1.0f,-1.0f);
				glVertex3f(-1.0f,1.0f,1.0f);
				glVertex3f(-1.0f,-1.0f,1.0f);

				//back
				glNormal3f(0,0,1);
				glVertex3f(1.0f,-1.0f,1.0f);
				glVertex3f(-1.0f,-1.0f,1.0f);
				glVertex3f(-1.0f,1.0f,1.0f);
				glVertex3f(1.0f,1.0f,1.0f);

				//bottom
				glNormal3f(0,-1, 0);
				glVertex3f(-1.0f,-1.0f,-1.0f);
				glVertex3f(-1.0f,-1.0f,1.0f);
				glVertex3f(1.0f,-1.0f,1.0f);
				glVertex3f(1.0f,-1.0f,-1.0f);

				//top
				glNormal3f(0,1, 0);
				glVertex3f(-1.0f,1.0f,-1.0f);
				glVertex3f(1.0f,1.0f,-1.0f);
				glVertex3f(1.0f,1.0f,1.0f);
				glVertex3f(-1.0f,1.0f,1.0f);

				glEnd();

			}
		private:
		};
	}
}