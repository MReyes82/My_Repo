package escuelaClases;
import interfaces.*;

import javax.swing.*;
import java.awt.*;

// TODO: AGREGAR BOTON DE CERRAR, AQUI Y EN TODAS LAS DEMAS CLASES
// TODO: PENDIENTE REESTILIZADO, NO DEBE TOMAR MAS DE 4 HORAS

public class MenuPrincipal extends JFrame {
    public MenuPrincipal() {
        setTitle("Menu Principal");
        setSize(300, 400);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(11, 1));

        addButton("Dar de alta maestro", AltaMaestro.class);
        addButton("Dar de alta alumno", AltaAlumno.class);
        addButton("Dar de alta grupo", AltaGrupo.class);
        addButton("Mostrar datos de maestros", MostrarMaestros.class);
        addButton("Mostrar datos de alumnos", MostrarAlumnos.class);
        addButton("Mostrar datos de grupos", MostrarGrupos.class);
        addButton("Mostrar nombres de personas alfabeticamente", OrdenarPorNombre.class);
        addButton("Mostrar personas ordenadas por edad", OrdenarPorEdad.class);
        addButton("Eliminar elemento de un arreglo", EliminarInstancia.class);
        addButton("Buscar persona", BuscarPersona.class);
        addButton("Agregar actividades extracurriculares", AgregarActividades.class);
    }

    private void addButton(String text, Class<? extends JFrame> frameClass) {
        JButton button = new JButton(text);
        button.addActionListener(e -> {
            try {
                frameClass.getConstructor().newInstance().setVisible(true);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        });
        add(button);
    }
}
