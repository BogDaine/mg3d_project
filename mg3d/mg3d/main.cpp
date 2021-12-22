
//TO DO: Functie separata care initializeaza scena (momentan se face asta in main)
// 
//TO DO: Submarine controls
//
//TO DO: Physics
//
// TO DO: Functii de get si set pentru componentele clasei Entity
//
//TO DO: Apa (la cel mai basic mod, este doar un plan cu textura albastra, sau doar culoare albastra)
// cu un shader simplu pentru apa
// 
//TO DO:texturi diferite pe teren in functie de inaltime
//shader care le blenduieste
// 
//TO DO: separarea codului (alta functie) pentru maparea umbrelor de codul care deseneaza efectiv scena (in functia Scene::Draw)
// 
//TO DO: The posibility of binding the camera to a submarine
//TO DO: Fishies! :)



//DISCLAIMER:
//  -Pare mult si complicat, dar e doar mult
//  -Codul este gandit astfel incat sa fie usor de folosit la orice aplicatie 3D
// 
// 
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//EXPLICATII:
//
//-Modelele 3D sunt in header-ul Models.h
//  -acolo se si initializeaza
//  -momentan, avem doar un model de submarin acolo
//
// 
//-Multe shadere sunt in header-ul Shaders.h
//  -acolo se si initializeaza
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Functia WindowLoop:
//  -Ruleaza la fiecare frame
//  -Apeleaza functia renderer::DrawScene
//  -Se ocupa de actualizarea scenei (Apeleaza Scene::Update)
//  -Apeleaza functia de prelucrare a input-urilor (InputHandler::HandleTheInput)
//
//Clasa Entity:
//  -Obiect ajutator pentru a face modelarea unei scene mai usoara
//  -Are functii virtuale de desenare si de actualizare
//  -Are niste vectori pentru pozitie, rotatie, viteza etc. (Trebuie facute functii de get si set pentru ei)
// 
//Clasa VisibleEntity
//  -Derivata din clasa Entity
//  -Are un Model*, modelul asociat entitatii respective
//  -Pe langa componentele clasei Entity, mai are matricea de transformare,
//   care se actualizeaza in functia VisibleEntity::Update
//  
//  -Functia VisibleEntity::Draw(Shader*):
//      -Deseneaza modelul asociat, aplicand transformarile entitatii (unde e, cum e rotita, scalarea etc.)
// 
//  -Functia VisibleEntity::Update:
//      -Actualizeaza matricea de transformare
// 
// 
//Clasa InputHandler:
//  -Clasa care se ocupa cu... input-ul de la utilizator
//  
//  -Componente:
//      -Fereastra GLFW asociata
//      -Camera asociata
//      -Submarinul asociat
//      -Modul de input
//  
//  -Se comporta diferit, in functie de modul de input selectat (se mai pot adauga moduri de input,
//   cum ar fi modul de controlare a submarinului etc.)
//      -Momentan avem doar schimbare din modul de controlare a camerei cu modul de "meniu", care nu face nimic, cu tasta ESCAPE
// 
// 
// 
// 
// 
//Clasa Scene:
//  -Are mai multe componente:
//      -Vectorul de entitati
//      -Terenul
//      -Skybox-ul
//      -Lumina (momentan numai una, functionand ca Point Light
//      
//      -FrameBuffer-ul si pentru maparea umbrelor
//      -Textura de adancimi (pentru maparea umbrelor)
//
//      -Functia Draw(Shader*):
//          -Deseneaza scena:
//              -Deseneaza terenul
//              -Deseneaza fiecare entitate folosind shader-ul primit
//              -deseneaza skybox-ul
//          -Momentan, se ocupa si de maparea umbrelor (de pus, eventual, intr-o alta functie)
//
//      -Functia Update:
//          -Cheama functia Entity::Update pentru fiecare entitate din scena
//              -(functia Entity::Update este virtuala si difera de la entitate la entitate)
//              -Momentan, avem un singur tip de entitate: Submarinul
//
//  -Pentru a adauga o entitate, se poate folosi functia Scene::PushEntity
//      -functia de desenare si functia de actualizare sunt chemate automat din functia WindowLoop, deci n-avem stres
//
// 
// 
// Clasa Texture:
//  -E folosita pentru a incarca texturile pentru modelele 3D
//  -Are si functia statica Texture::CreateTexture care returneaza un unsigned int, cum ii place lui OpenGL
//      (Luata din codul de la laborator)
// 
// Clasa Model:
//  -Se ocupa cu incarcarea si desenarea modelelor 3D
//  -E luata de pe net, dar am modificat-o ca sa nu iti omoare calculatorul
//  ----learnopengl.com----
// 
// 
// 
// Clasa Shader:
//  -Se ocupa cu shaderele GLSL
//  -E luata din codul de la laborator si modificata putin sa mearga mai bine
//      (adica are un unordered map de locatii pentru variabilele uniforme)
// 
// 
// 
// Clasa Camera:
//  -Se ocupa de matricele de transformare necesare desenarii unei scene 3D
//  -E luata din codul de la laborator si nu e modificata sa mearga mai bine, ca nu prea ma pricep la mate :)
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header-e de utility:
//      -Cfg.h
//          -Retine dimensiunea ferestrei si dimensiunea texturii pentru maparea umbrelor, momentan
//          -cfg::GetWindowWidth()
//          -cfg::GetWindowHeight()
// 
//          -cfg::GetShadowWidth()
//          -cfg::GetShadowHeight()
// 
//      -TheTime.h
//          -Se ocupa cu... timpul
//          -Functia TheTime::DeltaTime() returneaza (double) de timpul trecut de la ultimul frame
//          -Functia TheTime::LastTime() returneaza (double) de timpul trecut de la initializarea GLFW
//
// 
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Chestii smechere:
//  -Header-ul PostProcessing.h
//      -Contine efecte de postprocesare dupa randarea scenei, care pot fi inlantuite
//          (vezi in functia Renderer::DrawScene cum se foloseste)
// 
// 
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Boilerplate:
//
//  -Un set de clase ajutatoare pentru lucrul cu Bufferele OpenGL
//      (Sunt copiate toate dint filmulete de pe Youtube (The Cherno. Resursa buna pentru OpenGL)
// 
//  -GLCall
//      -este luat si el tot de acolo
//      -il folosesc la debugging (Arunca exceptii pentru functiile OpenGL care nu s-au executat corect)
//
//That's about it, for now
//-Bogdan


