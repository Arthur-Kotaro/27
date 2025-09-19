#include <iostream>
#include <string>
#include <cmath>
#include "main1.hpp"

enum Colour {red, green, blue};
class GeomShape
{
    Colour shapeColour;
    double center_X_AxisCoordinate;
    double center_Y_AxisCoordinate;
    double ShapeArea;
    double CircumscribedRectanglesSideA;
    double CircumscribedRectanglesSideB;
public:
    GeomShape()
    {
        std::string inpColour;
        std::cout << "Enter X-Axis and Y-Axis Coordinates of figures center: ";
        std::cin >> center_X_AxisCoordinate >> center_Y_AxisCoordinate;
        do
        {
            std::cout << "Enter colour (red,green, blue): ";
            std::cin >> inpColour;
        } while (inpColour != "red" && inpColour != "green" && inpColour != "blue");
        if(inpColour == "red") shapeColour = red;
        else if(inpColour == "green") shapeColour = green;
        else if(inpColour == "blue") shapeColour = blue;
    }
    ShowInfo()
    {
        if(shapeColour == red) std::cout << "Red ";
        else if(shapeColour == green) std::cout << "Green ";
        else if(shapeColour == blue) std::cout << "Blue ";
        std::cout << input_str << "\'s area equals to " << tmp->FigureOutArea() << ". It\'s Circumscribed Rectangle\'s Sides equals to " << CircumscribedRectanglesSideA << " and " << CircumscribedRectanglesSideB << ".\n";

    }
};

class Circle:public GeomShape
{
    double radius;
public:
    Circle()
    {
        do
        {
            std::cout << "Enter radius of a circle: ";
            std::cin >> radius;
        } while (radius <= 0);
        ShapeArea = FigureOutArea();
        FigureOutCircumscribedRectangle();
    }

    double FigureOutArea() { return M_PI * radius * radius; }

    FigureOutCircumscribedRectangle()
    {
        CircumscribedRectanglesSideA = 2 * radius;
        CircumscribedRectanglesSideB =  CircumscribedRectanglesSideA;
    }
};

class Square:public GeomShape
{
    double squareSideLength;
public:
    Square()
    {
        do
        {
            std::cout << "Enter side length of a square: ";
            std::cin >> squareSideLength;
        } while (squareSideLength <= 0);
        ShapeArea = FigureOutArea();
        FigureOutCircumscribedRectangle();
    }

    double FigureOutArea() { return squareSideLength * squareSideLength; }

    FigureOutCircumscribedRectangle()
    {
        CircumscribedPectanglesSideA = squareSideLength;
        CircumscribedRectanglesSideB = CircumscribedPectanglesSideA;
    }
};

class EquilateralTriangle:public GeomShape
{
    double equilateralTriangleSideLength;
public:
    EquilateralTriangle()
    {
        do
        {
            std::cout << "Enter side length of an equilateral triangle: ";
            std::cin >> equilateralTriangleSideLength;
        } while (equilateralTriangleSideLength <= 0);
        ShapeArea = FigureOutArea();
        FigureOutCircumscribedRectangle();
    }

    double FigureOutArea() { return equilateralTriangleSideLength * equilateralTriangleSideLength * std::sqrt(3) / 4; }

    FigureOutCircumscribedRectangle()
    {
        CircumscribedPectanglesSideA = equilateralTriangleSideLength;
        CircumscribedPectanglesSideB = CircumscribedPectanglesSideA * sin (M_PI / 6); // sin (90 - (180/3) = sin (30), 30 in rad equals 2Pi / (360/30) => 2Pi / 12 => Pi / 6
    }
};

class Rectangle:public GeomShape
{
    double rectangle_A_SideLength;
    double rectangle_B_SideLength;
public:
    Rectangle()
    {
        double RectangleSide_A_Length;
        double RectangleSide_B_Length;
        do
        {
            std::cout << "Enter rectangles A-side length and B-side length : ";
            std::cin >> RectangleSide_A_Length >> RectangleSide_B_Length;
        } while (RectangleSide_A_Length <= 0 || RectangleSide_B_Length <= 0);
        ShapeArea = FigureOutArea();
        FigureOutCircumscribedRectangle();
    }

    double FigureOutArea() { return RectangleSide_A_Length * RectangleSide_B_Length;}

    FigureOutCircumscribedRectangle()
    {
        CircumscribedPectanglesSideA = RectangleSide_A_Length;
        CircumscribedPectanglesSideB = RectangleSide_B_Length);
    }
};


int main()
{
    std::string input_str;
    void * tmp = nullptr;
    do
    {
        std::cout<< "\nEnter command (circle/square/triangle/rectangle/exit): ";
        std::cin>>input_str;
        if (input_str == "circle")          (Circle *) tmp = new Circle;
        else if (input_str == "square")     (Square *) tmp = new Square;
        else if (input_str == "triangle")   (EquilateralTriangle *) tmp = new EquilateralTriangle;
        else if (input_str == "rectangle")  (Rectangle * tmp) = new Rectangle;
        else if (input_str == "exit")       break;
        else
        {
            std::cout<< "Invalid input. Try again.\n";
            continue;
        }
        tmp->ShowInfo();
        delete tmp;
        tmp = nullptr;
    } while (true);
    return 0;
}
