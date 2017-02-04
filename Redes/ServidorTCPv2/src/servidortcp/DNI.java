package servidortcp;

import java.util.Map;

public class DNI implements MiniServlet {

    /*
     * Para el correcto funcionamiento es necesario un constructor sin
     * parámetros y público
     */
    public DNI() {
    }
    public static final String NIF_STRING_ASOCIATION = "TRWAGMYFPDXBNJZSQVHLCKE";

    @Override
    public String doGet(Map<String, String> parameters) {
        int nDNI = Integer.parseInt(parameters.get("dni"));

        return printHeader() + printBody(nDNI) + printEnd();
    }

    private char letraDNI(int dni) {
        return NIF_STRING_ASOCIATION.charAt(dni % 23);
    }

    private String printHeader() {
        return "<html><head> <title>DNI</title> </head> ";
    }

    private String printBody(int number) {
        return "<body><center><h1> DNI:  " + number + "<font color=\"red\">" + letraDNI(number) + "</font></h1></center></body>";
    }

    private String printEnd() {
        return "</html>";
    }
}