#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "Shader.h"

#include "glfwstuff.h"

#include "Models.h"
#include "Shaders.h"
#include "Submarine.h"


int main()
{
	GLFWwindow* window;
	InitWindow(window, "titlu imaginativ");

    //Placeholder code.
    //Will modify later
    //Like functions for scene initialization and whatnot

	Scene scene;
	int width, height;
	glfwGetWindowSize(window, &width, &height);
    Camera* pCamera = new Camera(width, height, glm::vec3(0.0f, 9.5f, 7.0f));

    InputHandler input(window, pCamera);

    std::vector<std::string> faces
    {
            "skybox/right.jpg",
            "skybox/left.jpg",
            "skybox/top.jpg",
            "skybox/bottom.jpg",
            "skybox/front.jpg",
            "skybox/back.jpg"
    };

    models::InitModels();
    shaders::InitShaders();

    


    scene.SetSkybox(faces);
    Submarine DummySubmarine({ 0, 10, 5 });
    Submarine DummySubmarine1({ 13, 45, 0 });
    DummySubmarine1.Rotate(0, 0, glm::radians(90.0f));
    scene.PushEntity(&DummySubmarine);
    //scene.PushEntity(&DummySubmarine1);

    DummySubmarine.Scale(0.05, 0.05, 0.05);
    input.BindSubmarine(&DummySubmarine);

    /*constexpr float pi = glm::pi<float>();
    float N = 10, M = 10;
    float r = 200;

    for (float n = 0; n < N; n++)
    {
        for (float m = 0; m < M; m++)
        { 
            scene.PushEntity(new Submarine(glm::vec3(sin(pi * m/M) * cos(2 * pi * n/N),
                                            sin(pi * m/M) * sin(2 * pi * n/N),
                                            cos(pi * m/M) ) * r));
        }
    }*/
    //^aia de mai sus facea o sfera din submarine^

    scene.InitShadowMap();
    Terrain terrain("..\\Assets\\Heightmaps\\terrain_smaller_2.png");
    //Terrain terrain("..\\Assets\\Misc_textures\\black.png");
    //Terrain terrain("..\\Assets\\Misc_textures\\Grass.jpg");
   // terrain.SetTexture1("..\\Assets\\Misc_textures\\white_pixel.png");
    terrain.SetTexture1("..\\Assets\\Misc_textures\\ocean_floor.jpg");
    //terrain.SetTexture1("..\\Assets\\Misc_textures\\Grass.jpg");

    scene.SetTerrain(&terrain);

    pCamera->SetMode(ECameraMode::THIRD_PERSON);
    pCamera->BindEntity(&DummySubmarine);
	WindowLoop(window, scene, pCamera, &input);

    return 0;
}