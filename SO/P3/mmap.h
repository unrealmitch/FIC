
struct tmmap {

		void *dir;
		char *tiempo;
		int tam;	
      char * fichero;
      int descr;
		struct tmmap *sig;
};

typedef struct tmmap pmmap;

pmmap *crearListaMmap(); 
pmmap *insertarListaMmap(pmmap *l, void *dir, int tam, char * fichero, char *tiempo, int descr);
void vaciarListaMmap(pmmap **l);
void imprimirListaMmap(pmmap *l);
pmmap* borrarListaMmap(pmmap *l, char * fich);
pmmap* borrarListaMmapDir(pmmap *l, char * dir);
