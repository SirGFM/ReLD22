#ifndef __MESH_H
#define __MESH_H

#include <GL/glew.h>
namespace CppOGL {
	class Buffer;
	
	class Mesh {
		private:
			/**
			 * Store information about the mesh's vertices.
			 */
			Buffer *buffer;
			/**
			 * Store information about how the mesh uses it's vertices.
			 */
			GLuint ibo;
			/**
			 * How many vertices there are in the vbo.
			 */
			int numVertices;
			/**
			 * How many triangles there are in the vbo.
			 */
			int numTriangles;
		public:
			/**
			 * Create a new unique mesh.
			 * 
			 * @param	data {const float[]}		Array of vertices in (X,Y,Z) format.
			 * @param	indices {const GLshort[]}	Array of triangule's vertices' index.
			 * @param	NumVertices {int}			How many vertices there are in data.
			 */
			Mesh(Buffer *_Buffer, const GLshort indices[], int NumTriangles);
			~Mesh();
			
			void associate();
			void render();
	};
}

#endif
