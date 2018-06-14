/****************************************************************
File:
Description: fractals
Modified by: Kajal Rama
Class: CSCI - 120
Date: 4/2/17
I hereby certify that this program is entirely my own work.
*****************************************************************/

#include <SFML/Graphics.hpp>
#include <iostream>
#include<cmath>
#include "TextButton.h"
#include <vector>
#define PI 3.14159265

using namespace std;

const float TEXT_X = 10;		// x coordinate of text buttons
const float TEXT_HEIGHT = 60;	// height of each row of text button
const float TEXT_WIDTH = 300;	// width of text button panel
const float WINDOW_WIDTH = 1200; // window width
const float WINDOW_HEIGHT = 800; // window height
const float FRACTAL_WIDTH = 250;	// width of a fractal
const float FRACTAL_HEIGHT = 250;	// height of a fractal
const float FRACTAL_LEVEL = 2;		// level of a fractal
const sf::Color LINK_COLOR = sf::Color::White;		// color of text link
const sf::Color HOVER_COLOR = sf::Color::Yellow;	// color of mouse-over link
const sf::Color ACTIVE_COLOR = sf::Color::Blue;		// color of active text link 

enum TextButtonType{CLEAR, FRACTAL1, FRACTAL2, FRACTAL3, FRACTAL4};      // Enumeration for different shape fractals

vector<sf::Shape*> generateBoxFractal(float x, float y, float width, float height, int level, sf::Color color);    // Create vector for box fractals
vector<sf::Shape*> generateFractal1(float x, float y, float width, float height, int level, sf::Color color);      // Create vector for triangle fractals
vector<sf::Shape*> generateFractal2(float x, float y, float width, float height, int level, sf::Color color);      // Create vector for star fractals

