#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace std;
using namespace sf;
namespace B2D_Examples {

class Renderer
{
public:

	//Debido a la diferencia en coordenadas entre SFML2 y Box2D, se hace una conversión del espacio del viewport
	inline Vector2f Scene_ViewportConversion(const b2Vec2 & box2d_position, float window_height);

	//Renderizado de la escena
	void render_view(b2World & physical_world, RenderWindow & win);
};
}
