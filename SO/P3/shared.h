
struct tshared {

		void *dir;
		char *tiempo;
		int tam;	
      key_t key;
		struct tshared *sig;
};

typedef struct tshared pshared;

pshared *crearListaShared(); 
pshared *insertarListaShared(pshared *l, void *dir, int tam, char *tiempo, key_t key);
void vaciarListaShared(pshared **l);
void imprimirListaShared(pshared *l);
pshared* borrarListaSharedDir(pshared *l, char * dir);
pshared* borrarListaShared(pshared *l, int tam);