int main()          // main function
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(1200, 800), "CSCI 120 - Fractals");         // this will create window title

	// set up text buttons and white drawing area
	TextButton clearButton("Clear", 40, LINK_COLOR, TEXT_X, TEXT_HEIGHT);                      // this will setup clear button to clear the window
	TextButton fractal1Button("Box Fractal", 40, ACTIVE_COLOR, TEXT_X, TEXT_HEIGHT * 2);       // this will setup box fractal button to create the box fractal
	TextButton fractal2Button("Fractal 1", 40, LINK_COLOR, TEXT_X, TEXT_HEIGHT * 3);           // this will setup fractal1 button to create the triangle fractal
	TextButton fractal3Button("Fractal 2", 40, LINK_COLOR, TEXT_X, TEXT_HEIGHT * 4);           // this will setup fractal2 button to create the star fractal
	TextButton fractal4Button("Fractal 3", 40, LINK_COLOR, TEXT_X, TEXT_HEIGHT * 5);           // this will setup fractal3 button to create any additional fractal user wants to add
	TextButton colorButton("Current Color:", 20, LINK_COLOR, TEXT_X, TEXT_HEIGHT * 6.5);       // this will show the current selected color
	sf::RectangleShape drawingArea(sf::Vector2f(WINDOW_WIDTH - TEXT_WIDTH - 5, WINDOW_HEIGHT- 10));  // this will create actual drawing area
	drawingArea.setPosition(TEXT_WIDTH, 5);                                                         // set the position of the drawing area
	drawingArea.setFillColor(sf::Color::White);                                                     // this will set the drawing area color to white
	TextButtonType activeButton = FRACTAL1;                                                         // active text button (which tool is currently used)

	// set up color palette 
	sf::Image colorImage;                                           // creates an image object
	if (!colorImage.loadFromFile("images/color-palette.png")) {    // loads the image file into the object 
		cerr << "Couldn't open image file!" << endl;               // this will print the meassage if the file doesn't open
		return EXIT_FAILURE;
	} 
	sf::Texture texture;                // create an texture object
	texture.loadFromImage(colorImage);  // this will load the color pallate image 
	sf::Sprite colorPaletteSprite;		// sprite for color palette
	colorPaletteSprite.setTexture(texture);   // this will set the color pallate as a texture
	colorPaletteSprite.setPosition(sf::Vector2f(TEXT_X, TEXT_HEIGHT * 8));    // set the color pallate on perticular position

	sf::Color currentColor = sf::Color::Red;	// current drawing color

	sf::RectangleShape colorRectangle(sf::Vector2f(50, 50)); // rectangle displaying the currently selected color
	colorRectangle.setFillColor(currentColor);              // will display the current color
	colorRectangle.setOutlineThickness(1);                  // will set the outlinethickness to 1
	colorRectangle.setOutlineColor(sf::Color::White);       // will set outline color to white
	colorRectangle.setPosition(TEXT_X, TEXT_HEIGHT * 7);    // will set the rectangle on perticular position

	vector<sf::Shape*> shapeVector;                        // vector containing pointers to shapes to be drawn

	while (window.isOpen())                               // run the program as long as the window is open
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)           // "close requested" event: we close the window
				window.close();                             // this will close the window
			else if (event.type == sf::Event::MouseMoved) {   // mouse moved event
				// mouse over effect for text buttons
				if (clearButton.contains(event.mouseMove.x, event.mouseMove.y)) {         // check if mouse is pointing to the clear button    
					clearButton.setTextColor(HOVER_COLOR);                         // if true then set the color to yellow
				}
				else
					clearButton.setTextColor(LINK_COLOR);     // if not then set it to white

				if (fractal1Button.contains(event.mouseMove.x, event.mouseMove.y)) {       // if the mouse if pointing to the boxfractal
					fractal1Button.setTextColor(HOVER_COLOR);                 // changes the color to yellow
				}
				else {
					if (activeButton == FRACTAL1)                           // if boxfractal button is clicked
						fractal1Button.setTextColor(ACTIVE_COLOR);            // set the boxfractal button to blue
					else
						fractal1Button.setTextColor(LINK_COLOR);              // if not true then set the boxfractal button to white
				}
				if (fractal2Button.contains(event.mouseMove.x, event.mouseMove.y)) {       // check if mouse is pointing to the fractal2 button
					fractal2Button.setTextColor(HOVER_COLOR);            // sets the fractal2 button to yellow
				}
				else {
					if (activeButton == FRACTAL2)             //if clicked on the fractal2 button or not
						fractal2Button.setTextColor(ACTIVE_COLOR);    //set the fractal2 button to blue color
					else
						fractal2Button.setTextColor(LINK_COLOR);    //set the fractal2 button to white color 
				}
				if (fractal3Button.contains(event.mouseMove.x, event.mouseMove.y)) {     // if mouse is pointing to the fractal2 button or not
					fractal3Button.setTextColor(HOVER_COLOR);    //sets the fractal2 button to yellow color
				}
				else {
					if (activeButton == FRACTAL3)                   //if clicked on the fractal2 button or not
						fractal3Button.setTextColor(ACTIVE_COLOR);   //set the fractal2 button to blue color
					else
						fractal3Button.setTextColor(LINK_COLOR);      //set the fractal2 button to white color
				}
				if (fractal4Button.contains(event.mouseMove.x, event.mouseMove.y)) {     //if clicked on the fractal3 button or not
					fractal4Button.setTextColor(HOVER_COLOR);                             //sets the fractal3 button to yellow color
				}
				else {
					if (activeButton == FRACTAL4)                       //if clicked on the fractal3 button or not
						fractal4Button.setTextColor(ACTIVE_COLOR);      //set the fractal3 button to blue color
					else
						fractal4Button.setTextColor(LINK_COLOR);          //set the fractal2 button to white color
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) { 
				if (event.mouseButton.button == sf::Mouse::Left &&       // clear button is clicked
					clearButton.contains(event.mouseButton.x, event.mouseButton.y)) {
					shapeVector.clear(); // clear shape vector
				}
				else if (event.mouseButton.button == sf::Mouse::Left &&  // fractal 1 button is clicked
					fractal1Button.contains(event.mouseButton.x, event.mouseButton.y)) {
					activeButton = FRACTAL1;                         // set fractal1 to active button
					fractal1Button.setTextColor(ACTIVE_COLOR); // change text color to indicate that this fractal type is selected
				}
				else if (event.mouseButton.button == sf::Mouse::Left &&  // fractal 2 button is clicked
					fractal2Button.contains(event.mouseButton.x, event.mouseButton.y)) {
					activeButton = FRACTAL2;                   //set fractal2 to active button
					fractal2Button.setTextColor(ACTIVE_COLOR); // change text color to indicate that this fractal type is selected
				}
				else if (event.mouseButton.button == sf::Mouse::Left &&  // fractal 3 button is clicked
					fractal3Button.contains(event.mouseButton.x, event.mouseButton.y)) {
					activeButton = FRACTAL3;                    //set fractal3 to active button
					fractal3Button.setTextColor(ACTIVE_COLOR); // change text color to indicate that this fractal type is selected
				}
				else if (event.mouseButton.button == sf::Mouse::Left &&  // fractal 4 button is clicked
					fractal4Button.contains(event.mouseButton.x, event.mouseButton.y)) {
					activeButton = FRACTAL4;                    //set fractal4 to active button
					fractal4Button.setTextColor(ACTIVE_COLOR); // change text color to indicate that this fractal type is selected
				}
				else if (event.mouseButton.button == sf::Mouse::Left &&  // drawing area is clicked
					drawingArea.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					if (activeButton == FRACTAL1) {                           // create box fractal
						vector<sf::Shape*> vec1 = generateBoxFractal(event.mouseButton.x, event.mouseButton.y,
							FRACTAL_WIDTH, FRACTAL_HEIGHT, FRACTAL_LEVEL, currentColor);         //generateBoxFractal function is being called
						shapeVector.insert(shapeVector.end(), vec1.begin(), vec1.end());         //insert the shape into Shape vector 
					}
					else if (activeButton == FRACTAL2) {                 //check if activebutton is fractal2
						cout << "TODO: DRAW FRACTAL TYPE 1\n";
						/** TODO: Call recursive function to create fractal **/

						
						// Things that I added
						vector<sf::Shape*> vec1 = generateFractal1(event.mouseButton.x, event.mouseButton.y,
							FRACTAL_WIDTH, FRACTAL_HEIGHT, FRACTAL_LEVEL, currentColor);         //generateFractal1 function is being called          
						shapeVector.insert(shapeVector.end(), vec1.begin(), vec1.end());         //insert the shape into Shape vector 
					}  
					else if (activeButton == FRACTAL3) {                     // check if activebutton if fractal3
						cout << "TODO: DRAW FRACTAL TYPE 2\n";
						/** TODO: Call recursive function to create fractal **/



						// Things that I added
						vector<sf::Shape*> vec1 = generateFractal2(event.mouseButton.x, event.mouseButton.y,
							FRACTAL_WIDTH, FRACTAL_HEIGHT,FRACTAL_LEVEL, currentColor);            //generateFractal2 function is being called    
						shapeVector.insert(shapeVector.end(), vec1.begin(), vec1.end());           //insert the shape into Shape vector 
					}
					else if (activeButton == FRACTAL4) {                  //// check if activebutton if fractal4
						cout << "TODO: DRAW FRACTAL TYPE 3\n";
						/** TODO: Call recursive function to create fractal **/

						
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Left &&								 // color palette is clicked
					colorPaletteSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					// get selected color from color palette and change the active drawing color
					currentColor = colorImage.getPixel(event.mouseButton.x - colorPaletteSprite.getPosition().x, 
						event.mouseButton.y - colorPaletteSprite.getPosition().y);
					colorRectangle.setFillColor(currentColor);              // change the color rectangle to show the current color
				}
			}
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw text buttons, color palette, and drawing area background
		window.draw(clearButton.getText());       //draws clearbutton
		window.draw(fractal1Button.getText());    //draws fractal1button
		window.draw(fractal2Button.getText());    //draws fractal2button
		window.draw(fractal3Button.getText());    //draws fractal3button
		window.draw(fractal4Button.getText());    //draws fractal4button
		window.draw(colorButton.getText());       //draws colorbutton
		window.draw(colorPaletteSprite);          //draws colorpalettesprites
		window.draw(colorRectangle);              //draws rectangle
		window.draw(drawingArea);                //draws drawingarea


		// draw shapes
		for (int i = 0; i < shapeVector.size(); ++i) {                  //this loop will draws the shapes that are stored in shapeVector vector
			window.draw(*shapeVector.at(i));
		}

		// end the current frame
		window.display();
	}

	return 0;
}

