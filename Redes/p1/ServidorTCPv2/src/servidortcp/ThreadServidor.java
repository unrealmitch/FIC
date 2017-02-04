package servidortcp;

import java.net.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Thread que atiende una conexión de un servidor de eco.
 */
public class ThreadServidor extends Thread {

/////////////////// DEFINICION DE OBJETOS Y VARIABLES \\\\\\\\\\\\\\\\\\\\
    Socket socket;
    String Recibido, Respuesta = "";
    //Creamos el objeto para la fecha y tb su formato
    Date fechasf = new Date();
    SimpleDateFormat formato = new SimpleDateFormat("EEE, dd MMM yyyy hh:mm:ss z");
    String fechacf = null;
    ArrayList<String> PalPet = new ArrayList<String>();
    //Envio de archivos no html
    boolean ArchivoWeb;
    int nBytesArch;
    byte[] ContenedorBytes;
    FileInputStream ArchivoEnBytes;
    private int x;
    //Trabajar con la cabecera If-Modified-Since
    boolean PetModific, Actualizar = false;
    String PModificado;
    Date FechaMod, FechaArch;
    Long LengthArch;
    //Cargamos logs
    Logs log = new Logs();
    //Variables para páginas dinámicas
    public String FormularioDo;
    ArrayList<String> ArgFormulario = new ArrayList<String>();
    ArrayList<String> ArgFormularioVal = new ArrayList<String>();
    Map<String, String> ArgumentosDo = new HashMap<String, String>();
/////////////////// DEFINICION DE FUNCIONES \\\\\\\\\\\\\\\\\\\\

    public String decodeURL(String URLcode) {
        //Cambiamos los %20 por espacios
        int i;
        while ((i = URLcode.indexOf("%20")) != -1) {
            URLcode = URLcode.substring(0, i) + " " + URLcode.substring(i + 3);
        }
        return URLcode;
    }

    public void Error404() {

        //Generamos la respuesta y el codigo del error 404
        String E404 = "<html><body><title>Error 404</title>"
                + "<b><font size=12>Error 404: NOT FOUND</font></b><br><br>"
                + "<center>La página demanda no ha sido encontrada <br>"
                + "<img src=\"http://www.nosologeeks.es/wp-content/uploads/chuck-norris.jpg\"><br>"
                + "Aunque él ... si la encontró.</center>"
                + "<br><br><br>"
                + "-Si es la primera vez que le aparece este error, intentelo más tarde.<br>"
                + "-Si es la segunda vez que le aparece, esta asegurado, usted es idiota.<br>"
                + "-Si aún le sigue apareciendo, le recomendamos que acuda a ayuda profesional, y no la informática.<br>"
                + "-Finalmente, si es usted el profesor, le ruego que sea compasivo y no tenga en cuenta estas ultimas lineas.<br>"
                + "<br> Disculpen las molestias, <br> Atentamente: Un mono y su teclado."
                + "</body></html>";

        Respuesta = "HTTP/1.1 404 NOT FOUND\n";
        Respuesta += "Content-Length: " + E404.length() + "\n";
        LengthArch = (long) E404.length();
        Respuesta += "Content-Type: text/html\n\n";
        Respuesta += E404;
    }

    public void GenerarPaginaDir(String Directorio) throws IOException {
        //Funcion que genera un html con los archivos del directorio específicado

        //Empezamos a generar el codigo html
        String NotFound = "<html><body><title>Explorando: " + Directorio + "</title>"
                + "<br><b><font size=10>     Explorando directorio: " + Directorio + "</font></b>"
                + "<br><br><br>";

        //Cargamos el directorio
        File dir = new File(Directorio);
        File[] ficheros = dir.listFiles();

        String PathDir = (dir.getPath()).substring(1);
        
        int i;
        while ((i = PathDir.indexOf('\\')) != -1) {
            PathDir = PathDir.substring(0, i) + "/" + PathDir.substring(i + 1);;
        }

        //Empezamos a generar el codigo html con los ficheros encontrados
        if (ficheros == null) {
            NotFound += "     El directorio está vacio";
        } else {
            for (x = 0; x < (ficheros.length); x++) {
                String nombreArchivo = ficheros[x].getName();
                NotFound += "<a href=\"" + PathDir + "/" + nombreArchivo + "\">     " + nombreArchivo + "</a><br>";
            }
            NotFound += "</body></html>";
        }
        
        //Establecemos las cabeceras y finalizamos la respuesta
        Respuesta = "HTTP/1.1 404 NOT FOUND\n";
        Respuesta += "Content-Length: " + NotFound.length() + "\n";
        Respuesta += "Content-Type: text/html\n\n";
        Respuesta += NotFound;
    }

