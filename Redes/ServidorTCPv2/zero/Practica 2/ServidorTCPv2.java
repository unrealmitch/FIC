/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package servidortcp;

import java.io.IOException;
import java.net.*;


/**
 * Ejemplo que implementa un servidor de eco usando TCP.
 */
public class ServidorTCPv2 {
    
    public static void main(String argv[]) throws IOException {
        ServerSocket ssocket = null;
        
        try {
// Creamos el socket del servidor y establecemos su timeout
            
            //Cargamos la configuracio
            Configuracion config = new Configuracion();
            config.cargarConfig();
            
            //Establecemos el puerto de escucha
            int PuertoEscucha;
            
            if ((Configuracion.PORT >= 0) && (Configuracion.PORT <= 65534)){
                PuertoEscucha = Configuracion.PORT;
            } else{
                PuertoEscucha = 80;
            }
            
            //Creamos el socket que estará a la escucha
            ssocket = new ServerSocket(PuertoEscucha);
            ssocket.setSoTimeout(0);
            System.out.println("Servidor iniciado bajo el puerto " + ssocket.getLocalPort());
            
            while (true) {
// Esperamos posibles conexiones
                Socket wsocket = ssocket.accept();
                System.out.println("Nueva conexión de: " + wsocket.getInetAddress().toString());
// Creamos un objeto ThreadServidor, pasándole la nueva conexión
                ThreadServidor NuevoHilo = new ThreadServidor(wsocket);
// Iniciamos su ejecución con el método start()
                NuevoHilo.start();
            }
        } catch (SocketTimeoutException e) {
            System.err.println("30 segs sin recibir nada");
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        } finally {
//Cerramos el socket del servidor
            ssocket.close();  
        }
    }
}