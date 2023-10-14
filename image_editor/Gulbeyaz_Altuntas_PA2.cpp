#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Image{  

    private:
    int width; 
    int height;
    int max_val; 
    vector <int> pixels;  // created a vector to save the datas in it

    public: 
    void menu();  // this function has the menu options in it, we call other functions inside this menu 
    void open_image_menu();  // it opens the ppm file and prints the values into a vector
    void script_to_grayscale(); // it changes the values of the vector with new ones
    void save_data_image();  // it saves the new datas in the vector to another output file

};


void Image::menu(){

    int option, choice;
    string input;

   while(true){  // we call the main menu over and over again until user enters "0"

    cout << "MAIN MENU" << endl;
    cout << "0 - Exit" << endl;
    cout << "1 - Open An IMAGE (D)" << endl;
    cout << "2 - Save Image Data (D)" << endl;
    cout << "3 - Scripts (D)" << endl;

    cin >> option;

    switch(option){
       
        case 0: 
        exit(0);
        break;

        case 1:
        cout << "OPEN AN IMAGE MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Enter The Name Of The Image File" << endl;
        cin >> choice;
        if (choice == 0){
            break;
        }
        if (choice == 1){
            open_image_menu();  // opens the ppm file
            }
        break;

       
        case 2:
        cout << "SAVE IMAGE DATA" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Enter A File Name" << endl;
        cin >> choice;
        if (choice == 0){
            break;
        }
        if(choice == 1){
           save_data_image(); 
           exit(0); // after saving the data I exited, if the user wants to do it with another file then they have to compile again
        }
        break;

        case 3:
        cout << "SCRIPTS" << endl;
        cout << "CONVERT TO GRAYSCALE MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels." << endl;
        cin >> choice;
        if (choice == 0){
            break;
        }
        if (choice == 1){
         script_to_grayscale();  // changes the values 
        }
        break;

        default:
        cout << "Input error" << endl;  // if the user enters something other than 1-2-3 then it will give input error
        }

    }
   
}



void Image::open_image_menu(){

    string filename;  // getting the filename
    cin >> filename;

    ifstream file(filename);
    
    if (!file.is_open()) { // if it doesn't open the file then we give error and exit
        cout << "There is not a file like that." << endl; 
        exit(0);
    }

    string magic_number; // this magic number is "p3" format ( I googled and they used magic_number so I wanted to use it)

    file >> magic_number;
    file >> width >> height >> max_val; // we read the width, height and max_value from the file
  
    // printing the magic_number, width, height, max_val:
    cout << magic_number << endl; 
    cout << width << " " << height << endl;
    cout << max_val << endl;

    pixels.resize(width * height * 3); // i sized the pixels vector here
    int value; // this is for the reading every number 
    
     for (int i = 0; i < width * height * 3; i++) {  // since every pixel has red, green, blue values, we multiply it with three
        file >> value;
        pixels[i] = value;
    }
    
    int red, green, blue; // to take the values and print them, red equals to 0, green to 1, blue to 2 and it all continues till the last one
    
   for (int i = 0; i < height; i++) { // for rows
        for (int j = 0; j < width; j++) {  // for coloumns
            int pixel_index = (i * width + j) * 3;  // calculate the index of the first byte of the rgb values for the current pixel, I stored them as 0, 1, 2
            red = pixels[pixel_index];
            green = pixels[pixel_index + 1];
            blue = pixels[pixel_index + 2];
            cout << "  "  << red << "  " << green << "  " << blue << "  ";  
        }
        cout << endl;  // a new line for every rows
    }
    file.close();
    
}

 void Image::script_to_grayscale(){
 
    float c_r, c_g, c_b;  // our entered float numbers that's going to change red, blue, green values
    cin >> c_r;
    cin >> c_g;
    cin >> c_b;

    while(c_r >= 1 || c_r < 0 && c_g >= 1 || c_g < 0  && c_b >= 1 || c_b < 0 ){ // input error
        cout << "Enter a valid number please, between [0,1):" << endl;
        cin >> c_r;
        cin >> c_g;
        cin >> c_b;
    }

    float red, green, blue;  // defined them in float now

    for (int i = 0; i < height; i++) { // for rows
         for (int j = 0; j < width; j++) { // for coloumns
            int pixel_index = (i * width + j) * 3;
            red = pixels[pixel_index];
            green = pixels[pixel_index + 1];
            blue = pixels[pixel_index + 2];
            pixels[pixel_index] = c_r * red + c_g * green + c_b * blue; // changed to the new values for every byte
            pixels[pixel_index + 1] = c_r * red + c_g * green + c_b * blue;
            pixels[pixel_index + 2] = c_r * red + c_g * green + c_b * blue;

        if(pixels[pixel_index] > 255){ // if the calculated new version is bigger than 255, we take them as 255
            pixels[pixel_index] = 255;
            pixels[pixel_index+1] = 255;
            pixels[pixel_index+2] = 255;
        }

    }
        cout << endl;
    }

 }

 void Image::save_data_image(){

    string file_name; 
    cin >> file_name;
    ofstream output_file(file_name); // opened an empty file
    
    output_file << "P3" << endl;
    output_file << width << " " << height << endl;
    output_file << "255" << endl;

     //  writing the new pixel values to the file with the same method
        
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
        int pixel_index = (i * width + j) * 3;
        output_file << pixels[pixel_index] << " ";
        output_file << pixels[pixel_index + 1] << " ";
        output_file << pixels[pixel_index + 2] << " ";
            }
            output_file << endl;
    }
    output_file.close();
    
   
 }


int main(){

    Image my_image; // defining our class
    my_image.menu(); // called the menu first and after the menu is called, the user is going to choose the other options from the menu

    return 0;
}
