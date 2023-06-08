using System;
//using Npgsql;

class Color
{
    public double red;
    public double green;
    public double blue;

    public Color( double r, double g, double b )
    {
        red = ((r/100)*255);
        green = ((g/100)*255);
        blue = ((b/100)*255);
    }

    public override string ToString()
    {
        return $"<path=\"rgb({red}, {green}, {blue})\""; 
    }

    static void Main()
    {
        Color Accomack = new Color( 33, 37, 28);
        Console.WriteLine( Accomack.ToString() );
    }
}
