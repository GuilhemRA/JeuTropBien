#include "App.hpp"

App::App() : _previousTime(0.0), _viewSize(1.0) {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Chargement des textures de la Map
    paths_textures[typeChemin::chemin_vertical] = loadTexture(img::load(make_absolute_path("images/Tuiles/chemin_vertical.png", true), 3, true));
    paths_textures[typeChemin::chemin_horizontal] = loadTexture(img::load(make_absolute_path("images/Tuiles/chemin_horizontal.png", true), 3, true));

    paths_textures[typeChemin::chemin_haut_gauche] = loadTexture(img::load(make_absolute_path("images/Tuiles/chemin_tournant_haut_gauche.png", true), 3, false));
    paths_textures[typeChemin::chemin_haut_droite] = loadTexture(img::load(make_absolute_path("images/Tuiles/chemin_tournant_haut_droite.png", true), 3, false));
    paths_textures[typeChemin::chemin_gauche_bas] = loadTexture(img::load(make_absolute_path("images/Tuiles/chemin_tournant_gauche_bas.png", true), 3, false));
    paths_textures[typeChemin::chemin_droite_bas] = loadTexture(img::load(make_absolute_path("images/Tuiles/chemin_tournant_droite_bas.png", true), 3, false));

    paths_textures[typeChemin::chemin_T] = loadTexture(img::load(make_absolute_path("images/Tuiles/chemin_T.png", true), 3, false));
    paths_textures[typeChemin::chemin_T_inverse] = loadTexture(img::load(make_absolute_path("images/Tuiles/chemin_T_inverse.png", true), 3, false));
    paths_textures[typeChemin::chemin_T_gauche] = loadTexture(img::load(make_absolute_path("images/Tuiles/chemin_T_gauche.png", true), 3, true));

    tiles_textures[typeCase::chemin_depart] = loadTexture(img::load(make_absolute_path("images/Tuiles/chemin_depart.png", true), 3, true));
    tiles_textures[typeCase::chemin_arrivee] = loadTexture(img::load(make_absolute_path("images/Tuiles/chemin_arrivee.png", true), 3, true));

    tiles_textures[typeCase::emplacement_tour] = loadTexture(img::load(make_absolute_path("images/Tuiles/emplacement_tour.png", true), 3, true));

    tiles_textures[typeCase::nonchemin_1] = loadTexture(img::load(make_absolute_path("images/Tuiles/nonchemin_1.png", true), 3, true));
    tiles_textures[typeCase::nonchemin_2] = loadTexture(img::load(make_absolute_path("images/Tuiles/nonchemin_2.png", true), 3, true));
    tiles_textures[typeCase::nonchemin_3] = loadTexture(img::load(make_absolute_path("images/Tuiles/nonchemin_3.png", true), 3, true));

    // Chargement des textures des ennemis
    ennemis_textures[typeEnnemi::elisabeth] = loadTexture(img::load(make_absolute_path("images/Ennemis/elisabeth.png", true), 3, true));
    ennemis_textures[typeEnnemi::colin] = loadTexture(img::load(make_absolute_path("images/Ennemis/colin.png", true), 3, true));
    ennemis_textures[typeEnnemi::milan] = loadTexture(img::load(make_absolute_path("images/Ennemis/milan.png", true), 3, true));

    // Chargement des textures des tours
    tours_textures[typeTour::archer] = loadTexture(img::load(make_absolute_path("images/Tours/TourArcher1x1.png", true), 3, true));
    tours_textures[typeTour::chevalier] = loadTexture(img::load(make_absolute_path("images/Tours/TourChevalier1x1.png", true), 3, true));
    tours_textures[typeTour::sorcier] = loadTexture(img::load(make_absolute_path("images/Tours/TourSorcier1x1.png", true), 3, true));

    GLuint zoneDegats = loadTexture(img::load(make_absolute_path("images/Tuiles/zoneDegats.png", true), 3, true));
}

