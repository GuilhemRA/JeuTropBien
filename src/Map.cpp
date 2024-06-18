#include <vector>
#include <iostream>
#include <fstream>
#include "Operator.hpp"
#include "GLHelpers.hpp"
#include "Map.hpp"
#include "Tours.hpp"

struct Tour;

void MAP::determineCouleursCase() {
    Case pixel;
    for (size_t i = 0; i < this->imageMap.data_size(); i += this->imageMap.channels_count()) {
        pixel.position.x = i / this->imageMap.channels_count() % this->nombreDePixelEnLigne;
        pixel.position.y = i / this->imageMap.channels_count() / this->nombreDePixelEnLigne;
        pixel.couleur = {(int)*(this->imageMap.data() + i), (int)*(this->imageMap.data() + i + 1), (int)*(this->imageMap.data() + i + 2)};
        this->ListeCase.push_back(pixel);
    }
}

Couleur MAP::couleurITD(std::string const &type) {
    Couleur couleur;
    // Ouvre le fichier Map.itd
    std::string cheminITD = {"../../data/Map.itd"};
    std::ifstream inputFile(cheminITD);
    std::string line;

    while (getline(inputFile, line))
    {
        // Récupération des paramètres de couleurs des cases
        if (line.find(type) != std::string::npos)
        {
            std::istringstream iss(line);
            std::string _type;
            std::vector<int> vectCouleur;

            iss >> _type;

            int nombre;
            while (iss >> nombre)
            {
                if (nombre < 0 || nombre > 255)
                {
                    std::cerr << "ERREUR - dans l'ITD : " << type << " non valide : " << nombre << " n'est pas entre 0 et 255." << std::endl;
                    std::exit(EXIT_FAILURE);
                }
                vectCouleur.push_back(nombre);
            }
            couleur.R = vectCouleur[0];
            couleur.G = vectCouleur[1];
            couleur.B = vectCouleur[2];
        }
    }
    inputFile.close();

    return couleur;
}

void MAP::associeCouleurTypeCase() {
    for(Case &pixel : this->ListeCase) {
        if(pixel.couleur == couleurITD("chemin")) {
            pixel.typeDeCase = typeCase::chemin;
        }
        else if(pixel.couleur == couleurITD("depart")) {
            pixel.typeDeCase = typeCase::chemin_depart;
        }
        else if(pixel.couleur == couleurITD("arrivee")) {
            pixel.typeDeCase = typeCase::chemin_arrivee;
        }
        else if(pixel.couleur == couleurITD("tour")) {
            pixel.typeDeCase = typeCase::emplacement_tour;
        }
    }
}

