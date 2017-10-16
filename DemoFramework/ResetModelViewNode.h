#pragma once

#include "OpenGL.h"
#include "TransformNodeBase.h"

namespace Crawfis
{
	namespace Graphics 
	{
		//
		// A concrete implementation of the ITransformNode.
		//
		class ResetModelViewNode : public TransformNodeBase
		{
		public:
			//
			// Constructor. 
			//
			ResetModelViewNode(std::string name, ISceneNode* subject) : TransformNodeBase(name, subject)
			{
			}
			// 
			// Apply the transform. This implementation will use the OpenGL
			// state machine to track transformations.
			//
			virtual void Apply()
			{
				// TODO: Remove old Fixed Functionality
				glMatrixMode( GL_MODELVIEW );
				glPushMatrix();
				glLoadIdentity();
			}
			// 
			// Remove or undo the application of the transform. This implementation 
			// will use the OpenGL state machine to track transformations.
			//
			virtual void Unapply()
			{
				// TODO: Remove old Fixed Functionality
				glMatrixMode( GL_MODELVIEW );
				glPopMatrix();
			}
		};
	}
}