
struct tmmalloc {

		char *dir;
		char *tiempo;
		int tam;	
		struct tmmalloc *sig;
};

typedef struct tmmalloc pmmalloc;

pmmalloc *crearListaMalloc(); 
pmmalloc *insertarListaMalloc(pmmalloc *l, void *dir, char *tiempo, int tam);
void vaciarListaMalloc(pmmalloc **l);
void imprimirListaMalloc(pmmalloc *l);
pmmalloc* borrarListaMalloc(pmmalloc *l, int tam);
pmmalloc* borrarListaMallocDir(pmmalloc *l, char * dir);