/**
 * Returns a vector containing pointers to Shape objects that create a box fractal of 
 * the given dimension, location, level, and color.
 * @param x			x-coordinate
 * @param y			y-coordinate
 * @param width		width in pixels
 * @param height	height in pixels
 * @param level		fractal level (nonnegative)
 * @param color		fill color
*/

//genererateBoxFractal function
vector<sf::Shape*> generateBoxFractal(float x, float y, float width, float height, int level, sf::Color color) {
	vector<sf::Shape*> vec;           //creates vector
	if (level <= 0) { // base case
		// create a rectangle of the given dimensions, position, and fill color
		sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(width, height));
		rect->setPosition(x, y);
		rect->setFillColor(color);
		vec.push_back(rect);
		return vec;
	}
	else { // recursive case
		float w = width / 3; // width of fractal of the next lower level
		float h = height / 3; // height of fractal of the next lower level
		// use recursive calls to create five fractals of the next lower level 
		//  at top-left, top-right, center, bottom-left, bottom, right
		// all the vectors returned by the recursive calls are merged into one vector
		vector<sf::Shape*> vec1 = generateBoxFractal(x, y, w, h, level - 1, color);         //recursive call
		vec.insert(vec.end(), vec1.begin(), vec1.end());                                    //insert the result into vec
		vector<sf::Shape*> vec2 = generateBoxFractal(x + 2 * w, y, w, h, level - 1, color);  //recursive call
		vec.insert(vec.end(), vec2.begin(), vec2.end());                                     //insert the result into vec
		vector<sf::Shape*> vec3 = generateBoxFractal(x + w, y + h, w, h, level - 1, color);  //recursive call
		vec.insert(vec.end(), vec3.begin(), vec3.end());                                     //insert the result into vec
		vector<sf::Shape*> vec4 = generateBoxFractal(x, y + 2 * h, w, h, level - 1, color);  //recursive call
		vec.insert(vec.end(), vec4.begin(), vec4.end());                                     //insert the result into vec
		vector<sf::Shape*> vec5 = generateBoxFractal(x + 2 * w, y + 2 * h, w, h, level - 1, color);   //recursive call
		vec.insert(vec.end(), vec5.begin(), vec5.end());                                     //insert the result into vec
	}

	return vec;
}





