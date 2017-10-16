#pragma once

#include "OpenGL.h"

#include "IMaterial.h"
#include "DepthTestedRasterOps.h"
#include "ShaderProgram.h"
#include "IShaderConstant.h"
#include "Color.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// Concrete implementation of IMaterial.
		//   - Uses the Material properties.
		//   - Reads in a vertex and a fragment shader from two separate files
		//   - standard depth testing
		// Probably could have derived this from SimpleShaderMaterial.
		//
		class ShadedMaterial : public IMaterial
		{
		public:
			//
			// Constructor.
			//
			ShadedMaterial(std::string vertexFile, std::string fragmentFile)
			{
				FragmentRoutine* fragRoutine = new FragmentRoutine(fragmentFile);
				VertexRoutine* vertRoutine = new VertexRoutine(vertexFile);
				this->shaderProgram = new ShaderProgram(vertRoutine, fragRoutine);
				this->rasterOps = new DepthTestedRasterOps();
				ambient = Colors::Black;
				diffuse = Colors::White;
				specular = Colors::Black;
			}
			//
			// Enable the material.
			//
			virtual void Enable()
			{
				// TODO: Set any shader constants needing lighting information.
				//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient.getValue());
				//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse.getValue());
				//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular.getValue());
				//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
				shaderProgram->Enable();
				rasterOps->Enable();
			}
			//
			// Disable the material. This will be a no-op for our system, since
			// we will require these to be set at the beginning of every material
			// when it is enabled.
			//
			virtual void Disable()
			{
			}
			//
			// Get the ambient reflection coefficient as a color.
			//
			Color getAmbientReflection() const
			{
				return Color(ambient);
			}
			//
			// Set the ambient reflection coefficient as a color.
			//
			void setAmbientReflection(Color ambient)
			{
				this->ambient = ambient;
			}
			//
			// Get the ambient reflection coefficient as a color.
			//
			Color getDiffuseReflection() const
			{
				return Color(diffuse);
			}
			//
			// Set the ambient reflection coefficient as a color.
			//
			void setDiffuseReflection(Color diffuse)
			{
				this->diffuse = diffuse;
			}
			//
			// Get the ambient reflection coefficient as a color.
			//
			Color getSpecularReflection() const
			{
				return Color(specular);
			}
			//
			// Set the ambient reflection coefficient as a color.
			//
			void setSpecularReflection(Color specular)
			{
				this->specular = specular;
			}
			//
			// Get the shininess exponent
			//
			float getShininess() const
			{
				return shininess;
			}
			//
			// Set the shininess exponent
			//
			void setShininess(float shininess)
			{
				this->shininess = shininess;
			}
			void setShaderConstant(IShaderConstant* shaderConstant)
			{
				shaderProgram->setShaderConstant(shaderConstant);
			}
			IShaderConstant* getShaderConstant()
			{
				return shaderProgram->getShaderConstant();
			}

		private:
			IRasterOps* rasterOps;
			IShaderProgram* shaderProgram;
			Color ambient;
			Color diffuse;
			Color specular;
			float shininess;
		};
	}
}