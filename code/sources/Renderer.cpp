#include "Renderer.hpp"

namespace B2D_Examples
{
	void Renderer::render_view(b2World & physical_world, RenderWindow & win)
	{
		//Mediante el método GetBodyList del mundo físico de la escena, podemos recuperar todos los cuerpos B2D presentes en la misma,
		//iterando por todos los elementos que componen dicha lista
		for (b2Body * scene_body = physical_world.GetBodyList(); scene_body != nullptr; scene_body = scene_body->GetNext())
		{
			//Por cada componente que encontremos en la lista de b2Body en la escena, obtenemos su transform (Posición en la escena)
			const b2Transform & body_transform = scene_body->GetTransform();

			//A continuación, recuperamos todas las fixtures de dicho b2Body mediante el metodo GetFixtureList(), el cual devuelve otra lista
			//con todas las fixtures que componen el b2Body
			for (b2Fixture * body_fixtures = scene_body->GetFixtureList(); body_fixtures != nullptr; body_fixtures = body_fixtures->GetNext())
			{
				//Obtenemos la forma (shape) de cada una de las fixtures que componen en b2Body
				b2Shape::Type shape_type = body_fixtures->GetShape()->GetType();

				//La manera de dibujar el componente fixture en la escena, mediante elementos SFML2 requiere saber el tipo de componente que se va a dibujar
				//para poder correlacionar los componentes gráficos con los componentes físicos, de cara a este ejemplo, solamente se contemplan formas circulares (e_circles)
				//y formas poligonales convexas (e_polygon), podrían añadirse nuevas formas, pero de cara al ejemplo no son necesarias

				//Si shape es CIRCULO (e_circle)
				if (shape_type == b2Shape::e_circle)
				{
					//Creamos un puntero a la forma de la fixture actual en la lista de fixtures (para poder acceder a sus propiedades)
					b2CircleShape * circle = dynamic_cast<b2CircleShape *>(body_fixtures->GetShape());

					//La ID nos permite saber que componente estámos cogiendo y poder modificar su color
					int id = (int)(scene_body->GetUserData());

					//Creamos el componente visual de SFML2 que representa visualmente un círculo
					CircleShape shape;

					//Ajustamos el color según el ID
					switch (id)
					{
					case 999:
						shape.setFillColor(Color::Magenta);
						break;

					default:
						shape.setFillColor(Color::Yellow);
						break;
					}
					//Obtenemos los valores a partir del componente B2D, necesarios para el dibujado y utilizamos dichos valores para que SFML2 realize
					//el dibujado de la forma en la misma posición y tamaño

					//Colocamos dicho círculo en las coordenadas obtenidas del b2Body (convirtiendo el espacio por incompatibilidad B2D / SFML2), establecemos un color
					//y pasamos el radio del circulo físico al dibujado, según esto, al dibujar, tendrá la misma forma exacta que el componente B2D
					shape.setPosition(Scene_ViewportConversion(b2Mul(body_transform, circle->m_p), (float)win.getSize().y) - Vector2f(circle->m_radius, circle->m_radius));
					shape.setRadius(circle->m_radius);
					win.draw(shape);
				}

				//Si es shape POLIGONO (e_polygon)
				else if (shape_type == b2Shape::e_polygon)
				{
					//Creamos un puntero a la forma de la fixture actual en la lista de fixtures (para poder acceder a sus propiedades)
					b2PolygonShape * box2d_polygon = dynamic_cast<b2PolygonShape *>(body_fixtures->GetShape());

					//La ID nos permite saber que componente estámos cogiendo y poder modificar su color
					int id = (int)(scene_body->GetUserData());

					//Creamos el componente visual de SFML2 que representa visualmente un polígono convexo
					ConvexShape sfml_polygon;

					//Establecemos los vértices que formará el gráfico SFML2 a partir de los vértices que forman la fixture B2D
					sfml_polygon.setPointCount(box2d_polygon->GetVertexCount());

					//Ajustamos el color según el ID
					switch (id)
					{
					case 001: case 002:
						sfml_polygon.setFillColor(Color::Green);
						break;

					case 106: case 107:
						sfml_polygon.setFillColor(Color::Red);
						break;

					case 301: case 302: case 303:
						sfml_polygon.setFillColor(Color::Magenta);
						break;

					default:
						sfml_polygon.setFillColor(Color::Cyan);
						break;
					}

					//Despues recorremos dichos vértices y pasamos su posición a la forma poligonal SFML2
					for (int i = 0; i < box2d_polygon->GetVertexCount(); i++)
					{
						sfml_polygon.setPoint( i,Scene_ViewportConversion(b2Mul(body_transform, box2d_polygon->GetVertex(i)), (float)win.getSize().y) );
					}
					win.draw(sfml_polygon);
				}
			}
		}
	}

	//Es necesaria realizar una conversión del espacio entre los valores B2D y SFML2, debido a que la
	//Y está invertida entre estas dos librerías (posición Y=0, varía de la parte superior izq a inferior izq)
	inline Vector2f Renderer::Scene_ViewportConversion(const b2Vec2 & b2dposition, float scene_height)
	{
		return Vector2f(b2dposition.x, scene_height - b2dposition.y);
	}

}

