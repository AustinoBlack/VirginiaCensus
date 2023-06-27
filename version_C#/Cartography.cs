using System;
//using Npgsql;

class Color
{
    public double red;
    public double green;
    public double blue;

    // young - ages 0-30
    // adult - ages 31-60
    // senior - ages 60+
    // Color creates a rgb color values from the population values of a County
    public Color( double young, double adult, double senior )
    {
        red = ((young/100)*255);
        green = ((adult/100)*255);
        blue = ((senior/100)*255);
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

class County
{
    public string name;
    public int population;
    public int zero;
    public int fifteen;
    public int thirty;
    public int fourtyfive;
    public int sixty;
}