void App::setup() {
    // Set the clear color to a nice blue
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    // Setup the text renderer with blending enabled and white text color
    TextRenderer.ResetFont();
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer.SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.EnableBlending(true);

    // MAP
    MAP1.determineCouleursCase();
    MAP1.associeCouleurTypeCase();
    MAP1.determineTypeCase();
    MAP1.recupereNoeudsITD();
    MAP1.creationGraph();
    MAP1.plusCourtChemin();

    // ENNEMIS
        // ELISABETH
        Elisabeth.texture = ennemis_textures[typeEnnemi::elisabeth];
        Elisabeth.position = MAP1.ListePlusCourtChemin[0][0].position;
        Elisabeth.VitesseEnnemi = 1.5f;
        Elisabeth.DegatsEnnemi = 15;
        Elisabeth.PdVEnnemi = 100;
        VectEnnemis.push_back(Elisabeth);
        //COLIN
        Colin.texture = ennemis_textures[typeEnnemi::colin];
        Colin.position = MAP1.ListePlusCourtChemin[0][1].position;
        Colin.DegatsEnnemi = 5;
        Colin.PdVEnnemi = 50;
        VectEnnemis.push_back(Colin);
        // MILAN
        Milan.texture = ennemis_textures[typeEnnemi::milan];
        Milan.position = MAP1.ListePlusCourtChemin[0][0].position;
        Milan.VitesseEnnemi = .8f;
        Milan.DegatsEnnemi = 1;
        Milan.PdVEnnemi = 200;
        VectEnnemis.push_back(Milan);

    // TOURS
        // ARCHER
        Archer.texture = tours_textures[typeTour::archer];
        VectTours.push_back(Archer);
        // CHEVALIER
        Chevalier.texture = tours_textures[typeTour::chevalier];
        VectTours.push_back(Chevalier);
        // SORCIER
        Sorcier.texture = tours_textures[typeTour::sorcier];
        VectTours.push_back(Sorcier);

}

void App::update() {

    const double currentTime {glfwGetTime()};
    const double elapsedTime {currentTime - _previousTime};

    Colin.recupereTemps(elapsedTime);
    Elisabeth.recupereTemps(elapsedTime);
    Milan.recupereTemps(elapsedTime);

    _previousTime = currentTime;
    
    render();
}