    public void GenerarRespuesta(String RutaArchivo, boolean EsGet, boolean EsDir)
            throws FileNotFoundException, IOException {

        //Creamos la cabecera de la respuesta

        Respuesta = "Date: " + fechacf + "\n";
        Respuesta += "Server: UnrealJServer/" + System.getProperty("java.version")
                + " (" + System.getProperty("os.name") + ")\n";

        // Obtenemos el nombre del archivo
        String PeticionArch = RutaArchivo;

        if ("/".equals(PeticionArch) || "".equals(PeticionArch)) {
            PeticionArch = Configuracion.DIRECTORY + Configuracion.DIRECTORY_INDEX;
        }

        // Lo Cargamos

        PeticionArch = decodeURL(PeticionArch);
        File ArchivoDemand = new File("." + PeticionArch);
        System.out.println("Se ha demandado : " + PeticionArch);

        //Si exhiste creamos la cabecera y generamos el código
        if (ArchivoDemand.exists()) {
            if (ArchivoDemand.isFile()) {

                //Comprobamos si el archivo de cache es mas viejo que el archivo del server
                Actualizar = true;
                FechaArch = new Date(ArchivoDemand.lastModified());

                //System.out.println("-Fecha Cache: " + FechaMod);
                //System.out.println("-Fecha Archv: " + FechaArch);

                if (PetModific && Configuracion.CACHE) {
                    if (FechaMod.before(FechaArch)) {
                        Actualizar = true;
                        //System.out.println("El archivo en cache está desfasado");
                    } else {
                        Actualizar = false;
                    }
                }

                if (Actualizar) {
                    Respuesta = "HTTP/1.1 200 OK\n" + Respuesta;
                    Respuesta += "Last-Modified: " + formato.format(ArchivoDemand.lastModified()) + "\n";
                    Respuesta += "Content-Length: " + ArchivoDemand.length() + "\n";
                    LengthArch = (long) ArchivoDemand.length();

                    //Determinaos el Content-Type por el formato del archivo
                    String extension = PeticionArch.substring(PeticionArch.lastIndexOf('.'));

                    //El switch con strings funciona en NB 7.1.1, pero en caso
                    //de trabajar en una version inferior tan solo habría que hace
                    //sentencias if anidadas para un mismo funcionamiento.
                    switch (extension) {
                        case ".txt":
                            Respuesta += "Content-Type: text/plain\n";
                            break;
                        case ".html":
                        case ".htm":
                        case ".php":
                        case ".asp":
                        case ".aspx":
                        case ".shtml":
                            Respuesta += "Vary: Accept-Encoding,User-Agent\n";
                            Respuesta += "Content-Type: text/html\n";
                            ArchivoWeb = true;
                            break;
                        case ".gif":
                            Respuesta += "Vary: Accept-Encoding,User-Agent\n";
                            Respuesta += "Content-Type: image/gif\n";
                            ArchivoWeb = false;
                            break;
                        case ".png":
                            Respuesta += "Vary: Accept-Encoding,User-Agent\n";
                            Respuesta += "Content-Type: image/png\n";
                            ArchivoWeb = false;
                            break;
                        case ".jpeg":
                        case ".jpg":
                            Respuesta += "Vary: Accept-Encoding,User-Agent\n";
                            Respuesta += "Content-Type: image/jpeg\n";
                            ArchivoWeb = false;
                            break;
                        default:
                            Respuesta += "Vary: Accept-Encoding,User-Agent\n";
                            Respuesta += "Content-Type:application/octet-stream\n";
                            ArchivoWeb = false;
                            break;
                    }

                    Respuesta += "\n";

                    //En caso de que sea peticion GET añadimos el código
                    if (EsGet) {

                        //Dependiendo de si es un html o un archivo
                        if (ArchivoWeb) {

                            /*
                             * Cargamos y leemos el html (obsoleto)
                             *
                             * String codeHTML = ""; BufferedReader entrada =
                             * new BufferedReader( new
                             * FileReader(ArchivoDemand));
                             *
                             * String lineaTEXTO;
                             *
                             * while ((lineaTEXTO = entrada.readLine()) != null)
                             * { codeHTML += (lineaTEXTO + "\n"); } Respuesta +=
                             * codeHTML;
                             */

                            ArchivoEnBytes = new FileInputStream('.' + PeticionArch);
                            nBytesArch = (int) ArchivoDemand.length();
                            ContenedorBytes = new byte[nBytesArch];
                            ArchivoEnBytes.read(ContenedorBytes);
                        } else {
                            //Cargamos en un array de bytes el archivo
                            ArchivoEnBytes = new FileInputStream('.' + PeticionArch);
                            nBytesArch = (int) ArchivoDemand.length();
                            ContenedorBytes = new byte[nBytesArch];
                            ArchivoEnBytes.read(ContenedorBytes);
                        }
                    }
                } else {//En caso de que el archivo en cache no sea mas viejo que el del server
                    Respuesta = "HTTP/1.1 304 Not Modified\n";
                    Respuesta = "Date: " + fechacf + "\n";
                    Respuesta += "Server: UnrealJServer/" + System.getProperty("java.version")
                            + " (" + System.getProperty("os.name") + ")\n";

                    ArchivoWeb = false;
                    LengthArch = (long) 0;
                    //Aqui envio la cabecera para que el navegador lo cargue de su cache
                    //aunque no conseguí que esta parte lleguase a funcionar bien
                }
            } else { //En caso de que sea un directorio

                //Añadimos index.html
                if ('/' == (PeticionArch.charAt(PeticionArch.length() - 1))) {
                    PeticionArch += Configuracion.DIRECTORY_INDEX;
                } else {
                    PeticionArch += "/" + Configuracion.DIRECTORY_INDEX;
                }

                //Y volvemos a la funcion con el archivo demandado corregido
                GenerarRespuesta(PeticionArch, EsGet, true);
            }

        } else {
            //Si no existe el archivo
            if (EsDir) {
                if (Configuracion.ALLOW) {
                    GenerarPaginaDir(ArchivoDemand.getParent());
                } else {
                    System.out.println("Archivo solicitado no encontrado: " + PeticionArch);
                    Error404();
                }
            } else {
                System.out.println("Archivo solicitado no encontrado: " + PeticionArch);
                Error404();
            }
        }
    }

