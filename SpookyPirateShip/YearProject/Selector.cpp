#include "Selector.h"

Selector::Selector(ResourceManager& t_gameAssets) :
	triangle{sf::Triangles},
	gameassets{&t_gameAssets}
{
	initialize();
}

Selector::~Selector()
{
}

void Selector::clearGUI()
{
	m_slelectorGUI.clearGUI();
}

void Selector::update(sf::Time t_deltaTime, MyVector3 mouseClick, int scroll, bool pressed)
{
	if (scroll < 0)
	{
		m_slelectorGUI.movewidgets(0, -50);
		startY -= 50;
		
	}
	else if(scroll > 0)
	{
		if (startY + 50 <= 0)
		{
			m_slelectorGUI.movewidgets(0, 50);
			startY += 50;
		}
	}
	std::cout << startY << std::endl;
}

void Selector::render(sf::RenderWindow& t_window)
{
	//triangle.append(c1);
	//triangle.append(c2);
	//triangle.append(c3);
	//t_window.draw(triangle);
	t_window.draw(m_displayBox);
	m_slelectorGUI.render(t_window);
}

void Selector::initialize()
{
	m_position = MyVector3(1536,0,0);
	m_displayBox.setPosition(m_position);
	m_displayBox.setFillColor(sf::Color(200,200,200,255));
	m_displayBox.setOutlineColor(sf::Color::Black);
	m_displayBox.setOutlineThickness(2);
	m_displayBox.setSize(sf::Vector2f(384, 1280));
	c1.color = sf::Color(255, 255, 255, 255);
	c2.color = sf::Color(255, 255, 255, 255);
	c3.color = sf::Color(255, 255, 255, 255);

	sf::Font font;
	try {
		font.loadFromFile("FasterOne-Regular.ttf");
	}
	catch(...){

	}
	
	Button* button1 = new Button(gameassets->m_gameTextures["Test0"], 384, 128);
	button1->setButtonTag("Test0");
	button1->setIndex(0);
	button1->setPosition(sf::Vector2f(1536, 0));
	widgetPosArray.push_back(sf::Vector2f(button1->getPosition()));
	button1->setRotation(0);
	button1->resetOrigin();
	button1->setOutline(sf::Color::Black, 3);
	button1->setAsStarter();
	m_slelectorGUI.addWidget(button1);
	m_slelectorGUI.setStartFocus(button1);

	for (int i = 1; i < 15; i++)
	{
		std::string stg = "Test" + std::to_string(i);
		std::cout << stg << std::endl;
		Button* button = new Button(gameassets->m_gameTextures[stg], 384, 128);
		button->setButtonTag(stg);
		button->resetOrigin();
		button->setIndex(i);
		button->setPosition(sf::Vector2f(1536, 128*(i)));
		button->setRotation(0);
		button->setOutline(sf::Color::Black, 3);
		m_slelectorGUI.addWidget(button);
		widgetPosArray.push_back(sf::Vector2f(button->getPosition()));
	}

}

void Selector::setPosition(MyVector3 t_position)
{
	//c1.position = t_position;
	//c2.position = t_position + MyVector3(50, -50, 0);
	//c3.position = t_position + MyVector3(50,  50, 0);
	m_position = t_position + MyVector3(0, 0, 0);
	m_displayBox.setPosition(t_position);
	//m_slelectorGUI.setWidgetPositons(m_position);
}

void Selector::setLength(float lenght)
{
	m_displayBox.setSize(sf::Vector2f(m_displayBox.getSize().x, lenght));
}

std::pair<std::string, int> Selector::selectTile(MyVector3 mousePos)
{
	return m_slelectorGUI.findSelected(mousePos);
}

void Selector::runAction(std::string& t_actionString)
{
}

void Selector::handleControllerInput()
{
}

void Selector::moveWidgets(sf::Vector2f mv)
{
	m_slelectorGUI.movewidgets(mv.x, mv.y);
}

void Selector::updateWids(sf::Vector2f t_diffOfCam)
{
	std::vector<sf::Vector2f> temp;
	for (auto& goop : widgetPosArray)
	{
		temp.push_back(goop + t_diffOfCam);
	}
	m_slelectorGUI.setWidgetPositons(temp);
}
