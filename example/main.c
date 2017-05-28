
#include<stdio.h>

#include "../src/loadmodel.h"


int main(int argc, char* argv[])
{
	float* ver = 0;
	int verc = 0;
	unsigned int* tri = 0;
	int tric = 0;

	if(loadModel("cube.csmf", &ver, &verc, &tri, &tric))
	{
		printf("model load failure\n");
		return 1;
	}

	printf("Verts: %d\n", verc);
	int v;
	for(v=0;v<verc;v++)
	{
		printf(" Vert %4d:   x: %10f  y: %10f  z: %10f\n", v, ver[3*v+0], ver[3*v+1], ver[3*v+2]);
	}

	printf("Tris: %d\n", tric);
	int t;
	for(t=0;t<tric;t++)
	{
		printf(" Tri %4d:   v0: %5d  v1: %5d  v2: %5d\n", t, tri[3*t+0], tri[3*t+1], tri[3*t+2]);
	}

	return 0;
}