    public void GenerarRespuestaDo(String LineaHeader) throws Exception {
        //Generamos la página de respuesta a una página dinámica
        FormularioDo = LineaHeader.substring(LineaHeader.lastIndexOf("/") + 1, LineaHeader.indexOf(".do"));

        //Sacamos los parametros y sus nombres
        int i, i2, i3;

        i = LineaHeader.indexOf(".do?");
        i2 = LineaHeader.indexOf("=", i);

        ArgFormulario.add(LineaHeader.substring(i + 4, i2));

        if (LineaHeader.indexOf("&") != -1) {
            ArgFormularioVal.add(LineaHeader.substring(i2 + 1, LineaHeader.indexOf("&")));
        } else {
            ArgFormularioVal.add(LineaHeader.substring(i2 + 1, LineaHeader.length()));
        }

        while ((i = (LineaHeader.indexOf("&", i + 1))) != -1) {

            i2 = LineaHeader.indexOf("=", i);
            ArgFormulario.add(LineaHeader.substring(i + 1, i2));

            if ((i3 = LineaHeader.indexOf("&", i2 + 1)) != -1) {
                ArgFormularioVal.add(LineaHeader.substring(i2 + 1, i3));
            } else {
                ArgFormularioVal.add(LineaHeader.substring(i2 + 1, LineaHeader.length()));
            }
        }

        //Los pasamos a un map
        int j;
        for (j = 0; j <= ArgFormulario.size() - 1; j++) {
            ArgumentosDo.put(ArgFormulario.get(j), ArgFormularioVal.get(j));
        }

        //Y generamos el html
        String CodeHTML = (ServerUtils.processDynRequest(FormularioDo, ArgumentosDo));

        Respuesta = "HTTP/1.1 200 OK\n";
        Respuesta += "Date: " + fechacf + "\n";
        Respuesta += "Server: UnrealJServer/" + System.getProperty("java.version")
                + " (" + System.getProperty("os.name") + ")\n";
        Respuesta += "Last-Modified: " + fechacf + "\n";
        Respuesta += "Content-Length: " + CodeHTML.length() + "\n\n";
        Respuesta += CodeHTML;

        LengthArch = (long) CodeHTML.length();
        ArchivoWeb = false;
    }

/////////////////// Empezamos el Hilo de Ejecución  \\\\\\\\\\\\\\\\\\\\
    public ThreadServidor(Socket s) {
        socket = s;
    }

