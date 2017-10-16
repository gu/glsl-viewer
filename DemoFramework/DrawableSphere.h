#pragma once

#include "OpenGL.h"
#include "IDrawable.h"
#include <math.h>

namespace Crawfis
{
	namespace Graphics 
	{
		class DrawableSphere : public IDrawable
		{
		public:
			DrawableSphere(int desiredNumberOfTriangles, bool wireframe) 
			{
				int subdivisions = (int) sqrtf(desiredNumberOfTriangles/2);
				numberOfLongitudeSlices = subdivisions < minSubdivision ? minSubdivision : subdivisions;
				this->wireframe = wireframe;

				created = false;
				displayList = 0;
			}
			virtual void Draw()
			{
				InternalDraw();
			}
		private:
			void CreateSphere()
			{
                // Create a new display list.
                created = true;
				displayList = glGenLists(1);
				glNewList(displayList, GL_COMPILE);
                // use the glu quadric functions to create the sphere.
				::GLUquadric* q;
				q = gluNewQuadric();
                if( wireframe )
					gluQuadricDrawStyle(q, GLU_LINE);
                else
					gluQuadricDrawStyle(q, GLU_FILL);

				gluQuadricNormals(q, GLU_SMOOTH);
				gluQuadricTexture(q, GLU_TRUE);
				gluSphere(q, 1.0, numberOfLongitudeSlices, numberOfLongitudeSlices/2);
				glEndList();
			}
			void InternalDraw()
			{
				if (!created)
				{
					CreateSphere();
				}
				//
				// Actually draw the sphere
				//
				glCallList(displayList);
			}
		private:
			bool created;
			unsigned int displayList;
			int numberOfLongitudeSlices;
			bool wireframe;
			static const int minSubdivision = 10;
		};
	}
}