// things that I added

// generateFractal1 function

vector<sf::Shape*> generateFractal1(float x, float y, float width, float height, int level, sf::Color color)
{
	vector<sf::Shape*> vec;                        //vec declaration
	if (level <= 0) { // base case
					  // create a triangle of the given dimensions, position, and fill color
		sf::ConvexShape* convex = new sf::ConvexShape(3);      // this will create triangle
		convex->setPointCount(3);
		convex->setPoint(0, sf::Vector2f(x,y));               // sets the first point of the triangle
		convex->setPoint(1, sf::Vector2f(x+(width/2), y+height));   // sets the second point of the triangle
		convex->setPoint(2, sf::Vector2f(x - (width / 2), y + height));  // sets the third point of the triangle

		convex->setFillColor(color);        //fill the triangle with selected color
		vec.push_back(convex);               //insert hte triangle shape into vec
		return vec;
	}
	else { // recursive case
		float w = width / 2; // width of fractal of the next lower level
		float h = height / 2; // height of fractal of the next lower level
							  // use recursive calls to create five fractals of the next lower level 
							  //  at top-left, top-right, center, bottom-left, bottom, right
							  // all the vectors returned by the recursive calls are merged into one vector
		vector<sf::Shape*> vec1 = generateFractal1(x, y, w, h, level - 1, color);      //recursive call
		vec.insert(vec.end(), vec1.begin(), vec1.end());                               //insert shape into vec
		vector<sf::Shape*> vec2 = generateFractal1(x + (w/2) , y+(h), w, h, level - 1, color);  //recursive call
		vec.insert(vec.end(), vec2.begin(), vec2.end());                                         //insert shape into vec
		vector<sf::Shape*> vec3 = generateFractal1(x-(w/2), y+h , w, h, level - 1, color);   //recursive call
		vec.insert(vec.end(), vec3.begin(), vec3.end());                                     //insert shape into vec
		
		
		}

	return vec;
}

//generateFractal2 function
vector<sf::Shape*> generateFractal2(float x, float y, float width, float height, int level, sf::Color color)
{
	vector<sf::Shape*> vec;      //vec declaration
	if (level <= 0) { // base case
			return vec;
	}
	else { // recursive case

		float w = width / 3; // width of fractal of the next lower level
		float h = height / 2; // height of fractal of the next lower level
							  // use recursive calls to create five fractals of the next lower level 
							  //  at top-left, top-right, center, bottom-left, bottom, right
							  // all the vectors returned by the recursive calls are merged into one vector
		//int rot = 0;
		for (int i = 0; i < 5; i++)
		{
			sf::RectangleShape* line = new sf::RectangleShape(sf::Vector2f(width, 3));   //creates the rectangle shape
			//	rot = rot - 45;
			line->rotate((360 / 5 * i) - 90);    //rotate the lines to certain degrees to make a star
			line->setPosition(x, y);           //sets the position of the star
			line->setFillColor(color);          //sets the color of the star
			vec.push_back(line);           //insert the star shape
		}
		vector<sf::Shape*> vec1 = generateFractal2(x, y-width, w, h, level - 1, color);                                //recursive call
		vec.insert(vec.end(), vec1.begin(), vec1.end());                                                              //shape inserted into vec
		vector<sf::Shape*> vec2 = generateFractal2(x+width*sin(2*PI/5), y-width*cos(2*PI/5), w, h, level - 1, color);  //recursive call
		vec.insert(vec.end(), vec2.begin(), vec2.end());                                                               //shape inserted into vec
		vector<sf::Shape*> vec3 = generateFractal2(x - width*sin(2 * PI / 5), y - width*cos(2 * PI / 5), w, h, level - 1, color);  //recursive call
		vec.insert(vec.end(), vec3.begin(), vec3.end());                                                                           //shape inserted into vec
		vector<sf::Shape*> vec4 = generateFractal2(x- width*sin(4 * PI / 5), y - width*cos(4 * PI / 5), w, h, level - 1, color);   //recursive call
		vec.insert(vec.end(), vec4.begin(), vec4.end());                                                                           //shape inserted into vec
		vector<sf::Shape*> vec5 = generateFractal2(x + width*sin(4 * PI / 5), y - width*cos(4 * PI / 5), w, h, level - 1, color);   //recursive call
		vec.insert(vec.end(), vec5.begin(), vec5.end());                                                                            //shape inserted into vec
		
	}
	return vec;
}


