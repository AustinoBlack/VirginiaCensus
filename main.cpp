//Austin Black
//Nov. 24
//Lab 10
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Color{//color declaration
  double red;
  double green;
  double blue;

  string asString(){//outputs a color in svg format
    return "<path fill=\"rgb(" + to_string((red/100)*255) + "," + to_string((green/100)*255) + ","+ to_string((blue/100)*255) + ")\" ";
  }
};

struct County{//county declaration
  string countyname;
  int pop;
  double zero;
  double fifteen;
  double thirty;
  double fourtyfive;
  double sixty;

  string asString(){//outputs county as readable string
    return "{" + countyname + "," + to_string(pop) + "," + to_string(zero) + "," + to_string(thirty) + "," + to_string(sixty) + "}";
  }
};

int findLine(string msg, string word){//finds certain strings in the lines of a file
  if(msg.size() >= word.size()){
    for(int i = 0; i < msg.size()-word.size()+1; ++i){
      if(msg.substr(i,word.size()) == word){
        return i;
      }
    }
  }
  return -1;
}

int findTitle(string msg, string word){//exactly like findLine, but named differently for organization
  if(msg.size() >= word.size()){
    for(int i = 0; i < msg.size()-word.size()+1; ++i){
      if(msg.substr(i,word.size()) == word){
        return i;
      }
    }
  }
  return -1;
}

/*County findCounty(string name, vector<County> counties){//used to sort the counties to the colors would be in the correct spot
  County rv;
  for(County c: counties){
    if(c.countyname == name){
      rv = c;
    }
  }
}*/

int main(){
  vector<County> countyInfo; //holds county info from census2010
  County c;
  vector<Color> countyColor; //holds a color for each county
  Color rgb;

  vector<string> starts; //"building block vectors"
  vector<string> ends;

  vector<string> titles; //"sorting" vectors - i was planning on using the sortedtitles vector to help sort the counties, so the colors would be in the correct county.
  vector<string> sorttitles;
  vector<string> unsort;

  vector<string> vamap; //ouput vectors
  vector<string> Alpho;

  ifstream input1; //input and output file declarations
  ifstream input2;
  ofstream output;

  input1.open("census2010.txt");
    while(input1 >> c.countyname >> c.pop >> c.zero >> c.fifteen >> c.thirty >> c.fourtyfive >> c.sixty){
      c.zero += c.fifteen;
      c.thirty += c.fourtyfive;
      c.sixty = c.sixty;
      countyInfo.push_back(c); //adds and stores age groups in a vector
      unsort.push_back(c.countyname); //adds unsorted counties to a vector
        //cout << c.asString() << endl;//debug

      rgb.red = c.zero;
      rgb.green = c.thirty;
      rgb.blue = c.sixty;
      countyColor.push_back(rgb); //adds color values to a vector
        //cout << rgb.asString() << endl;//debug

      input2.open("va-tiny-names.txt");
      string line = "";
      while(getline(input2,line)){//finds lines with "<path" and replaces them with a color, already in svg format
        Alpho.push_back(line);//stores the contents of va-tiny-names in a vector for later
        int index = (findLine(line,"<path"));
        if(index != -1){
          string end = line.substr(index +5);
            ends.push_back(end);
        }
        int indey = (findTitle(line,"<title>"));//finds lines with "<title>" and separates the name of the county frrom the rest of the line
        if(indey != -1){
          string title = line.substr(indey);
          string middle = line.substr(7, line.size()-22);
          sorttitles.push_back(middle); //stores titles in a vector in the "desired" order
          //cout << middle << endl;
          titles.push_back(title);
          //cout << title << endl;
        }
      }
    }
  for(int i = 0; i < ends.size(); ++i){ //builds the bulk of the soon to be "virginia.svg" using the information that has been stored in the vectors
    //cout << countyColor[i].asString() + ends[i] + "\n" + titles[i] << endl;
    vamap.push_back(countyColor[i].asString() + ends[i] + "\n" + titles[i]);
  }

//for(int i = 0; i < unsort.size(); ++i){
  //cout << sorttitles[i]  << endl;
//}
  input1.close();//close input files
  input2.close();

  output.open("virginia.svg");
    for(int i = 0; i < 7; ++i){ //outputs the first 7 lines of va-tiny-names into the svg file
      output << Alpho[i] << endl;
    }
  
    for(string str: vamap){ //outputs the contents of "vamap" which holds the bulk of the new svg file
      output << str << endl;
    }

    output << Alpho[275] << endl; //outpts the last line of va-tiny-names
  output.close();//close output
}
