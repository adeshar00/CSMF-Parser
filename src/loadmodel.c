
#include<stdio.h>
#include<stdlib.h>


int loadModel(char* filename,
              float* vertices[],
              int* vertexcount,
              unsigned int* triangles[],
              int* trianglecount)
{
	/*
	    Returns 0 on success, 1 if there's an error.

		filename:       Path of the csmf file to be loaded
		vertices:       Pointer to vertex array to be populated
		vertexcount:    Number of vertices in "vertices" array
		triangles:      Pointer to index array to be populated
		trianglecount:  Number of triangles in "triangles" array
	*/


	float* ver = 0;
	int verc = 0;
	unsigned int* tri = 0;
	int tric = 0;

	unsigned char* ba;  // byte array for file data
	int balen;          // length of ba


	// Copy file to byte array
	{
		// Open file
		FILE* file;
		file = fopen(filename,"rb");
		if(file==0)
		{
			// TODO print error e.x. "unable to open file"
			return 1;
		}

		// Get file size
		fseek(file, 0, SEEK_END);
		balen = ftell(file);
		rewind(file);

		// Read file and copy to 'ba'
		ba = (unsigned char*)malloc(sizeof(unsigned char)*balen);
		if(ba==0) return 1; // TODO print error "malloc failed"
		int r = fread(ba, balen, 1, file);

		// Close file
		fclose(file);

	}


	// Parse byte array for to generate model data
	{
		const int FILEHEADLEN = 2; // Bytes in file header
		const int OBHEADLEN = 22;  // Bytes in header of each object in model
		const int BPVERT = 6;      // Bytes per vertex
		const int BPTRI = 6;       // Bytes per tri
		int pi = FILEHEADLEN;    // 'Parse Index'; tracks which byte is currently being interpreted
		//  TODO add version numbering system
		//int obCount = 256*ba[1] + ba[0]; // Number of objects in file
		//  TODO parser currently only handles files with single object

		// Extract vertex and triangle data from each object
		//int ob;
		//for(ob=0; ob<obCount; ob++)
		{
			verc = 256*ba[pi+1] + ba[pi+0];
			tric = 256*ba[pi+3] + ba[pi+2];
			// load trans/rot/scale data

			if(pi+OBHEADLEN+verc*BPVERT+tric*BPTRI > balen)
			{
				// TODO print error; file data is wonky
				free(ba);
				return 1;
			}

			// Populate vertices
			{

				ver = (float*)malloc(sizeof(float)*verc*3);
				int v;
				int vstart = pi+OBHEADLEN;
				for(v=0; v<verc; v++)
				{
					int bi = vstart + v*BPVERT; // byte-array index
					// X component
					ver[v*3+0] = (float)ba[bi+1] - 128.0f + ((float)ba[bi+0]/256.0f);
					// Y component
					ver[v*3+1] = (float)ba[bi+3] - 128.0f + ((float)ba[bi+2]/256.0f);
					// z component
					ver[v*3+2] = (float)ba[bi+5] - 128.0f + ((float)ba[bi+4]/256.0f);
				}
			}

			// Populate triangles
			{
				tri = (unsigned int*)malloc(sizeof(unsigned int)*tric*3);
				int t;
				int tstart = pi+OBHEADLEN+verc*BPVERT;
				for(t=0; t<tric; t++)
				{
					int bi = tstart + t*BPTRI; // byte-array index
					// Vertex Index 1
					tri[3*t+0] = 256*ba[bi+1] + ba[bi+0];
					// Vertex Index 2
					tri[3*t+1] = 256*ba[bi+3] + ba[bi+2];
					// Vertex Index 3
					tri[3*t+2] = 256*ba[bi+5] + ba[bi+4];
				}
			}

			// Update parse index
			pi+= OBHEADLEN+verc*BPVERT+tric*BPTRI;

		}
		
		free(ba);

	}


	// Set return pointers
	if(vertices!=0)       *vertices = ver;
	else return 1; // TODO print errors: "null pointer for [varname]"
	if(vertexcount!=0)    *vertexcount = verc;
	else return 1;
	if(triangles!=0)      *triangles = tri;
	else return 1;
	if(trianglecount!=0)  *trianglecount = tric;
	else return 1;


	// Done
	return 0;

}
