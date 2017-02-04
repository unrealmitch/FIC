#define TNORMAL 0
#define TSENAL 1
#define PARADO 2
#define ACTIVO 3

struct tproceso {
		int pid;
		char *nombre;
		char *tiempo;
		int prioridad;	
		int estado;  
		struct tproceso *sig;
};

typedef struct tproceso proceso;


proceso* crearLista2p(); 
proceso *addLista2p(proceso *p, int pro_pid,char *nombre,char* tiempo,int prioridad,int estado);
proceso *delLista2p(proceso *p,proceso *borrar);
void printprocess(proceso* p);
void clearLista2p(proceso **p);
proceso* refreshLista2p(proceso* p);
