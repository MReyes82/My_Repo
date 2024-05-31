package escuelaClases;

public class Main 
{
    public static void main(String[] args) 
    {
        Control.inicializarArreglos();
        Control.testMaestros();
        Control.testAlumnos();
        new MenuPrincipal().setVisible(true);
    }
}
