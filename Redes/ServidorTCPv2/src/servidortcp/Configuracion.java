package servidortcp;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

/**
 *
 * @author UnrealMitch
 */
public class Configuracion {

    private static final String RUTA_PATH = "./src/servidortcp";
    private static final String FICHERO = "Servidor.properties";
    public static int PORT;
    public static String DIRECTORY_INDEX;
    public static String DIRECTORY;
    public static boolean ALLOW;
    public static boolean CACHE;

    public void Configuracion() {
    }

    public void cargarConfig() {
        try {
            String rutaFichero = RUTA_PATH + "/" + FICHERO;
            Properties prop = new Properties();
            prop.load(new FileInputStream(rutaFichero));
            //FileInputStream archivoInput = new FileInputStream(rutaFichero);

//Carga Fichero. 
            //objPropiedadFichero.load(archivoInput);

//Obteniendo Datos. 
            PORT = Integer.parseInt(prop.getProperty("PORT").toString());
            DIRECTORY_INDEX = prop.getProperty("DIRECTORY_INDEX");
            DIRECTORY = prop.getProperty("DIRECTORY");

            if ("1".equals(prop.getProperty("ALLOW"))) {
                ALLOW = true;
            } else {
                ALLOW = false;
            }

            if ("1".equals(prop.getProperty("CACHE"))) {
                CACHE = true;
            } else {
                CACHE = false;
            }

        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
