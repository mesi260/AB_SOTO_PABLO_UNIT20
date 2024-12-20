#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "citaMedica.h"

class Medico {
private:
    std::string nombre;
    std::string ID;
    std::string especialidad;
    bool disponibilidad;
    std::vector<CitaMedica*> citas;

public:
    // Constructor
    Medico(std::string _nombre, std::string _ID, std::string _especialidad, bool _disponibilidad)
        : nombre(_nombre), ID(_ID), especialidad(_especialidad), disponibilidad(_disponibilidad) {}

    void registrarMedico() {
        std::ofstream archivo("medicos.txt", std::ios::app);
        if (archivo.is_open()) {
            archivo << "Nombre: " << nombre << "\n";
            archivo << "ID: " << ID << "\n";
            archivo << "Especialidad: " << especialidad << "\n";
            archivo << "Disponibilidad: " << (disponibilidad ? "Sí" : "No") << "\n\n";
            archivo.close();
        } else {
            std::cerr << "Error al abrir el archivo para registrar el médico.\n";
        }
    }
    void modificarMedico(const std::string& nuevoNombre, const std::string& nuevaEspecialidad) {
        nombre = nuevoNombre;
        especialidad = nuevaEspecialidad;
        std::cout << "Médico modificado a " << nombre << " con especialidad " << especialidad << "\n";
    }
    void añadirCita(CitaMedica* cita) {
        citas.push_back(cita);
    }
    // Metodos de consulta
    std::string getNombre() const { return nombre; }
    std::string getEspecialidad() const { return especialidad; }
    std::string getID() const { return ID; }
    bool getDisponibilidad() const { return disponibilidad; }
    // Metodo estatico para obtener el número de campos requeridos
    static int camposRequeridos() { return 4; } // Nombre, ID, Especialidad, Disponibilidad
    // Metodo para comparar IDs ignorando mayus y espacios
    bool compararID(const std::string& otroID) const {
        std::string id1 = ID, id2 = otroID;
        // Eliminar espacios y convertir a minus
        id1.erase(0, id1.find_first_not_of(' '));
        id1.erase(id1.find_last_not_of(' ') + 1);
        id2.erase(0, id2.find_first_not_of(' '));
        id2.erase(id2.find_last_not_of(' ') + 1);

        std::transform(id1.begin(), id1.end(), id1.begin(), ::tolower);
        std::transform(id2.begin(), id2.end(), id2.begin(), ::tolower);

        return id1 == id2;
    }
};