void App::render() {

    if(Jeu==0) {
        // Clear the color and depth buffers of the frame buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        TextRenderer.SetTextSize(SimpleText::SIZE_32);
        TextRenderer.Label("Appuyez sur la touche", _width / 2, _height / 2 - 50, SimpleText::CENTER);
        TextRenderer.Label("S", _width / 2, _height / 2, SimpleText::CENTER);
        TextRenderer.Label("pour jouer", _width / 2, _height / 2 + 50, SimpleText::CENTER);
        TextRenderer.Render();

    } if(Jeu==1) {

        if(PdVCible<=0){
            Jeu=2;
        }
        if(CompteurVagueEnnemis==4 && PdVCible>0) {
            Jeu=3;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Clear the color and depth buffers of the frame buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        MAP1.dessineMap(tiles_textures,paths_textures);

        if(CompteurPlacementTour==6  && PdVCible>0 && CompteurVagueEnnemis!=4) {
            if(CompteurVagueEnnemis%3==1) {
                if (Milan.numeroNoeudActuel != MAP1.ListePlusCourtChemin[0].size() -1 && Milan.PdVEnnemi>0) {
                    Milan.deplacement(MAP1.ListePlusCourtChemin,MAP1);
                        if(Milan.position.x-(int)Milan.position.x>.5f) {
                            xEnnemi = (int)Milan.position.x + 1;
                        } else {xEnnemi = (int)Milan.position.x;}
                        if(Milan.position.y-(int)Milan.position.y>.5f) {
                            yEnnemi = (int)Milan.position.y + 1;
                        } else {yEnnemi = (int)Milan.position.y;}
                    Milan.siDansZoneDegats(xEnnemi,yEnnemi, VectPosTour);

                } else if(Milan.PdVEnnemi<=0) {
                    TextRenderer.Label("un Milan sauvage est mort", _width / 50, 300, SimpleText::LEFT);
                    TextRenderer.Render();
                    CompteurVagueEnnemis++;
                } else if(degatOuNonM==false) {
                    PdVCible-=Milan.DegatsEnnemi;
                    degatOuNonM=true;
                    CompteurVagueEnnemis++;
                }
            } if(CompteurVagueEnnemis%3==2) {
                if (Colin.numeroNoeudActuel != MAP1.ListePlusCourtChemin[0].size() -1 && Colin.PdVEnnemi>0) {
                    Colin.deplacement(MAP1.ListePlusCourtChemin,MAP1);
                        if(Colin.position.x-(int)Colin.position.x>.5f) {
                            xEnnemi = (int)Colin.position.x + 1;
                        } else {xEnnemi = (int)Colin.position.x;}
                        if(Colin.position.y-(int)Colin.position.y>.5f) {
                            yEnnemi = (int)Colin.position.y + 1;
                        } else {yEnnemi = (int)Colin.position.y;}
                    Colin.siDansZoneDegats(xEnnemi,yEnnemi, VectPosTour);

                } else if(Colin.PdVEnnemi<=0) {
                    TextRenderer.Label("un Colin sauvage est mort", _width / 50, 330, SimpleText::LEFT);
                    TextRenderer.Render();
                    CompteurVagueEnnemis++;
                } else if(degatOuNonC==false) {
                    PdVCible-=Colin.DegatsEnnemi;
                    degatOuNonC=true;
                    CompteurVagueEnnemis++;
                }            
            } if(CompteurVagueEnnemis%3==0) {
                if (Elisabeth.numeroNoeudActuel != MAP1.ListePlusCourtChemin[0].size() -1 && Elisabeth.PdVEnnemi>0) {
                    Elisabeth.deplacement(MAP1.ListePlusCourtChemin,MAP1);
                        if(Elisabeth.position.x-(int)Elisabeth.position.x>.5f) {
                            xEnnemi = (int)Elisabeth.position.x + 1;
                        } else {xEnnemi = (int)Elisabeth.position.x;}
                        if(Elisabeth.position.y-(int)Elisabeth.position.y>.5f) {
                            yEnnemi = (int)Elisabeth.position.y + 1;
                        } else {yEnnemi = (int)Elisabeth.position.y;}
                    Elisabeth.siDansZoneDegats(xEnnemi,yEnnemi, VectPosTour);

                } else if(Elisabeth.PdVEnnemi<=0) {
                    TextRenderer.Label("une Elisabeth sauvage est morte, tant mieux !", _width / 50, 360, SimpleText::LEFT);
                    TextRenderer.Render();
                    CompteurVagueEnnemis++;
                } else if(degatOuNonE==false) {
                    PdVCible-=Elisabeth.DegatsEnnemi;
                    degatOuNonE=true;
                    CompteurVagueEnnemis++;
                }
            }
        }

        // Affichage du placement des Tours
        if(ActionPlacementTour==1 || CompteurPlacementTour>0) {

            for(int i{0}; i<3; i++) {
                if(VectTours[i].tourPlacee==true) {
                    dessineTourCurseur(VectTours[i], VectTours[i].x, VectTours[i].y, MAP1);
                }
            }

            if(CompteurPlacementTour==0 && VectTours[0].tourPlacee==false) {
                dessineTourCurseur(VectTours[0], sourisX, sourisY, MAP1);
            }
            if (CompteurPlacementTour==2 && VectTours[1].tourPlacee==false) {
                    dessineTourCurseur(VectTours[1], sourisX, sourisY, MAP1);  
            }
            if (CompteurPlacementTour==4 && VectTours[2].tourPlacee==false) {
                    dessineTourCurseur(VectTours[2], sourisX, sourisY, MAP1);
            }
        }

        TextRenderer.SetTextSize(SimpleText::SIZE_16);
        std::string PdVCible_str = "Points de vie Base : " + std::to_string(PdVCible) + "/100";
        const char *PdVCible_c_str = PdVCible_str.c_str();
        TextRenderer.Label(PdVCible_c_str, 50, 200, SimpleText::LEFT);

        std::string PdVE_str = "Points de vie Elisabeth : " + std::to_string((int)Elisabeth.PdVEnnemi);
        const char *PdVE_c_str = PdVE_str.c_str();
        TextRenderer.Label(PdVE_c_str, 50, 220, SimpleText::LEFT);

        std::string PdVC_str = "Points de vie Colin : " + std::to_string((int)Colin.PdVEnnemi);
        const char *PdVC_c_str = PdVC_str.c_str();
        TextRenderer.Label(PdVC_c_str, 50, 240, SimpleText::LEFT);

        std::string PdVM_str = "Points de vie Milan : " + std::to_string((int)Milan.PdVEnnemi);
        const char *PdVM_c_str = PdVM_str.c_str();
        TextRenderer.Label(PdVM_c_str, 50, 260, SimpleText::LEFT);

        TextRenderer.Label("Jolie map tavu", _width / 2, 20, SimpleText::CENTER);
        TextRenderer.Label("Appuyez sur la touche T", _width / 50, 100, SimpleText::LEFT);
        TextRenderer.Label("pour placer les 3 Tours", _width / 50, 115, SimpleText::LEFT);

        TextRenderer.Render();

    } if(Jeu==2) {
        // Clear the color and depth buffers of the frame buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        TextRenderer.SetTextSize(SimpleText::SIZE_32);
        TextRenderer.Label("JEU TROP BIEN", _width / 2, _height / 2 - 25, SimpleText::CENTER);
        TextRenderer.SetTextSize(SimpleText::SIZE_64);
        TextRenderer.Label(" PERDU", _width / 2, _height / 2 + 25, SimpleText::CENTER);
        TextRenderer.Render(); 
    } if(Jeu==3) {
        // Clear the color and depth buffers of the frame buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        TextRenderer.SetTextSize(SimpleText::SIZE_32);
        TextRenderer.Label("JEU TROP BIEN", _width / 2, _height / 2 - 25, SimpleText::CENTER);
        TextRenderer.SetTextSize(SimpleText::SIZE_64);
        TextRenderer.Label("REUSSI", _width / 2, _height / 2 + 25, SimpleText::CENTER);
        TextRenderer.Render(); 
    } 
}

void App::key_callback(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
	    if(Jeu == 0) {
			Jeu = 1;
        }
    if(CompteurPlacementTour!=4) {
        if (key == GLFW_KEY_T && action == GLFW_PRESS)
            if(ActionPlacementTour == 0) {
                ActionPlacementTour = 1;
            } else {
                ActionPlacementTour = 0;
            }
    }
}

void App::mouse_button_callback(int button, int action, int mods) {

    if (determineSiCaseTourClique(sourisX,sourisY, MAP1) == true) {
        xposTour = sourisX;
        yposTour = sourisY;

        if(CompteurPlacementTour==0) {
            std::cout << CompteurPlacementTour << std::endl;
            VectTours[CompteurPlacementTour].x = sourisX;
            VectPosTour.push_back(sourisX);
            VectTours[CompteurPlacementTour].y = sourisY;
            VectPosTour.push_back(sourisY);
            VectTours[CompteurPlacementTour].tourPlacee = true;
            CompteurPlacementTour+=2;
        } else if(CompteurPlacementTour==2) {
            if(VectTours[(CompteurPlacementTour/2)-1].x!=sourisX && VectTours[(CompteurPlacementTour/2)-1].y!=sourisY) {
                VectTours[1].x = sourisX;
                VectPosTour.push_back(sourisX);
                VectTours[1].y = sourisY;
                VectPosTour.push_back(sourisY);
                VectTours[1].tourPlacee = true;
                std::cout << CompteurPlacementTour << std::endl;
                CompteurPlacementTour+=2;
                std::cout << CompteurPlacementTour << std::endl;
            }
        } else if(CompteurPlacementTour==4) {
            if(VectTours[1].x!=sourisX && VectTours[1].y!=sourisY) {
                if(VectTours[0].x!=sourisX && VectTours[0].y!=sourisY) {
                    VectTours[CompteurPlacementTour/2].x = sourisX;
                    VectPosTour.push_back(sourisX);
                    VectTours[CompteurPlacementTour/2].y = sourisY;
                    VectPosTour.push_back(sourisY);
                    VectTours[CompteurPlacementTour/2].tourPlacee = true;
                    CompteurPlacementTour+=2;
                }
            }
        }
    }
}

void App::scroll_callback(double /*xoffset*/, double /*yoffset*/) {
}

void App::cursor_position_callback(double xpos, double ypos) {

    // Calculer l'aspect ratio pour x
    float aspectRatio = _width / static_cast<float>(_height);

    // Coordonnées normalisées [-1, 1]
    double normalizedX = (2.0 * xpos / _width - 1.0) * aspectRatio;
    double normalizedY = 1.0 - 2.0 * ypos / _height;

    sourisX = (normalizedX * 0.5 * _viewSize + MAP1.semiTailleMap) * MAP1.nombreDePixelEnLigne;
    sourisY = (normalizedY * 0.5 * _viewSize + MAP1.semiTailleMap) * MAP1.nombreDePixelEnLigne;

}

void App::size_callback(int width, int height) {

    _width  = width;
    _height = height;

    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, _width, _height);

    const float aspectRatio { _width / (float) _height };

    // Change the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(aspectRatio > 1.0f) {
        glOrtho(-_viewSize / 2.0f * aspectRatio, _viewSize / 2.0f * aspectRatio, -_viewSize / 2.0f, _viewSize / 2.0f, -1.0f, 1.0f);
    } else {
        glOrtho(-_viewSize / 2.0f, _viewSize / 2.0f, -_viewSize / 2.0f / aspectRatio, _viewSize / 2.0f / aspectRatio, -1.0f, 1.0f);
    }
}

void App::dessineTourCurseur(Tour tour, int x, int y, MAP &Map) {
    draw_quad_with_texture(x, y, tour.texture, Map);
}

bool App::determineSiCaseTourClique(int x, int y, MAP &Map) {
    if((!((x<0 && y==0)||(x>=10 && y==9))) && y<10) {
        int numeroCase = x+(y*((int)Map.nombreDePixelEnLigne));
        if(Map.ListeCase[numeroCase].typeDeCase == typeCase::emplacement_tour) {
            return true;
        }
    }
}