void MAP::recupereNoeudsITD() {
    std::vector<Noeud> NOEUDS;

    std::string cheminITD = {"../../data/Map.itd"};
    std::ifstream inputFile(cheminITD);
    std::string line;

    int graph_noeuds;    // graph : graph_noeuds
    int nodes_count{0}; // compte le nombre de nodes référencés

    while (getline(inputFile, line))
    {
        if (line.find("graph") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string graph;
            iss >> graph;
            iss >> graph_noeuds;
        }
        // Récupération des paramètres des noeuds
        if (line.find("node") != std::string::npos)
        {
            nodes_count++;
            std::istringstream iss(line);
            std::string noeud;
            std::vector<float> nombres;

            // on zap le premier element qui est un noeud
            iss >> noeud;

            float nombre;
            while (iss >> nombre)
                nombres.push_back(nombre);

            Noeud nouveauNoeud;
            nouveauNoeud.numeroNoeud = static_cast<int>(nombres[0]);
            nouveauNoeud.position.x = nombres[1];
            nouveauNoeud.position.y = nombres[2];
            for (size_t i{3}; i < nombres.size(); i++)
                nouveauNoeud.NoeudsConnectado.push_back(nombres[i]);
            NOEUDS.push_back(nouveauNoeud);
        }
    }
    inputFile.close();

    if (graph_noeuds != nodes_count)
    {
        std::cerr << "ERREUR - ITD : Le nombre de noeuds est mal référencé c tro nul." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    this->ListeNoeud = NOEUDS;
}

void MAP::creationGraph() {
    for (Noeud &noeud : this->ListeNoeud) //Pour chaque nodes de l'ITD
        for (int numeroNoeudConnectado : noeud.NoeudsConnectado) //On boucle sur les noeuds connectés
            for (Noeud &noeudAConnecter : this->ListeNoeud)
                if (numeroNoeudConnectado == noeudAConnecter.numeroNoeud)
                {
                    float distance = (std::abs(noeud.position.x - noeudAConnecter.position.x) + std::abs(noeud.position.y - noeudAConnecter.position.y));
                    this->Graph.add_directed_edge(noeud.numeroNoeud, noeudAConnecter.numeroNoeud, distance);
                }
}

void MAP::plusCourtChemin()
{
    std::vector<int> Departs; // Spawns ennemi
    for (Noeud &noeud : this->ListeNoeud)
    {
        if (noeud.NoeudsConnectado.empty()) {
            Departs.push_back(noeud.numeroNoeud);
        }
    }
    int Arrivee{0};              // id de la Base

    // Pour chaque Départs, on attribue un plus court chemin par rapport à l'Arrivée
    for (int depart : Departs)
    {
        std::unordered_map<int, std::pair<float, int>> DISTANCES{this->Graph.dijkstra(Arrivee, depart)};
        std::vector<int> numeroDuPlusCourtChemin;
        std::vector<Noeud> plusCourtChemin;
        auto segmentFinalEntreNoeuds{DISTANCES.at(depart)};

        numeroDuPlusCourtChemin.push_back(depart);
        while (segmentFinalEntreNoeuds.second != Arrivee)
        {
            numeroDuPlusCourtChemin.push_back(segmentFinalEntreNoeuds.second);
            segmentFinalEntreNoeuds = DISTANCES.at(segmentFinalEntreNoeuds.second);
        }
        numeroDuPlusCourtChemin.push_back(Arrivee);

        // Du tableau d'id, on en déduit les noeuds composants le chemin le plus court dans l'ordre.
        for (int numeroPlusCourtNoeud : numeroDuPlusCourtChemin)
        {
            for (Noeud &noeud : this->ListeNoeud)
                if (noeud.numeroNoeud == numeroPlusCourtNoeud)
                    plusCourtChemin.push_back(noeud);
        }
        this->ListePlusCourtChemin.push_back(plusCourtChemin);
    }
}

void MAP::determineTypeCase() {
    for(Case &pixel : this->ListeCase) {

        int pixelActuel = pixel.position.x+(pixel.position.y*nombreDePixelEnLigne);

        int pixelHaut = pixelActuel - nombreDePixelEnLigne;
        int pixelBas = pixelActuel + nombreDePixelEnLigne;
        int pixelGauche = pixelActuel - 1;
        int pixelDroite = pixelActuel + 1;

        if(ListeCase[pixelActuel].typeDeCase == typeCase::chemin) {
            // Si la case de gauche et la case de droite sont des chemins
            if(ListeCase[pixelGauche].typeDeCase == typeCase::chemin && ListeCase[pixelDroite].typeDeCase == typeCase::chemin) {
                // Si haut chemin
                if(ListeCase[pixelHaut].typeDeCase == typeCase::chemin) {
                        pixel.typeDeChemin = typeChemin::chemin_T_inverse;
                        pixel.EstUnNoeud = true;
                }
                // Si bas chemin
                else if(ListeCase[pixelBas].typeDeCase == typeCase::chemin) {
                        pixel.typeDeChemin = typeChemin::chemin_T;
                        pixel.EstUnNoeud = true;
                }
                else {
                    pixel.typeDeChemin = typeChemin::chemin_horizontal;
                }
            }
            else if(ListeCase[pixelGauche].typeDeCase == typeCase::chemin) {
                if(ListeCase[pixelHaut].typeDeCase == typeCase::chemin && ListeCase[pixelBas].typeDeCase == typeCase::chemin) {
                    pixel.typeDeChemin = typeChemin::chemin_T_gauche;
                    pixel.EstUnNoeud = true;
                }
                else if(ListeCase[pixelHaut].typeDeCase == typeCase::chemin) {
                    pixel.typeDeChemin = typeChemin::chemin_haut_gauche;
                    pixel.EstUnNoeud = true;
                }
                else {
                    pixel.typeDeChemin = typeChemin::chemin_gauche_bas;
                    pixel.EstUnNoeud = true;
                }
            }
            else if(ListeCase[pixelDroite].typeDeCase == typeCase::chemin) {
                if(ListeCase[pixelHaut].typeDeCase == typeCase::chemin || ListeCase[pixelHaut].typeDeCase == typeCase::chemin_depart) {
                    pixel.typeDeChemin = typeChemin::chemin_haut_droite;
                }
                else {
                    pixel.typeDeChemin = typeChemin::chemin_droite_bas;
                    pixel.EstUnNoeud = true;
                }
            }
            else {
                pixel.typeDeChemin = typeChemin::chemin_vertical;
            }
        }
        else if(ListeCase[pixelActuel].typeDeCase == typeCase::nonchemin) {
            int numero = (int)(pixel.position.x*pixel.position.y)%3;
            if(numero==0) {
                pixel.typeDeCase = typeCase::nonchemin_1;
            }
            if(numero==1) {
                pixel.typeDeCase = typeCase::nonchemin_2;
            }
            if(numero==2) {
                pixel.typeDeCase = typeCase::nonchemin_3;
            }             
        }
        else if(ListeCase[pixelActuel].typeDeCase == typeCase::chemin_depart) {
            pixel.EstUnNoeud = true;
        }
        else if(ListeCase[pixelActuel].typeDeCase == typeCase::chemin_arrivee) {
            pixel.EstUnNoeud = true;
        }
    }
}

void MAP::dessineMap(std::unordered_map<typeCase, GLuint> &tiles_textures, std::unordered_map<typeChemin, GLuint> &paths_textures) {
    for(Case &pixel : this->ListeCase) {
        if (pixel.typeDeCase == typeCase::chemin)
            draw_quad_with_texture(pixel.position.x, pixel.position.y, paths_textures[pixel.typeDeChemin], *this);
        else
            draw_quad_with_texture(pixel.position.x, pixel.position.y, tiles_textures[pixel.typeDeCase], *this);
    }
}