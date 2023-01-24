# 3VGP_ArteLuna

Prerequisitos:

Windows 10
opengl 4.6
Visual Studio 2019 o superior


Instrucciones de build:

Ejecutar "build-solution.bat"


Instrucciones de ejecución:

Al ejecutar el programa, hay una escena con una ventana de ImGui con la que se pueden moficar la transformación de
los objetos en pantalla. 
Pulsar el espacio hace que los objetos se muevan en Y.


Tutorial de uso del motor.

1. Creación Entidad
2. Render component
3. Transform component
4. Inputs


1 - Creación entidad

Comenzaremos guardando la referencia del EntityManager para poder hacer uso de su función CreateNewEntity().

EntityManager& manager_ref = EntityManager::GetManager();
Entity& entity = manager_ref.CreateNewEntity(nullptr);

A la función CreateNewEntity() podremos pasarle como parametro un padre del cual será hijo nuestra entidad. Si no queremos que sea hijo de nadie tan solo tendremos
que pasarle un nullptr.

Con esto ya tendremos nuestra entidad creada.




2 - Render component

Crearemos un shared_ptr de la clase Material y le pasaremos los siguientes parámetros.

std::shared_ptr<Material> material = std::make_shared<Material>(Material(const char* vert, const char* frag,const char* texture_src, 
				     Texture::Filter mag_filter, Texture::Filter min_filter, Texture::Type type , Texture::Wrap ws, Texture::Wrap wt, Texture::Wrap wr););

Para saber que parametros podemos elegir de Filter, Type y Wrap consultar el final del readme.
Con esto habremos creado nuestro material con su vertex y fragment shader asi como su textura asociada.
Tras esto debemos asegurarnos de que nuestros path sources están bien escritos para las texturas y shaders.
A continuación antes de nuestro bucle de juego deberemos llamar a la función SetData() de la textura de nuestro material (texture_)

Deberemos pasarle los siguientes parametros
SetData(DataType d_type, unsigned int mip_map_LOD);
Para saber que parametros podemos elegir de DataType consultar el final del readme.

Ahora que ya disponemos de un material deberemos crear un mesh, para esto crearemos un shared_ptr de Mesh y le pasaremos la ruta de nuestro obj tal que así
std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("../../data/models/ugandan_sonic.obj");

Por último tan solo deberemos obtener el render component de la entidad que hayamos creado e igualarle nuestro material y nuestro mesh tal que así

RenderComponent* render_cmp =  entity.get_component<RenderComponent>();
ender_cmp->mesh_ = mesh;
material->texture_.SetData(Texture::UNSIGNED_BYTE, 0);
render_cmp->material_ = material;


Con estos pasos habremos creado nuestro render component con un material y textura asociados.




3 - Transform component

Empezamos por crear un Puntero de la clase TransformComponent que recibirá el componente TransformComponent de la entidad que deseemos mediante la función del entity manager
get_component<TransformComponent>();

TransformComponent* transform_cmp = entity.get_component<TransformComponent>();

Una vez hecho esto ya dispondremos del transform component y podremos editarlo como deseemos mediante las funciones del propio componente set_position(), set_scale(),
set_rotation() y finalmente para que funcione cualquiera de las anteriores transformaciones usaremos la función set_transform().

Los parametros que deberemos pasarles a las funciones previamente citadas son

set_position(const glm::vec3& position)

set_rotation(const glm::vec3& rotation)

set_scale(const glm::vec3& scale)

Con esto ya habremos conseguido transformar nuestra entidad a nuestro gusto.


4 - Input

Para realizar la comprobación de Input mediante teclado tan solo debemos hacer uso de la función IsKeyDown() de la clase Input llamandola desde nuestra window ya que es
la que tiene el contexto.

A la función deberemos pasarle que tecla queremos usar tal que así
window.input_->IsKeyDown(InputKeyboard::KEY_0)

Para saber que parametros de InputKeyboard podemos pasarle a la función consultar al final del readme.


Un ejemplo completo de todo lo anterior explicado sería el siguiente

