package interfaces;

import escuelaClases.*;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;


// TODO: AGREGAR LOGICA PARA QUE SOLICITE LOS LAS INSTANCIAS DE ALUMNOS PARA EL GRUPO

public class AltaGrupo extends JFrame 
{
    public AltaGrupo() 
    {
        setTitle("Alta Grupo");
        setSize(400, 300);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(3, 2));

        JTextField numField = new JTextField();
        JTextField cantidadField = new JTextField();

        add(new JLabel("Numero del grupo:"));
        add(numField);
        add(new JLabel("Cantidad maxima de alumnos:"));
        add(cantidadField);

        JButton submitButton = new JButton("Submit");
        submitButton.addActionListener(e -> {
            if (validateIntegerField(numField) && validateIntegerField(cantidadField)) {
                int num = Integer.parseInt(numField.getText());
                int cantidad = Integer.parseInt(cantidadField.getText());

                if (num < 0 || cantidad < 0) {
                    JOptionPane.showMessageDialog(this, "ERROR: valor invalido ingresado.");
                    return;
                }

                Maestro profesorDelGrupo = seleccionarMaestro();
                if (profesorDelGrupo == null) {
                    JOptionPane.showMessageDialog(this, "No se seleccionó un maestro válido.");
                    return;
                }

                List<Alumno> alumnosDelGrupo = seleccionarAlumnos(cantidad);
                if (alumnosDelGrupo.isEmpty()) {
                    JOptionPane.showMessageDialog(this, "No se seleccionaron alumnos válidos.");
                    return;
                }

                Grupo nuevoGrupo = new Grupo(num, cantidad, profesorDelGrupo);
                nuevoGrupo.setAlumnos(new Alumno[nuevoGrupo.getCantidadMaxAlumnos()]);
                
                Control.agregarGrupo(nuevoGrupo);
                JOptionPane.showMessageDialog(this, "Grupo agregado exitosamente.");
                dispose();
            } else {
                JOptionPane.showMessageDialog(this, "ERROR: valor invalido ingresado.");
            }
        });

        add(submitButton);
        setVisible(true);
    }

    private Maestro seleccionarMaestro() {
        List<Maestro> maestros = Control.getProfesores();
        String[] opciones = maestros.stream().map(Maestro::getNombre).toArray(String[]::new);

        if (opciones.length == 0) {
            JOptionPane.showMessageDialog(this, "No hay maestros disponibles.");
            return null;
        }

        String seleccion = (String) JOptionPane.showInputDialog(this, "Seleccione el maestro del grupo:", "Seleccionar Maestro",
                JOptionPane.QUESTION_MESSAGE, null, opciones, opciones[0]);

        return maestros.stream().filter(maestro -> maestro.getNombre().equals(seleccion)).findFirst().orElse(null);
    }

    private List<Alumno> seleccionarAlumnos(int cantidad) {
        List<Alumno> alumnosSeleccionados = new ArrayList<>();
        List<Alumno> alumnosDisponibles = Control.getEstudiantes();

        for (int i = 0; i < cantidad; i++) {
            String[] opciones = alumnosDisponibles.stream().map(Alumno::getNombre).toArray(String[]::new);
            if (opciones.length == 0) {
                JOptionPane.showMessageDialog(this, "No hay suficientes alumnos disponibles.");
                break;
            }

            String seleccion = (String) JOptionPane.showInputDialog(this, "Seleccione el alumno " + (i + 1) + " del grupo:", "Seleccionar Alumno",
                    JOptionPane.QUESTION_MESSAGE, null, opciones, opciones[0]);

            Alumno alumnoSeleccionado = alumnosDisponibles.stream()
                    .filter(alumno -> alumno.getNombre().equals(seleccion))
                    .findFirst()
                    .orElse(null);

            if (alumnoSeleccionado != null) {
                alumnosSeleccionados.add(alumnoSeleccionado);
                alumnosDisponibles.remove(alumnoSeleccionado);
            }
        }

        return alumnosSeleccionados;
    }

    public boolean validateIntegerField(JTextField textField) {
        try {
            Integer.parseInt(textField.getText().trim());
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}