    @Override
    public void run() {
        try {
            // Establecemos el canal de entrada
            BufferedReader sInput = new BufferedReader(new InputStreamReader(
                    socket.getInputStream()));

            // Establecemos el canal de salida
            DataOutputStream sOutput = new DataOutputStream(socket.getOutputStream());

            //Recibimos el mensaje del cliente, linea a linea
            String LineaHeader = null;

            while ((LineaHeader = sInput.readLine()).length() != 0) {
                if (LineaHeader != null) {
                    Recibido += (LineaHeader) + "\n";
                }
            }

            Recibido = Recibido.substring(4);

            //Miramos si el archivo en cache del servidor es más viejo que el actual


            int x1 = Recibido.indexOf("If-Modified-Since");

            if (x1 != -1) {
                int x2 = Recibido.indexOf("\n", x1);
                PModificado = Recibido.substring(x1 + 19, x2);
                PetModific = true;
                FechaMod = formato.parse(PModificado);
            } else {
                PetModific = false;
            }

            //Establecemos la hora en la que se ha recibido la petición
            fechasf.getTime();
            fechacf = formato.format(fechasf);


            // Separamos la peticion en palabras
            StringTokenizer tokenpalpet = new StringTokenizer(Recibido);
            while (tokenpalpet.hasMoreTokens()) {
                PalPet.add(tokenpalpet.nextToken().toString());
            }

            String HeaderPet = PalPet.get(1).toString();
            // Procesamos el tipo de petición
            switch (PalPet.get(0)) {
                case "GET":
                    if (HeaderPet.indexOf(".do?") == -1) {
                        GenerarRespuesta(HeaderPet, true, false);
                    } else {
                        GenerarRespuestaDo(HeaderPet);
                    }
                    break;

                case "HEAD":
                    GenerarRespuesta(HeaderPet, false, false);
                    break;

                case "POST":
                    Respuesta = "HTTP/1.1 501 NOT IMPLEMENTED";
                    break;

                case "PUT":
                    Respuesta = "HTTP/1.1 501 NOT IMPLEMENTED";
                    break;

                case "DELETE":
                    Respuesta = "HTTP/1.1 501 FORBIDDEN";
                    break;

                default:
                    System.out.println("Recibida petición erronea!!");
                    Respuesta = "HTTP/1.1 400 Bad Request";
                    break;
            }

            //Enviamos la respuesta al cliente
            sOutput.writeBytes(Respuesta);

            //En caso de ser un archivo, enviamos el array de bytes
            if (ArchivoWeb = true) {
                //byte[] buffer = new byte[1024];
                sOutput.write(ContenedorBytes, 0, nBytesArch);
            }

            //Añadimos entradas a los logs
            String MensajeLog;


            if ((Respuesta.charAt(9) == '3') || (Respuesta.charAt(9) == '2')) {


                MensajeLog = "• Conexión realizada con exito: \n"
                        + "-Petición del cliente: " + Recibido + "\n"
                        + "-Dirección IP cliente: " + socket.getInetAddress() + "\n"
                        + "-Fecha de la petición: " + fechacf + "\n"
                        + "-Código de respuesta: " + Respuesta.substring(9, 13) + "\n"
                        + "-Tamaño del archivo enviado: " + LengthArch.toString() + "\n\n";
                log.Loggin(MensajeLog, false);
            } else {
                MensajeLog = "• Error en la petición: \n"
                        + "-Petición del cliente: " + Recibido + "\n"
                        + "-Dirección IP cliente: " + socket.getInetAddress() + "\n"
                        + "-Fecha de la petición: " + fechacf + "\n"
                        + "-Código de error: " + Respuesta.substring(9, 13) + "\n"
                        + "-Header de Respuesta: " + Respuesta.substring(0, Respuesta.indexOf("\n")) + "\n\n";
                log.Loggin(MensajeLog, true);
            }

            // Cerramos los flujos
            sOutput.close();
            sInput.close();

        } catch (SocketTimeoutException e) {
            System.err.println("30 segs sin recibir nada");
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        } finally {
            try {
                // Cerramos el socket
                socket.close();
            } catch (IOException ex) {
                Logger.getLogger(ThreadServidor.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}