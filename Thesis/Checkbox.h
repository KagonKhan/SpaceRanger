#pragma once

class Checkbox :
	public sf::Drawable
{
private:
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	struct Cross : public sf::Drawable
	{
	private:
		void draw(sf::RenderTarget& target, sf::RenderStates)const override;

		sf::VertexArray m_Shape;
		sf::Vector2f m_Position;
		float m_Size;
		float m_Thickness;
		float m_Padding;

		void calculateCrossQuads();

	public:
		Cross(float size, float thickness = 10.f, float padding = 0.9f, sf::Color color = sf::Color::Black);
		void setSize(float size);
		void setPosition(const sf::Vector2f& pos);
		void setPosition(float x, float y);
		sf::Vector2f getSize() const;
		void setColor(const sf::Color& color);
		// Should be in range of 0.1 - 0.9
		void setPadding(float padding);
		void setThickness(float thickness);
	} m_Cross;

	sf::Vector2f m_Position;
	sf::Color m_FillColor;
	sf::RectangleShape m_Shape;
	bool m_IsChecked;

public:
	Checkbox(float size = 25.f, const sf::Color& bgColor = sf::Color(200, 200, 200));



#pragma region SETTERS / GETTERS

	void setPosition(const sf::Vector2f& pos);
	void setFillColor(const sf::Color& color);
	void setSize(float size);

	void setIsChecked(bool checked)				{	m_IsChecked = checked;					};
	bool getIsChecked() const					{	return m_IsChecked;						};
	void setPosition(float x, float y)			{	setPosition(sf::Vector2f(x, y));		};
	void setOutlineThickness(float thickness)	{	m_Shape.setOutlineThickness(thickness);	};
	sf::Vector2f getSize() const				{	return m_Shape.getSize();				};


#pragma endregion

};