int main() {
  Window window("Aleksander");
  ImGui::CreateContext();
  

  
  std::shared_ptr<Material> material = std::make_shared<Material>("../../bin/vertex.glslv",
   "../../bin/fragment.glslf", "../../data/muse.jpg", Texture::Linear, Texture::Linear, Texture::T_2D, Texture::Clamp_to_edge,
   Texture::Clamp_to_edge, Texture::Clamp_to_edge);

  std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("../../data/models/ugandan_sonic.obj");
  EntityManager& manager_ref = EntityManager::GetManager();
  

  Entity& entity = manager_ref.CreateNewEntity(nullptr);
  RenderComponent* render_cmp =  entity.get_component<RenderComponent>();
  TransformComponent* transform_cmp = entity.get_component<TransformComponent>();

  glm::vec3 position_ = { (-offset * number_of_entities) / 2.0f, 0.0f, -10.0f };
  glm::vec3 scale_ = { 1.0f, 1.0f, 1.0f };
  glm::vec3 rotation_ = { 0.0f, 0.0f, 0.0f };
  
  transform_cmp->set_position(position_);
  transform_cmp->set_scale(scale_);
  transform_cmp->set_rotation(rotation_);
  transform_cmp->set_transform();


  render_cmp->mesh_ = mesh;
  material->texture_.SetData(Texture::UNSIGNED_BYTE, 0);
  render_cmp->material_ = material;
  
  double last_time = window.GetTime();

 
  while (!window.ShouldClose()) {
    window.ProcessInput(deltatime);
    window.Clear();
	
    window.RenderScene();
    if(window.input_->IsKeyDown(InputKeyboard::Space)) {
	// Something cool
     }
  }
   
    window.Draw();
  }

  window.End();
  
  return 0;
}


  Filter {
       	Linear,
        Nearest,
        Nearest_Mipmap_Nearest,
        Linear_mipmap_nearest,
        Nearest_mipmap_linear,
        Linear_mipmap_linear
    };

    DataType {
        BYTE,
        UNSIGNED_BYTE,
        FLOAT,
        INT,
        UNSIGNED_INT,
        SHORT,
        UNSIGNED_SHORT,
    };

    Wrap {
        Repeat,
        Mirrored_repeat,
        Clamp_to_edge,
    };

    Type {
        T_Invalid = 0,
        T_1D,
        T_2D,
        T_3D,
        T_Cubemap,
    };

    Format {
        None = 0,
        R,
        RG,
        RGB,
        RGBA,
        Depth,
        Depth32,
    };


InputKeyboard
{
  UNKNOWN = -1,
  SPACE = 32,
  APOSTROPHE = 26,
  COMMA = 44,
  MINUS = 47,
  PERIOD = 46,
  SLASH = 54,
  KEY_0 = 48,
  KEY_1 = 49,
  KEY_2 = 50,
  KEY_3 = 51,
  KEY_4 = 52,
  KEY_5 = 53,
  KEY_6 = 54,
  KEY_7 = 55,
  KEY_8 = 56,
  KEY_9 = 57,
  SEMICOLON = 42,
  EQUAL = 1,
  A = 65,
  B = 66,
  C = 67,
  D = 68,
  E = 69,
  F = 70,
  G = 71,
  H = 72,
  I = 73,
  J = 74,
  K = 75,
  L = 76,
  M = 77,
  N = 78,
  O = 79,
  P = 80,
  Q = 81,
  R = 82,
  S = 83,
  T = 84,
  U = 85,
  V = 86,
  W = 87,
  X = 88,
  Y = 89,
  Z = 90,
  LEFT_BRACKET = 26,
  BACKSLASH = 41,
  RIGHT_BRACKET= 27,
  GRAVE_ACCENT= 40,
  WORLD_1 = GLFW_KEY_WORLD_1,
  WORLD_2 = GLFW_KEY_WORLD_2,
  ESCAPE = 256,
  ENTER = 28,
  TAB = 15,
  BACKSPACE = 14,
  INSERT = 338,
  DELETE= 338,
  RIGHT= 262,
  LEFT = 263,
  DOWN= 264,
  UP = 265,
  PAGE_UP= 337,
  PAGE_DOWN= 329,
  HOME = 327,
  END= 335,
  CAPS_LOCK= 58,
  SCROLL_LOCK = 281,
  NUM_LOCK = 325,
  PRINT_SCREEN = 311,
  PAUSE = 69,
  F1 = 290,
  F2 = 291,
  F3 = 292,
  F4 = 293,
  F5 = 294,
  F6 = 295,
  F7 = 296,
  F8= 297,
  F9 = 298,
  F10= 299,
  F11 = 300,
  F12 = 301,
  F13= GLFW_KEY_F13,
  F14= GLFW_KEY_F14,
  F15= GLFW_KEY_F15,
  F16 = GLFW_KEY_F16,
  F17 = GLFW_KEY_F17,
  F18 = GLFW_KEY_F18,
  F19= GLFW_KEY_F19,
  F20 = GLFW_KEY_F20,
  F21 = GLFW_KEY_F21,
  F22 = GLFW_KEY_F22,
  F23 = GLFW_KEY_F23,
  F24 = GLFW_KEY_F24,
  F25 = GLFW_KEY_F25,
  KP_0 = 320,
  KP_1 = 321,
  KP_2 = 322,
  KP_3 = 323,
  KP_4 = 324,
  KP_5 = 325,
  KP_6 = 326,
  KP_7 = 327,
  KP_8 = 328,
  KP_9 = 339,
  KP_DECIMAL = 330,
  KP_DIVIDE = 331,
  KP_MULTIPLY = 332,
  KP_SUBSTRACT = 333,
  KP_ADD = 334,
  KP_ENTER = 334,
  KP_EQUAL = 11,
  LEFT_SHIFT = 340,
  LEFT_CONTROL = 341,
  LEFT_ALT = 342,
  LEFT_SUPER = 280,
  RIGHT_SHIFT = 344,
  RIGHT_CONTROL = 345,
  RIGHT_ALT = 346,
  RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
  MENU = 349,
  LAST = 335,
}