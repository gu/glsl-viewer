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
				Vector3f Vertices[8];
				Vertices[0] = Vector3f(-1.0f, -1.0f, -1.0f);
				Vertices[1] = Vector3f(1.0f, -1.0f, -1.0f);
				Vertices[2] = Vector3f(-1.0f, 1.0f, -1.0f);
				Vertices[3] = Vector3f(-1.0f, -1.0f, 1.0f);
				Vertices[4] = Vector3f(1.0f, 1.0f, -1.0f);
				Vertices[5] = Vector3f(1.0f, -1.0f, 1.0f);
				Vertices[6] = Vector3f(-1.0f, 1.0f, 1.0f);
				Vertices[7] = Vector3f(1.0f, 1.0f, 1.0f);

				glGenBuffers(1, &this->VBO);
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

				
				unsigned int Indices[] = { 0, 1, 4, 2,
										   1, 5, 7, 4,
										   0, 2, 6, 3,
										   5, 3, 6, 7,
										   0, 3, 5, 1,
										   2, 4, 7, 6 };

				glGenBuffers(1, &this->IBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

				Vector3 Normals[6];
				Normals[0] = Vector3(0, 0, -1);
				Normals[1] = Vector3(1, 0, 0);
				Normals[2] = Vector3(-1, 0, 0);
				Normals[3] = Vector3(0, 0, 1);
				Normals[4] = Vector3(0, -1, 0);
				Normals[5] = Vector3(0, 1, 0);

				glGenBuffers(1, &this->NBO);
				glBindBuffer(GL_ARRAY_BUFFER, this->NBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(Normals), Normals, GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glEnableVertexAttribArray(2);
				glBindBuffer(GL_ARRAY_BUFFER, this->NBO);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);

				glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(2);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
		private:
			GLuint IBO;
			GLuint VBO;
			GLuint NBO;
		};
	}
}