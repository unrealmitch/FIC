/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package servidortcp;

import java.io.FileOutputStream;
import java.io.PrintStream;

/**
 *
 * @author UnrealMitch
 */
public class Logs {

    FileOutputStream archivo;
    PrintStream p = null;

    public void Logs() {
    }

    public void Loggin(String Mensaje, Boolean Error) {
        try {
            if (Error) {
                archivo = new FileOutputStream(".\\errores.txt", true);
            } else {
                archivo = new FileOutputStream(".\\accesos.txt", true);
            }

            p = new PrintStream(archivo);
            p.print(Mensaje);
            p.flush();
            p.close();
        } catch (Exception e) {
        } finally {
            p.flush();
            p.close();
        }
    }
}